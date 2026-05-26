import BasicTypes::*;
import PipelineTypes::*;
import ReadRegTypes::*;

module RegReadStage(
    IssueStageIF.ReadRegStage prev,
    ReadRegStageIF.ReadRegStage self,
    RegFileIF.ReadRegStage regFile,
    CtrlIF.ReadRegStage ctrl
);
    always_comb begin
        ctrl.rrStallReq = 1'b0;
        ctrl.rrStageEmpty = 1'b1;

        for (int i = 0; i < REGFILE_READ_PORT_NUM; i++) begin
            regFile.regFileReadReq[i] = '0;
        end

        for (int i = 0; i < WAY_NUM; i++) begin
            int rp;
            DataPath dataA;
            DataPath dataB;

            rp = i * 2;
            regFile.regFileReadReq[rp + 0].enaRead = prev.nextStage[i].valid;
            regFile.regFileReadReq[rp + 0].regIndex = prev.nextStage[i].srcA;
            regFile.regFileReadReq[rp + 1].enaRead = prev.nextStage[i].valid;
            regFile.regFileReadReq[rp + 1].regIndex = prev.nextStage[i].srcB;

            unique case (prev.nextStage[i].opTypeA)
                OP_TYPE_PC:  dataA = prev.nextStage[i].pc;
                OP_TYPE_IMM: dataA = prev.nextStage[i].imm;
                default:     dataA = regFile.regFileReadRes[rp + 0].data;
            endcase
            unique case (prev.nextStage[i].opTypeB)
                OP_TYPE_IMM: dataB = prev.nextStage[i].imm;
                OP_TYPE_PC:  dataB = prev.nextStage[i].pc;
                default:     dataB = regFile.regFileReadRes[rp + 1].data;
            endcase

            self.nextToAluStage[i] = '0;
            self.nextToMemStage[i] = '0;
            self.nextToMulStage[i] = '0;
            self.nextToBrcStage[i] = '0;
            self.nextToSysStage[i] = '0;

            unique case (prev.nextStage[i].tubeType)
                TUBE_TYPE_ALU: begin
                    self.nextToAluStage[i].valid = prev.nextStage[i].valid && !ctrl.rrPipe.flush;
                    self.nextToAluStage[i].subType = prev.nextStage[i].SubType;
                    self.nextToAluStage[i].dataA = dataA;
                    self.nextToAluStage[i].dataB = dataB;
                    self.nextToAluStage[i].Rs1 = prev.nextStage[i].srcA;
                    self.nextToAluStage[i].Rs2 = prev.nextStage[i].srcB;
                    self.nextToAluStage[i].srcAIsRs1 = prev.nextStage[i].opTypeA == OP_TYPE_REG;
                    self.nextToAluStage[i].srcBIsRs2 = prev.nextStage[i].opTypeB == OP_TYPE_REG;
                    self.nextToAluStage[i].Rd = prev.nextStage[i].dst;
                    self.nextToAluStage[i].writeRd = prev.nextStage[i].writeDst;
                    self.nextToAluStage[i].robIndex = prev.nextStage[i].robIndex;
                end
                TUBE_TYPE_MEM: begin
                    self.nextToMemStage[i].valid = prev.nextStage[i].valid && !ctrl.rrPipe.flush;
                    self.nextToMemStage[i].subType = prev.nextStage[i].SubType;
                    self.nextToMemStage[i].dataA = dataA;
                    self.nextToMemStage[i].dataB = dataB;
                    self.nextToMemStage[i].Rs1 = prev.nextStage[i].srcA;
                    self.nextToMemStage[i].Rs2 = prev.nextStage[i].srcB;
                    self.nextToMemStage[i].srcAIsRs1 = prev.nextStage[i].opTypeA == OP_TYPE_REG;
                    self.nextToMemStage[i].srcBIsRs2 = prev.nextStage[i].opTypeB == OP_TYPE_REG;
                    self.nextToMemStage[i].imm = prev.nextStage[i].imm;
                    self.nextToMemStage[i].Rd = prev.nextStage[i].dst;
                    self.nextToMemStage[i].writeRd = prev.nextStage[i].writeDst;
                    self.nextToMemStage[i].robIndex = prev.nextStage[i].robIndex;
                    self.nextToMemStage[i].storeBufferIndexValid = prev.nextStage[i].storeBufferIndexValid;
                    self.nextToMemStage[i].storeBufferIndex = prev.nextStage[i].storeBufferIndex;
                end
                TUBE_TYPE_MUL: begin
                    self.nextToMulStage[i].valid = prev.nextStage[i].valid && !ctrl.rrPipe.flush;
                    self.nextToMulStage[i].subType = prev.nextStage[i].SubType;
                    self.nextToMulStage[i].dataA = dataA;
                    self.nextToMulStage[i].dataB = dataB;
                    self.nextToMulStage[i].Rs1 = prev.nextStage[i].srcA;
                    self.nextToMulStage[i].Rs2 = prev.nextStage[i].srcB;
                    self.nextToMulStage[i].srcAIsRs1 = prev.nextStage[i].opTypeA == OP_TYPE_REG;
                    self.nextToMulStage[i].srcBIsRs2 = prev.nextStage[i].opTypeB == OP_TYPE_REG;
                    self.nextToMulStage[i].Rd = prev.nextStage[i].dst;
                    self.nextToMulStage[i].writeRd = prev.nextStage[i].writeDst;
                    self.nextToMulStage[i].robIndex = prev.nextStage[i].robIndex;
                end
                TUBE_TYPE_BRC: begin
                    self.nextToBrcStage[i].valid = prev.nextStage[i].valid && !ctrl.rrPipe.flush;
                    self.nextToBrcStage[i].subType = prev.nextStage[i].SubType;
                    self.nextToBrcStage[i].dataA = dataA;
                    self.nextToBrcStage[i].dataB = dataB;
                    self.nextToBrcStage[i].Rs1 = prev.nextStage[i].srcA;
                    self.nextToBrcStage[i].Rs2 = prev.nextStage[i].srcB;
                    self.nextToBrcStage[i].srcAIsRs1 = prev.nextStage[i].opTypeA == OP_TYPE_REG;
                    self.nextToBrcStage[i].srcBIsRs2 = prev.nextStage[i].opTypeB == OP_TYPE_REG;
                    self.nextToBrcStage[i].pc = prev.nextStage[i].pc;
                    self.nextToBrcStage[i].imm = prev.nextStage[i].imm;
                    self.nextToBrcStage[i].Rd = prev.nextStage[i].dst;
                    self.nextToBrcStage[i].writeRd = prev.nextStage[i].writeDst;
                    self.nextToBrcStage[i].robIndex = prev.nextStage[i].robIndex;
                end
                default: begin
                    self.nextToSysStage[i].valid = prev.nextStage[i].valid && !ctrl.rrPipe.flush;
                    self.nextToSysStage[i].subType = prev.nextStage[i].SubType;
                    self.nextToSysStage[i].dataA = dataA;
                    self.nextToSysStage[i].Rs1 = prev.nextStage[i].srcA;
                    self.nextToSysStage[i].srcAIsRs1 = prev.nextStage[i].opTypeA == OP_TYPE_REG;
                    self.nextToSysStage[i].csrAddr = prev.nextStage[i].csrAddr;
                    self.nextToSysStage[i].Rd = prev.nextStage[i].dst;
                    self.nextToSysStage[i].writeRd = prev.nextStage[i].writeDst;
                    self.nextToSysStage[i].robIndex = prev.nextStage[i].robIndex;
                end
            endcase

            ctrl.rrStageEmpty &= !prev.nextStage[i].valid;
        end
    end
endmodule
