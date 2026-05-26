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
            self.nextBrcToStage[i].data = prev.nextToBrcStage[i].pc + 32'd4;
            self.nextBrcToStage[i].robIndex = prev.nextToBrcStage[i].robIndex;
            self.nextBrcToStage[i].taken = 1'b0;
            self.nextBrcToStage[i].trueTargetPc = prev.nextToBrcStage[i].pc + 32'd4;

            unique case (prev.nextToBrcStage[i].subType.brcSubType)
                BRC_SUBTYPE_BEQ:  self.nextBrcToStage[i].taken = (a == b);
                BRC_SUBTYPE_BNE:  self.nextBrcToStage[i].taken = (a != b);
                BRC_SUBTYPE_BLT:  self.nextBrcToStage[i].taken = ($signed(a) < $signed(b));
                BRC_SUBTYPE_BGE:  self.nextBrcToStage[i].taken = ($signed(a) >= $signed(b));
                BRC_SUBTYPE_BLTU: self.nextBrcToStage[i].taken = (a < b);
                BRC_SUBTYPE_BGEU: self.nextBrcToStage[i].taken = (a >= b);
                BRC_SUBTYPE_JAL,
                BRC_SUBTYPE_JALR: self.nextBrcToStage[i].taken = 1'b1;
                default:          self.nextBrcToStage[i].taken = 1'b0;
            endcase

            if (prev.nextToBrcStage[i].subType.brcSubType == BRC_SUBTYPE_JALR) begin
                self.nextBrcToStage[i].trueTargetPc = (a + prev.nextToBrcStage[i].imm) & ~32'd1;
            end else if (self.nextBrcToStage[i].taken) begin
                self.nextBrcToStage[i].trueTargetPc = prev.nextToBrcStage[i].pc + prev.nextToBrcStage[i].imm;
            end
        end
    end
endmodule
