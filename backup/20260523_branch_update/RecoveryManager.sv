import BasicTypes::*;
import RecoveryTypes::*;
import RenameTypes::*;

module RecoveryManager(
    RecoveryManagerIF.RecoveryManager self,
    CtrlIF.CtrlUnit ctrl,
    SpecRATIF.RecoveryManager specRAT,
    FreeListIF.RecoveryManager freeList
);
    always_comb begin
        self.recoveryInfo = '0;
        if (self.commitRecoveryReq.valid) begin
            self.recoveryInfo = self.commitRecoveryReq;
        end else if (self.writeBackRecoveryReq.valid) begin
            self.recoveryInfo = self.writeBackRecoveryReq;
        end

        self.pcUpdateEn = self.recoveryInfo.valid;
        self.pcUpdate = self.recoveryInfo.recoverPc;

        self.branchUpdateValid = self.recoveryInfo.valid &&
                                 self.recoveryInfo.cause == REC_BRANCH_MISS;
        self.branchPc = '0;
        self.branchTaken = 1'b0;
        self.branchTarget = self.recoveryInfo.recoverPc;
        self.branchMiss = self.branchUpdateValid;

        specRAT.specRATChkptRecover.ChkptRecoverEn = self.recoveryInfo.valid &&
                                                     self.recoveryInfo.chkptRecoverEn;
        specRAT.specRATChkptRecover.ChkptRecoverIndex = self.recoveryInfo.specRATChkptIndex;

        freeList.freeListChkptRecover.ChkptRecoverEn = self.recoveryInfo.valid &&
                                                       self.recoveryInfo.chkptRecoverEn;
        freeList.freeListChkptRecover.ChkptRecoverIndex = self.recoveryInfo.freeListChkptIndex;
    end
endmodule
