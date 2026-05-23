import BasicTypes::*;
import PipelineTypes::*;
import ROBTypes::*;
import RenameTypes::*;
import RecoveryTypes::*;
import StoreBufferTypes::*;

module CommitStage(
    CommitStageIf.CommitStage self,
    RecoveryManagerIF.CommitStage recovery,
    CtrlIF.CommitStage ctrl,
    ArchRATIF.CommitStage archRAT,
    SpecRATIF.CommitStage specRAT,
    FreeListIF.CommitStage freeList,
    StoreBufferIF.CommitStage storeBuffer,
    ROBIF.CommitStage rob
);
    always_comb begin
        recovery.commitRecoveryReq = '0;
        ctrl.serialBlock = 1'b0;
        storeBuffer.StoreBufferPopReq = '0;

        for (int i = 0; i < WAY_NUM; i++) begin
            rob.RobPopReq[i].req = 1'b0;
            archRAT.archRATUpdate[i] = '0;
            specRAT.specRATUpdate[i] = '0;
            freeList.freeListFree[i] = '0;
            self.commitValid[i] = 1'b0;
            self.commitPc[i] = '0;
        end
        specRAT.specRATChkptFree = '0;
        freeList.freeListChkptFree = '0;
        self.commitException = 1'b0;
        self.commitBranchMiss = 1'b0;

        for (int i = 0; i < WAY_NUM; i++) begin
            if (rob.RobPopRes[i].valid && rob.RobPopRes[i].entry.done &&
                !recovery.commitRecoveryReq.valid) begin
                self.commitValid[i] = 1'b1;
                self.commitPc[i] = rob.RobPopRes[i].entry.pc;

                if (rob.RobPopRes[i].entry.exception) begin
                    self.commitException = 1'b1;
                    recovery.commitRecoveryReq.valid = 1'b1;
                    recovery.commitRecoveryReq.cause = REC_EXCEPTION;
                    recovery.commitRecoveryReq.recoverPc = 32'h8000_0100;
                    recovery.commitRecoveryReq.frontendFlush = 1'b1;
                    recovery.commitRecoveryReq.backendFlush = 1'b1;
                end else if (rob.RobPopRes[i].entry.isMiss) begin
                    self.commitBranchMiss = 1'b1;
                    recovery.commitRecoveryReq.valid = 1'b1;
                    recovery.commitRecoveryReq.cause = REC_BRANCH_MISS;
                    recovery.commitRecoveryReq.recoverPc = rob.RobPopRes[i].entry.truePc;
                    recovery.commitRecoveryReq.specRATChkptIndex = rob.RobPopRes[i].entry.specRATChkptIndex;
                    recovery.commitRecoveryReq.freeListChkptIndex = rob.RobPopRes[i].entry.freeListChkptIndex;
                    recovery.commitRecoveryReq.chkptRecoverEn = 1'b1;
                    recovery.commitRecoveryReq.frontendFlush = 1'b1;
                    recovery.commitRecoveryReq.backendFlush = 1'b1;
                end else begin
                    rob.RobPopReq[i].req = 1'b1;
                    archRAT.archRATUpdate[i].UpdateEn = rob.RobPopRes[i].entry.DstValid;
                    archRAT.archRATUpdate[i].UpdateLgcRegNum = rob.RobPopRes[i].entry.lgcRegNum;
                    archRAT.archRATUpdate[i].UpdatePhyRegNum = rob.RobPopRes[i].entry.phyRegNum;
                    specRAT.specRATUpdate[i] = archRAT.archRATUpdate[i];
                    freeList.freeListFree[i].freeReq = rob.RobPopRes[i].entry.DstValid;
                    freeList.freeListFree[i].freePhyRegNum = rob.RobPopRes[i].entry.phyPrevRegNum;
                end
            end else if (rob.RobPopRes[i].valid && rob.RobPopRes[i].entry.isSerial &&
                         !rob.RobPopRes[i].entry.done) begin
                ctrl.serialBlock = 1'b1;
            end
        end
    end
endmodule
