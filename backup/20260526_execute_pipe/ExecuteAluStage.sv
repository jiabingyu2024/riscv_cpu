import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;

module ExecuteAluStage(
    ReadRegStageIF.ExecuteAluStage prev,
    ExecuteStageIF.ExecuteAluStage self,
    CtrlIF.ExecuteStage ctrl,
    BypassIF.ExecuteAluStage bypass
);
    function automatic DataPath alu(input SubTypePath st, input DataPath a, input DataPath b);
        unique case (st.aluSubType)
            ALU_SUBTYPE_SUB: alu = a - b;
            ALU_SUBTYPE_SLL: alu = a << b[4:0];
            ALU_SUBTYPE_SRL: alu = a >> b[4:0];
            ALU_SUBTYPE_SRA: alu = DataPath'($signed(a) >>> b[4:0]);
            ALU_SUBTYPE_XOR: alu = a ^ b;
            ALU_SUBTYPE_OR:  alu = a | b;
            ALU_SUBTYPE_AND: alu = a & b;
            default:         alu = a + b;
        endcase
    endfunction

    always_comb begin
        ctrl.exStallReq = 1'b0;
        ctrl.exStageEmpty = 1'b1;
        for (int i = 0; i < BYPASS_READ_PORT_NUM; i++) begin
            bypass.aluReadReq[i] = '0;
        end
        for (int i = 0; i < WAY_NUM; i++) begin
            DataPath a;
            DataPath b;
            bypass.aluReadReq[i*2+0].valid = prev.nextToAluStage[i].valid && prev.nextToAluStage[i].srcAIsRs1;
            bypass.aluReadReq[i*2+0].phyRegNum = prev.nextToAluStage[i].Rs1;
            bypass.aluReadReq[i*2+1].valid = prev.nextToAluStage[i].valid && prev.nextToAluStage[i].srcBIsRs2;
            bypass.aluReadReq[i*2+1].phyRegNum = prev.nextToAluStage[i].Rs2;
            a = bypass.aluReadRes[i*2+0].hit ? bypass.aluReadRes[i*2+0].data : prev.nextToAluStage[i].dataA;
            b = bypass.aluReadRes[i*2+1].hit ? bypass.aluReadRes[i*2+1].data : prev.nextToAluStage[i].dataB;

            self.nextAluToStage[i].valid = prev.nextToAluStage[i].valid && !ctrl.exPipe.flush;
            self.nextAluToStage[i].Rd = prev.nextToAluStage[i].Rd;
            self.nextAluToStage[i].writeRd = prev.nextToAluStage[i].writeRd;
            self.nextAluToStage[i].data = alu(prev.nextToAluStage[i].subType, a, b);
            self.nextAluToStage[i].robIndex = prev.nextToAluStage[i].robIndex;
            ctrl.exStageEmpty &= !self.nextAluToStage[i].valid;
        end
    end
endmodule
