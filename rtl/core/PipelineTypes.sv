

import BasicTypes::*;



package PipelineTypes;

    //ctrl
    typedef struct packed {
        logic stall;
        logic flush;
    } PipeCtrl;

    // PF to IF
    typedef struct packed {
        PcPath pcPred; // 来自分支预测器的预测PC地址
        logic  isPred;
    } PredInfo;
    typedef struct packed {
        PcPath pc;
        PredInfo predInfo;
        logic  valid;
    } PfToIfPath;

    //IF to ID
    typedef struct packed {
        PcPath pc;
        InstPath inst;
        logic  valid;
        PredInfo predInfo; 
    } IfToIdPath;

    // ID to RN

    typedef struct packed {
        logic valid;
        logic isSerial;

        logic writeReg;

        TubeTypePath tubeType;
        SubTypePath  SubType;

        OperandTypePath opTypeA;
        OperandTypePath opTypeB;

    } InstInfoPath;

    typedef struct packed {
        logic         lgcRegNumSrcAValid;
        logic         lgcRegNumSrcBValid;
        logic         lgcRegNumDstValid;
        LgcRegNumPath lgcRegNumSrcA;
        LgcRegNumPath lgcRegNumSrcB;
        LgcRegNumPath lgcRegNumDst;

    } LgcRegInfoPath;

    typedef struct packed {
        logic         PhyRegNumSrcAValid;
        logic         PhyRegNumSrcBValid;
        logic         PhyRegNumDstValid;
        PhyRegNumPath PhyRegNumSrcA;
        PhyRegNumPath PhyRegNumSrcB;
        PhyRegNumPath PhyRegNumDst;
    } PhyRegInfoPath;




    typedef struct packed {
        logic  valid;
        PcPath pc;
        InstPath inst;
        PredInfoPath predInfo;

        LgcRegInfoPath   lgcRegInfo;
        CsrAddrPath      csrAddr;
        InstInfoPath     instInfo;
        DataPath         imm;
    } IdToRnPath;    


    //RN To DS  
    typedef struct packed {
        logic valid;
        PcPath pc;
        PredInfoPath predInfo;
        
        CsrAddrPath      csrAddr;
        InstInfoPath     instInfo;
        DataPath         imm;
        PhyRegInfoPath   phyRegInfo;
        
    } RnToDsPath;

    //DS to IS
    typedef struct packed {
        logic valid;
        PcPath pc;
        PredInfoPath predInfo;
        
        CsrAddrPath      csrAddr;
        DataPath         imm;
    } DsToIsPath;

    //ROB 
    localparam ROB_DEPTH = 16;
    localparam ROB_DEPTH_WIDTH =  $clog2(ROB_DEPTH);

    typedef logic [ROB_DEPTH_WIDTH-1:0] RobFreeCountPath;

    typedef logic [ROB_DEPTH_WIDTH-1:0] RobIndexPath;
    typedef struct packed {
        RobIndexPath robIndex;
        logic    position;
        logic    valid;
    }RobPushResPath;

    typedef struct packed {
        RobEntryPath entry;
        logic        req;
    }RobPushReqPath;

    typedef struct packed {
        RobEntryPath entry;
        logic        valid;
    }RobPopResPath;

    typedef struct packed {
        logic  valid;
        RobIndexPath robIndex;
    }RobDoneReqPath;

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
        ChkptIndexPath      chkptIndex; 

        logic               isSerial;
        logic               exception;
        
    } RobEntryPath;


endpackage PipelineTypes;