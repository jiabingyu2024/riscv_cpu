import BasicTypes::*;

package ROBTypes;

    typedef logic [ROB_DEPTH_WIDTH-1:0] RobFreeCountPath;

    typedef struct packed {
        logic               valid;
        logic               done;
        PcPath              pc;

        logic               DstValid;
        LgcRegNumPath       lgcRegNum;
        PhyRegNumPath       phyRegNum;
        PhyRegNumPath       phyPrevRegNum;

        logic               isBranch;
        logic               takenPred;
        logic               isMiss;
        PcPath              truePc;
        ChkptIndexPath      specRATChkptIndex;
        ChkptIndexPath      freeListChkptIndex;

        logic               isSerial;
        logic               exception;
    } RobEntryPath;

    typedef struct packed {
        RobIndexPath robIndex;
        logic        position;
        logic        valid;
    } RobPushResPath;

    typedef struct packed {
        RobEntryPath entry;
        logic        req;
    } RobPushReqPath;

    typedef struct packed {
        logic req;
    } RobPopReqPath;

    typedef struct packed {
        RobEntryPath entry;
        logic        valid;
    } RobPopResPath;

    typedef struct packed {
        logic        valid;
        RobIndexPath robIndex;
        logic        isSerial;
        logic        exception;
        PcPath       trueTargetPc;
        logic        taken;
    } RobDoneReqPath;

endpackage : ROBTypes
