import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;

module ExecuteSysStage(
    ReadRegStageIF.ExecuteSysStage prev,
    ExecuteStageIF.ExecuteSysStage self,
    CtrlIF.ExecuteStage ctrl,
    BypassIF.ExecuteSysStage bypass
);
    always_comb begin
        for (int i = 0; i < BYPASS_READ_PORT_NUM; i++) bypass.sysReadReq[i] = '0;
        for (int i = 0; i < WAY_NUM; i++) begin
            bypass.sysReadReq[i*2].valid = prev.nextToSysStage[i].valid && prev.nextToSysStage[i].srcAIsRs1;
            bypass.sysReadReq[i*2].phyRegNum = prev.nextToSysStage[i].Rs1;
            self.nextSysToStage[i].valid = prev.nextToSysStage[i].valid && !ctrl.exPipe.flush;
            self.nextSysToStage[i].Rd = prev.nextToSysStage[i].Rd;
            self.nextSysToStage[i].writeRd = prev.nextToSysStage[i].writeRd;
            self.nextSysToStage[i].data = bypass.sysReadRes[i*2].hit ? bypass.sysReadRes[i*2].data :
                                          prev.nextToSysStage[i].dataA;
            self.nextSysToStage[i].robIndex = prev.nextToSysStage[i].robIndex;
            self.nextSysToStage[i].isSerial = 1'b1;
            self.nextSysToStage[i].exception =
                prev.nextToSysStage[i].subType.sysSubType == SYS_SUBTYPE_ECALL ||
                prev.nextToSysStage[i].subType.sysSubType == SYS_SUBTYPE_EBREAK;
        end
    end
endmodule
