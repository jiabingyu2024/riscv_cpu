import BasicTypes::*;
import PipelineTypes::*;
import StoreBufferTypes::*;
import ReadRegTypes::*;

module ExecuteMemStage(
    ReadRegStageIF.ExecuteMemStage prev,
    ExecuteStageIF.ExecuteMemStage self,
    CtrlIF.ExecuteStage ctrl,
    DramAccessIF.core dram,
    StoreBufferIF.ExecuteMemStage storeBuffer,
    BypassIF.ExecuteMemStage bypass
);
    ExMemToWbPath loadPipe0;
    ExMemToWbPath loadPipe1;
    ExMemToWbPath loadRsp;
    ExMemToWbPath loadLaunch;

    function automatic logic is_store(input MemSubType st);
        return st inside {MEM_SUBTYPE_SB, MEM_SUBTYPE_SH, MEM_SUBTYPE_SW};
    endfunction

    function automatic logic [3:0] store_wstrb(input MemSubType st, input AddrPath addr);
        unique case (st)
            MEM_SUBTYPE_SB: store_wstrb = 4'b0001 << addr[1:0];
            MEM_SUBTYPE_SH: store_wstrb = addr[1] ? 4'b1100 : 4'b0011;
            default:        store_wstrb = 4'b1111;
        endcase
    endfunction

    function automatic DataPath align_store_data(input MemSubType st, input AddrPath addr, input DataPath data);
        unique case (st)
            MEM_SUBTYPE_SB: align_store_data = data << (addr[1:0] * 8);
            MEM_SUBTYPE_SH: align_store_data = data << (addr[1] * 16);
            default:        align_store_data = data;
        endcase
    endfunction

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            loadPipe0 <= '0;
            loadPipe1 <= '0;
            loadRsp <= '0;
        end else if (ctrl.exPipe.flush) begin
            loadPipe0 <= '0;
            loadPipe1 <= '0;
            loadRsp <= '0;
        end else begin
            loadRsp <= '0;
            if (loadPipe1.valid && dram.rvalid) begin
                loadRsp <= loadPipe1;
                loadRsp.data <= dram.rdata;
            end
            loadPipe1 <= loadPipe0;
            loadPipe0 <= '0;
            if (dram.req && !dram.we) begin
                loadPipe0 <= loadLaunch;
            end
        end
    end

    always_comb begin
        logic loadSelected;

        dram.req = 1'b0;
        dram.we = 1'b0;
        dram.addr = '0;
        dram.wdata = '0;
        dram.wstrb = '0;
        storeBuffer.StoreBufferMatchIn = '0;
        storeBuffer.StoreBufferPushReq = '0;
        loadLaunch = '0;
        loadSelected = 1'b0;

        for (int i = 0; i < BYPASS_READ_PORT_NUM; i++) bypass.memReadReq[i] = '0;
        for (int i = 0; i < WAY_NUM; i++) begin
            self.nextMemToStage[i] = '0;
        end

        if (loadRsp.valid) begin
            self.nextMemToStage[0] = loadRsp;
        end

        for (int i = 0; i < WAY_NUM; i++) begin
            DataPath base;
            DataPath dataB;
            AddrPath effAddr;

            base = prev.nextToMemStage[i].dataA;
            dataB = prev.nextToMemStage[i].dataB;
            bypass.memReadReq[i*2+0].valid = prev.nextToMemStage[i].valid && prev.nextToMemStage[i].srcAIsRs1;
            bypass.memReadReq[i*2+0].phyRegNum = prev.nextToMemStage[i].Rs1;
            bypass.memReadReq[i*2+1].valid = prev.nextToMemStage[i].valid && prev.nextToMemStage[i].srcBIsRs2;
            bypass.memReadReq[i*2+1].phyRegNum = prev.nextToMemStage[i].Rs2;
            if (bypass.memReadRes[i*2+0].hit) base = bypass.memReadRes[i*2+0].data;
            if (bypass.memReadRes[i*2+1].hit) dataB = bypass.memReadRes[i*2+1].data;

            effAddr = base + prev.nextToMemStage[i].imm;

            if (prev.nextToMemStage[i].valid && !ctrl.exPipe.flush) begin
                if (is_store(prev.nextToMemStage[i].subType.memSubType)) begin
                    storeBuffer.StoreBufferPushReq.valid = prev.nextToMemStage[i].storeBufferIndexValid;
                    storeBuffer.StoreBufferPushReq.index = prev.nextToMemStage[i].storeBufferIndex;
                    storeBuffer.StoreBufferPushReq.addr = effAddr;
                    storeBuffer.StoreBufferPushReq.data =
                        align_store_data(prev.nextToMemStage[i].subType.memSubType, effAddr, dataB);
                    storeBuffer.StoreBufferPushReq.wstrb =
                        store_wstrb(prev.nextToMemStage[i].subType.memSubType, effAddr);

                    self.nextMemToStage[i].valid = 1'b1;
                    self.nextMemToStage[i].Rd = prev.nextToMemStage[i].Rd;
                    self.nextMemToStage[i].writeRd = 1'b0;
                    self.nextMemToStage[i].robIndex = prev.nextToMemStage[i].robIndex;
                end else if (!loadSelected) begin
                    storeBuffer.StoreBufferMatchIn.valid = 1'b1;
                    storeBuffer.StoreBufferMatchIn.addr = effAddr;

                    loadLaunch.valid = 1'b1;
                    loadLaunch.Rd = prev.nextToMemStage[i].Rd;
                    loadLaunch.writeRd = prev.nextToMemStage[i].writeRd;
                    loadLaunch.robIndex = prev.nextToMemStage[i].robIndex;

                    if (storeBuffer.StoreBufferMatchOut.hit) begin
                        self.nextMemToStage[0].valid = 1'b1;
                        self.nextMemToStage[0].Rd = loadLaunch.Rd;
                        self.nextMemToStage[0].writeRd = loadLaunch.writeRd;
                        self.nextMemToStage[0].robIndex = loadLaunch.robIndex;
                        self.nextMemToStage[0].data = storeBuffer.StoreBufferMatchOut.data;
                    end else begin
                        dram.req = 1'b1;
                        dram.we = 1'b0;
                        dram.addr = effAddr;
                    end
                    loadSelected = 1'b1;
                end
            end
        end
    end
endmodule
