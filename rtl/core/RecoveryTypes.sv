import BasicTypes::*;

package RecoveryTypes;

    typedef enum logic [2:0] {
        REC_NONE,
        REC_BRANCH_MISS,
        REC_EXCEPTION,
        REC_REPLAY,
        REC_SERIAL
    } RecoveryCausePath;

    typedef struct packed {
        logic             valid;
        RecoveryCausePath cause;
        PcPath            recoverPc;
        ChkptIndexPath    specRATChkptIndex;
        ChkptIndexPath    freeListChkptIndex;
        logic             chkptRecoverEn;
        logic             frontendFlush;
        logic             backendFlush;
    } RecoveryReqPath;

endpackage : RecoveryTypes
