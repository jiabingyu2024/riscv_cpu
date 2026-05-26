import BasicTypes::*;
import PipelineTypes::*;
import IssueTypes::*;
import ROBTypes::*;
import StoreBufferTypes::*;

module DispatchStage(
    RenameStageIF.DispatchStage prev,
    DispatchStageIF.DispatchStage self,
    IssueQueueIF.DispatchStage issueQueue,
    PayloadIF.DispatchStage payload,
    CtrlIF.DispatchStage ctrl,
    ROBIF.DispatchStage rob,
    StoreBufferIF.DispatchStage storeBuffer
);
    always_comb begin
        int storeCount;
        logic storeBlock;

        ctrl.dsStageEmpty = 1'b1;
        ctrl.dsStallReq = 1'b0;
        ctrl.robFull = (rob.RobFreeCount < WAY_NUM);
        ctrl.issueQueueFull = (issueQueue.IssueFreeCount < WAY_NUM);
        storeBuffer.allocReq = 1'b0;
        storeCount = 0;

        for (int i = 0; i < WAY_NUM; i++) begin
            if (prev.nextStage[i].valid &&
                prev.nextStage[i].instInfo.tubeType == TUBE_TYPE_MEM &&
                (prev.nextStage[i].instInfo.SubType.memSubType inside
                    {MEM_SUBTYPE_SB, MEM_SUBTYPE_SH, MEM_SUBTYPE_SW})) begin
                storeCount++;
            end
        end

        storeBlock = (storeCount != 0 && !storeBuffer.allocRdy) || (storeCount > 1);
        storeBuffer.allocReq = (storeCount != 0) && !ctrl.dsPipe.stall && !storeBlock;

        for (int i = 0; i < WAY_NUM; i++) begin
            logic isStore;
            isStore = prev.nextStage[i].instInfo.tubeType == TUBE_TYPE_MEM &&
                      (prev.nextStage[i].instInfo.SubType.memSubType inside
                        {MEM_SUBTYPE_SB, MEM_SUBTYPE_SH, MEM_SUBTYPE_SW});

            self.nextStage[i].valid = prev.nextStage[i].valid && !ctrl.dsPipe.flush && !ctrl.dsPipe.stall;

            rob.RobPushReq[i].req = prev.nextStage[i].valid && !ctrl.dsPipe.stall;
            rob.RobPushReq[i].entry = '0;
            rob.RobPushReq[i].entry.valid = prev.nextStage[i].valid;
            rob.RobPushReq[i].entry.done = 1'b0;
            rob.RobPushReq[i].entry.pc = prev.nextStage[i].pc;
            rob.RobPushReq[i].entry.DstValid = prev.nextStage[i].phyRegInfo.PhyRegNumDstValid;
            rob.RobPushReq[i].entry.lgcRegNum = prev.nextStage[i].lgcRegInfo.lgcRegNumDst;
            rob.RobPushReq[i].entry.phyRegNum = prev.nextStage[i].phyRegInfo.PhyRegNumDst;
            rob.RobPushReq[i].entry.phyPrevRegNum = prev.nextStage[i].phyPrevDst;
            rob.RobPushReq[i].entry.isBranch = prev.nextStage[i].instInfo.tubeType == TUBE_TYPE_BRC;
            rob.RobPushReq[i].entry.takenPred = prev.nextStage[i].predInfo.isPred;
            rob.RobPushReq[i].entry.predPc = prev.nextStage[i].predInfo.pcPred;
            rob.RobPushReq[i].entry.truePc = prev.nextStage[i].predInfo.pcPred;
            rob.RobPushReq[i].entry.specRATChkptIndex = prev.nextStage[i].specRATChkptIndex;
            rob.RobPushReq[i].entry.freeListChkptIndex = prev.nextStage[i].freeListChkptIndex;
            rob.RobPushReq[i].entry.isStore = isStore;
            rob.RobPushReq[i].entry.storeBufferIndex = storeBuffer.allocIndex;
            rob.RobPushReq[i].entry.isSerial = prev.nextStage[i].instInfo.isSerial;
            rob.RobPushReq[i].entry.exception = 1'b0;

            issueQueue.IssuePushReq[i].valid = prev.nextStage[i].valid && !ctrl.dsPipe.stall &&
                                               rob.RobPushRes[i].valid;
            issueQueue.IssuePushReq[i].entry = '0;
            issueQueue.IssuePushReq[i].entry.tubeType = prev.nextStage[i].instInfo.tubeType;
            issueQueue.IssuePushReq[i].entry.srcA = prev.nextStage[i].phyRegInfo.PhyRegNumSrcA;
            issueQueue.IssuePushReq[i].entry.srcB = prev.nextStage[i].phyRegInfo.PhyRegNumSrcB;
            issueQueue.IssuePushReq[i].entry.srcARdy = !prev.nextStage[i].phyRegInfo.PhyRegNumSrcAValid;
            issueQueue.IssuePushReq[i].entry.srcBRdy = !prev.nextStage[i].phyRegInfo.PhyRegNumSrcBValid;
            issueQueue.IssuePushReq[i].entry.srcBIsImm = prev.nextStage[i].instInfo.opTypeB == OP_TYPE_IMM ||
                                                         prev.nextStage[i].instInfo.opTypeB == OP_TYPE_NONE;
            issueQueue.IssuePushReq[i].entry.dst = prev.nextStage[i].phyRegInfo.PhyRegNumDst;
            issueQueue.IssuePushReq[i].entry.writeDst = prev.nextStage[i].phyRegInfo.PhyRegNumDstValid;
            issueQueue.IssuePushReq[i].entry.delay = delay_for(prev.nextStage[i].instInfo.tubeType,
                                                               prev.nextStage[i].instInfo.SubType);
            issueQueue.IssuePushReq[i].entry.robIndex = rob.RobPushRes[i].robIndex;
            issueQueue.IssuePushReq[i].entry.robIndexPosition = rob.RobPushRes[i].position;

            payload.PayloadPushReq[i].valid = issueQueue.IssuePushReq[i].valid &&
                                              issueQueue.IssuePushRes[i].done;
            payload.PayloadPushReq[i].payloadIndex = issueQueue.IssuePushRes[i].payloadIndex;
            payload.PayloadPushReq[i].entry.pc = prev.nextStage[i].pc;
            payload.PayloadPushReq[i].entry.predInfo = prev.nextStage[i].predInfo;
            payload.PayloadPushReq[i].entry.csrAddr = prev.nextStage[i].csrAddr;
            payload.PayloadPushReq[i].entry.SubType = prev.nextStage[i].instInfo.SubType;
            payload.PayloadPushReq[i].entry.opTypeA = prev.nextStage[i].instInfo.opTypeA;
            payload.PayloadPushReq[i].entry.opTypeB = prev.nextStage[i].instInfo.opTypeB;
            payload.PayloadPushReq[i].entry.imm = prev.nextStage[i].imm;
            payload.PayloadPushReq[i].entry.storeBufferIndexValid = isStore;
            payload.PayloadPushReq[i].entry.storeBufferIndex = storeBuffer.allocIndex;

            ctrl.dsStageEmpty &= !self.nextStage[i].valid;
        end

        issueQueue.IssueCtrl.flush = ctrl.dsPipe.flush;
        ctrl.dsStallReq = ctrl.robFull | ctrl.issueQueueFull | storeBlock;
    end

    function automatic ShiftType delay_for(input TubeTypePath tube, input SubTypePath subtype);
        int cycles;
        cycles = 1;
        unique case (tube)
            TUBE_TYPE_MUL: cycles = (subtype.mulSubType inside {MUL_SUBTYPE_DIV, MUL_SUBTYPE_DIVU,
                                                                 MUL_SUBTYPE_REM, MUL_SUBTYPE_REMU}) ? 36 : 3;
            TUBE_TYPE_MEM: cycles = 3;
            default:       cycles = 1;
        endcase
        delay_for = ShiftType'(1) << (cycles - 1);
    endfunction
endmodule
