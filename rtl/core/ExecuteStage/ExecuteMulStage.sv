import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;

module ExecuteMulStage(
    ReadRegStageIF.ExecuteMulStage prev,
    ExecuteStageIF.ExecuteMulStage self,
    CtrlIF.ExecuteStage ctrl,
    BypassIF.ExecuteMulStage bypass
);
    function automatic DataPath muldiv(input SubTypePath st, input DataPath a, input DataPath b);
        unique case (st.mulSubType)
            MUL_SUBTYPE_MUL:  muldiv = a * b;
            MUL_SUBTYPE_DIV:  muldiv = (b == 0) ? 32'hffff_ffff : DataPath'($signed(a) / $signed(b));
            MUL_SUBTYPE_DIVU: muldiv = (b == 0) ? 32'hffff_ffff : a / b;
            MUL_SUBTYPE_REM:  muldiv = (b == 0) ? a : DataPath'($signed(a) % $signed(b));
            MUL_SUBTYPE_REMU: muldiv = (b == 0) ? a : a % b;
            default:          muldiv = a * b;
        endcase
    endfunction

    always_comb begin
        for (int i = 0; i < BYPASS_READ_PORT_NUM; i++) bypass.mulReadReq[i] = '0;
        for (int i = 0; i < WAY_NUM; i++) begin
            DataPath a;
            DataPath b;
            bypass.mulReadReq[i*2+0].valid = prev.nextToMulStage[i].valid && prev.nextToMulStage[i].srcAIsRs1;
            bypass.mulReadReq[i*2+0].phyRegNum = prev.nextToMulStage[i].Rs1;
            bypass.mulReadReq[i*2+1].valid = prev.nextToMulStage[i].valid && prev.nextToMulStage[i].srcBIsRs2;
            bypass.mulReadReq[i*2+1].phyRegNum = prev.nextToMulStage[i].Rs2;
            a = bypass.mulReadRes[i*2+0].hit ? bypass.mulReadRes[i*2+0].data : prev.nextToMulStage[i].dataA;
            b = bypass.mulReadRes[i*2+1].hit ? bypass.mulReadRes[i*2+1].data : prev.nextToMulStage[i].dataB;
            self.nextMulToStage[i].valid = prev.nextToMulStage[i].valid && !ctrl.exPipe.flush;
            self.nextMulToStage[i].Rd = prev.nextToMulStage[i].Rd;
            self.nextMulToStage[i].writeRd = prev.nextToMulStage[i].writeRd;
            self.nextMulToStage[i].data = muldiv(prev.nextToMulStage[i].subType, a, b);
            self.nextMulToStage[i].robIndex = prev.nextToMulStage[i].robIndex;
        end
    end
endmodule
