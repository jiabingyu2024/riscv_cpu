import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;

module ExecuteBrcStage(
    ReadRegStageIF.ExecuteBrcStage prev,
    ExecuteStageIF.ExecuteBrcStage self,
    CtrlIF.ExecuteStage ctrl,
    BypassIF.ExecuteBrcStage bypass
);
    always_comb begin
        for (int i = 0; i < BYPASS_READ_PORT_NUM; i++) bypass.brcReadReq[i] = '0;
        for (int i = 0; i < WAY_NUM; i++) begin
            DataPath a;
            DataPath b;
            bypass.brcReadReq[i*2+0].valid = prev.nextToBrcStage[i].valid && prev.nextToBrcStage[i].srcAIsRs1;
            bypass.brcReadReq[i*2+0].phyRegNum = prev.nextToBrcStage[i].Rs1;
            bypass.brcReadReq[i*2+1].valid = prev.nextToBrcStage[i].valid && prev.nextToBrcStage[i].srcBIsRs2;
            bypass.brcReadReq[i*2+1].phyRegNum = prev.nextToBrcStage[i].Rs2;
            a = bypass.brcReadRes[i*2+0].hit ? bypass.brcReadRes[i*2+0].data : prev.nextToBrcStage[i].dataA;
            b = bypass.brcReadRes[i*2+1].hit ? bypass.brcReadRes[i*2+1].data : prev.nextToBrcStage[i].dataB;

            self.nextBrcToStage[i].valid = prev.nextToBrcStage[i].valid && !ctrl.exPipe.flush;
            self.nextBrcToStage[i].Rd = prev.nextToBrcStage[i].Rd;
            self.nextBrcToStage[i].writeRd = prev.nextToBrcStage[i].writeRd;
            self.nextBrcToStage[i].data = DataPath'(prev.nextToBrcStage[i].robIndex);
            self.nextBrcToStage[i].robIndex = prev.nextToBrcStage[i].robIndex;
            self.nextBrcToStage[i].taken = (a == b);
            self.nextBrcToStage[i].trueTargetPc = a + b;
        end
    end
endmodule
