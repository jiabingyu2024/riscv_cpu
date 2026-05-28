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
    ROBIF.CommitStage rob,
    DramAccessIF.core dram
);
    always_comb begin
        logic stopCommit;

        recovery.commitRecoveryReq = '0;
        recovery.commitBranchUpdateValid = 1'b0;
        recovery.commitBranchPc = '0;
        recovery.commitBranchTaken = 1'b0;
        recovery.commitBranchTarget = '0;
        ctrl.serialBlock = 1'b0;
        storeBuffer.StoreBufferPopReq = '0;
        storeBuffer.flush = 1'b0;
        rob.RobFlush = 1'b0;

        dram.req = 1'b0;
        dram.we = 1'b0;
        dram.addr = '0;
        dram.wdata = '0;
        dram.wstrb = '0;

        for (int i = 0; i < WAY_NUM; i++) begin
            rob.RobPopReq[i].req = 1'b0;
            archRAT.archRATUpdate[i] = '0;
            freeList.freeListFree[i] = '0;
            self.commitValid[i] = 1'b0;
            self.commitPc[i] = '0;
        end
        specRAT.specRATChkptFree = '0;
        freeList.freeListChkptFree = '0;
        self.commitException = 1'b0;
        self.commitBranchMiss = 1'b0;
        stopCommit = 1'b0;

        for (int i = 0; i < WAY_NUM; i++) begin
            if (!stopCommit && rob.RobPopRes[i].valid) begin
                if (!rob.RobPopRes[i].entry.done) begin
                    stopCommit = 1'b1;
                    if (rob.RobPopRes[i].entry.isSerial) begin
                        ctrl.serialBlock = 1'b1;
                    end
                end else begin
                    self.commitPc[i] = rob.RobPopRes[i].entry.pc;

                    if (rob.RobPopRes[i].entry.isBranch &&
                        !recovery.commitBranchUpdateValid) begin
                        recovery.commitBranchUpdateValid = 1'b1;
                        recovery.commitBranchPc = rob.RobPopRes[i].entry.pc;
                        recovery.commitBranchTaken = rob.RobPopRes[i].entry.isMiss ?
                                                     !rob.RobPopRes[i].entry.takenPred :
                                                     rob.RobPopRes[i].entry.takenPred;
                        recovery.commitBranchTarget = rob.RobPopRes[i].entry.truePc;
                    end

                    if (rob.RobPopRes[i].entry.exception) begin
                        self.commitException = 1'b1;
                        recovery.commitRecoveryReq.valid = 1'b1;
                        recovery.commitRecoveryReq.cause = REC_EXCEPTION;
                        recovery.commitRecoveryReq.recoverPc = 32'h8000_0100;
                        recovery.commitRecoveryReq.frontendFlush = 1'b1;
                        recovery.commitRecoveryReq.backendFlush = 1'b1;
                        rob.RobFlush = 1'b1;
                        storeBuffer.flush = 1'b1;
                        stopCommit = 1'b1;
                    end else if (rob.RobPopRes[i].entry.isMiss) begin
                        self.commitValid[i] = 1'b1;
                        archRAT.archRATUpdate[i].UpdateEn = rob.RobPopRes[i].entry.DstValid;
                        archRAT.archRATUpdate[i].UpdateLgcRegNum = rob.RobPopRes[i].entry.lgcRegNum;
                        archRAT.archRATUpdate[i].UpdatePhyRegNum = rob.RobPopRes[i].entry.phyRegNum;
                        freeList.freeListFree[i].freeReq = rob.RobPopRes[i].entry.DstValid;
                        freeList.freeListFree[i].freePhyRegNum = rob.RobPopRes[i].entry.phyPrevRegNum;
                        self.commitBranchMiss = 1'b1;
                        recovery.commitRecoveryReq.valid = 1'b1;
                        recovery.commitRecoveryReq.cause = REC_BRANCH_MISS;
                        recovery.commitRecoveryReq.recoverPc = rob.RobPopRes[i].entry.truePc;
                        recovery.commitRecoveryReq.specRATChkptIndex = rob.RobPopRes[i].entry.specRATChkptIndex;
                        recovery.commitRecoveryReq.freeListChkptIndex = rob.RobPopRes[i].entry.freeListChkptIndex;
                        recovery.commitRecoveryReq.chkptRecoverEn = 1'b1;
                        recovery.commitRecoveryReq.frontendFlush = 1'b1;
                        recovery.commitRecoveryReq.backendFlush = 1'b1;
                        rob.RobFlush = 1'b1;
                        storeBuffer.flush = 1'b1;
                        stopCommit = 1'b1;
                    end else if (rob.RobPopRes[i].entry.isStore) begin
                        if (storeBuffer.StoreBufferCommit.valid &&
                            storeBuffer.StoreBufferCommit.index == rob.RobPopRes[i].entry.storeBufferIndex &&
                            dram.ready) begin
                            dram.req = 1'b1;
                            dram.we = 1'b1;
                            dram.addr = storeBuffer.StoreBufferCommit.addr;
                            dram.wdata = storeBuffer.StoreBufferCommit.data;
                            dram.wstrb = storeBuffer.StoreBufferCommit.wstrb;

                            storeBuffer.StoreBufferPopReq.valid = 1'b1;
                            storeBuffer.StoreBufferPopReq.index = rob.RobPopRes[i].entry.storeBufferIndex;
                            rob.RobPopReq[i].req = 1'b1;
                            self.commitValid[i] = 1'b1;
                        end
                        stopCommit = 1'b1;
                    end else begin
                        rob.RobPopReq[i].req = 1'b1;
                        self.commitValid[i] = 1'b1;

                        archRAT.archRATUpdate[i].UpdateEn = rob.RobPopRes[i].entry.DstValid;
                        archRAT.archRATUpdate[i].UpdateLgcRegNum = rob.RobPopRes[i].entry.lgcRegNum;
                        archRAT.archRATUpdate[i].UpdatePhyRegNum = rob.RobPopRes[i].entry.phyRegNum;
                        freeList.freeListFree[i].freeReq = rob.RobPopRes[i].entry.DstValid;
                        freeList.freeListFree[i].freePhyRegNum = rob.RobPopRes[i].entry.phyPrevRegNum;

                        if (rob.RobPopRes[i].entry.isBranch) begin
                            specRAT.specRATChkptFree.ChkptFreeEn = 1'b1;
                            specRAT.specRATChkptFree.ChkptFreeIndex =
                                rob.RobPopRes[i].entry.specRATChkptIndex;
                            freeList.freeListChkptFree.ChkptFreeEn = 1'b1;
                            freeList.freeListChkptFree.ChkptFreeIndex =
                                rob.RobPopRes[i].entry.freeListChkptIndex;
                        end
                    end
                end
            end
        end
    end
endmodule
