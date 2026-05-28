import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;

module ExecuteSysStage(
    ReadRegStageIF.ExecuteSysStage prev,
    ExecuteStageIF.ExecuteSysStage self,
    CtrlIF.ExecuteStage ctrl,
    BypassIF.ExecuteSysStage bypass
);
    RrToExSysPath pipeReg [WAY_NUM];

    always_ff @(posedge self.clk or posedge self.rst) begin
        if (self.rst) begin
            for (int i = 0; i < WAY_NUM; i++) begin
                pipeReg[i] <= '0;
            end
        end else if (!ctrl.exPipe.stall) begin
            pipeReg <= prev.nextToSysStage;
        end
    end

    always_comb begin
        for (int i = 0; i < BYPASS_READ_PORT_NUM; i++) bypass.sysReadReq[i] = '0;
        for (int i = 0; i < WAY_NUM; i++) begin
            bypass.sysReadReq[i*2].valid = pipeReg[i].valid && pipeReg[i].srcAIsRs1;
            bypass.sysReadReq[i*2].phyRegNum = pipeReg[i].Rs1;
            self.nextSysToStage[i].valid = pipeReg[i].valid && !ctrl.exPipe.flush && !ctrl.exPipe.stall;
            self.nextSysToStage[i].Rd = pipeReg[i].Rd;
            self.nextSysToStage[i].writeRd = pipeReg[i].writeRd;
            self.nextSysToStage[i].data = bypass.sysReadRes[i*2].hit ? bypass.sysReadRes[i*2].data :
                                          pipeReg[i].dataA;
            self.nextSysToStage[i].robIndex = pipeReg[i].robIndex;
            self.nextSysToStage[i].isSerial = 1'b1;
            self.nextSysToStage[i].exception =
                pipeReg[i].subType.sysSubType == SYS_SUBTYPE_ECALL ||
                pipeReg[i].subType.sysSubType == SYS_SUBTYPE_EBREAK;
        end
    end
endmodule
