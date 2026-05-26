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
    always_comb begin
        dram.req = 1'b0;
        dram.we = 1'b0;
        dram.addr = '0;
        dram.wdata = '0;
        dram.wstrb = '0;
        storeBuffer.StoreBufferMatchIn = '0;
        storeBuffer.StoreBufferPushReq = '0;
        for (int i = 0; i < BYPASS_READ_PORT_NUM; i++) bypass.memReadReq[i] = '0;

        for (int i = 0; i < WAY_NUM; i++) begin
            DataPath base;
            DataPath dataB;
            base = prev.nextToMemStage[i].dataA;
            dataB = prev.nextToMemStage[i].dataB;
            bypass.memReadReq[i*2+0].valid = prev.nextToMemStage[i].valid && prev.nextToMemStage[i].srcAIsRs1;
            bypass.memReadReq[i*2+0].phyRegNum = prev.nextToMemStage[i].Rs1;
            bypass.memReadReq[i*2+1].valid = prev.nextToMemStage[i].valid && prev.nextToMemStage[i].srcBIsRs2;
            bypass.memReadReq[i*2+1].phyRegNum = prev.nextToMemStage[i].Rs2;
            if (bypass.memReadRes[i*2+0].hit) base = bypass.memReadRes[i*2+0].data;
            if (bypass.memReadRes[i*2+1].hit) dataB = bypass.memReadRes[i*2+1].data;

            self.nextMemToStage[i].valid = prev.nextToMemStage[i].valid && !ctrl.exPipe.flush;
            self.nextMemToStage[i].Rd = prev.nextToMemStage[i].Rd;
            self.nextMemToStage[i].writeRd = prev.nextToMemStage[i].writeRd;
            self.nextMemToStage[i].robIndex = prev.nextToMemStage[i].robIndex;
            self.nextMemToStage[i].data = dram.rvalid ? dram.rdata : '0;

            if (prev.nextToMemStage[i].valid) begin
                if (prev.nextToMemStage[i].subType.memSubType inside {MEM_SUBTYPE_SB, MEM_SUBTYPE_SH, MEM_SUBTYPE_SW}) begin
                    storeBuffer.StoreBufferPushReq.valid = 1'b1;
                    storeBuffer.StoreBufferPushReq.addr = base + prev.nextToMemStage[i].imm;
                    storeBuffer.StoreBufferPushReq.data = dataB;
                end else begin
                    dram.req = 1'b1;
                    dram.we = 1'b0;
                    dram.addr = base + prev.nextToMemStage[i].imm;
                    storeBuffer.StoreBufferMatchIn.valid = 1'b1;
                    storeBuffer.StoreBufferMatchIn.addr = dram.addr;
                    if (storeBuffer.StoreBufferMatchOut.hit) begin
                        self.nextMemToStage[i].data = storeBuffer.StoreBufferMatchOut.data;
                    end
                end
            end
        end
    end
endmodule
