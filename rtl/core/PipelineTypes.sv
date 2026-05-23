

import BasicTypes::*;



package PipelineTypes;

    //ctrl
    typedef struct packed {
        logic stall;
        logic flush;
    } PipeCtrlPath;

    // PF to IF
    typedef struct packed {
        PcPath pcPred; // 来自分支预测器的预测PC地址
        logic  isPred;
    } PredInfoPath;
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
        PredInfoPath predInfo; 
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
        logic        isSerial;
        logic        exception;
        PcPath       trueTargetPc;
        logic        taken;
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
        ChkptIndexPath      specRATChkptIndex; 
        ChkptIndexPath      freeListChkptIndex;

        logic               isSerial;
        logic               exception;
        
    } RobEntryPath;

    //DS to IS
    typedef struct packed {
        logic valid;
        // PcPath pc;
        // PredInfoPath predInfo;
        
        // CsrAddrPath      csrAddr;
        // DataPath         imm;
    } DsToIsPath;

    // IS to RR
    typedef struct packed {
        logic valid;
        PayloadEntryPath payloadEntry;
        IssueEntryPath   issueEntry;

    } IsToRrPath;


    typedef struct packed {
        logic valid;
        SubTypePath subType;

        DataPath dataA;
        DataPath dataB;
        PhyRegNumPath Rs1;
        PhyRegNumPath Rs2;
        logic         srcAIsRs1;
        logic         srcBIsRs2;

        PhyRegNumPath Rd;
        logic         writeRd;

        RobIndexPath robIndex;

    }RrToExAluPath;

    typedef struct packed {
        logic valid;
        SubTypePath subType;

        DataPath dataA;
        DataPath dataB;
        PhyRegNumPath Rs1;
        PhyRegNumPath Rs2;
        logic         srcAIsRs1;
        logic         srcBIsRs2;

        DataPath      imm;

        PhyRegNumPath Rd;
        logic         writeRd;

        RobIndexPath robIndex;


    }RrToExMemPath;

    typedef struct packed {
        logic valid;
        SubTypePath subType;

        DataPath dataA;
        DataPath dataB;
        PhyRegNumPath Rs1;
        PhyRegNumPath Rs2;
        logic         srcAIsRs1;
        logic         srcBIsRs2;

        PhyRegNumPath Rd;
        logic         writeRd;

        RobIndexPath robIndex;

    }RrToExMulPath;

    typedef struct packed {
        logic valid;
        SubTypePath subType;

        DataPath dataA;
        DataPath dataB;
        PhyRegNumPath Rs1;
        PhyRegNumPath Rs2;
        logic         srcAIsRs1;
        logic         srcBIsRs2;    

        PhyRegNumPath Rd;
        logic         writeRd;


        RobIndexPath robIndex;

    }RrToExBrcPath;

    typedef struct packed {
        logic valid;
        SubTypePath subType;

        DataPath dataA;
        PhyRegNumPath Rs1;
        logic         srcAIsRs1;

        CsrAddrPath      csrAddr;

        PhyRegNumPath Rd;
        logic         writeRd;

        RobIndexPath robIndex;

    }RrToExSysPath;

    typedef struct packed {
        logic          valid;
        
        PhyRegNumPath  Rd;
        logic          writeRd;

        RobIndexPath   robIndex;
    } ExAluToWbPath;

    typedef struct packed {
        logic          valid;
        
        PhyRegNumPath  Rd;
        logic          writeRd;

        RobIndexPath   robIndex;
    } ExMemToWbPath;

    typedef struct packed {
        logic          valid;
        
        PhyRegNumPath  Rd;
        logic          writeRd;

        RobIndexPath   robIndex;
    } ExMulToWbPath;

    typedef struct packed {
        logic          valid;
        
        PhyRegNumPath  Rd;
        logic          writeRd;

        PcPath         trueTargetPc;
        logic          taken;

        RobIndexPath   robIndex;
    } ExBrcToWbPath;

    typedef struct packed {
        logic          valid;
        
        PhyRegNumPath  Rd;
        logic          writeRd;

        RobIndexPath   robIndex;    

        logic          isSerial;
        logic          exception;
    } ExSysToWbPath;

    
    //storeBuffer
    localparam STORE_BUFFER_DEPTH = 8;
    localparam STORE_BUFFER_WIDTH = $clog2(STORE_BUFFER_DEPTH);
    typedef logic [STORE_BUFFER_WIDTH-1:0] StoreBufferIndex;

    typedef struct packed {
        logic valid;
        StoreBufferIndex index;
        AddrPath addr;
        DataPath data;
    } StoreBufferPushReqPath;

    typedef struct packed {
        logic     valid;
        StoreBufferIndex index;      
    } StoreBufferPopReqPath;

    typedef struct packed {
        logic valid;
        AddrPath addr;
    } StoreBufferMatchInPath;

    typedef struct packed {
        logic    hit;
        DataPath data;
    } StoreBufferMatchOutPath;
    
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

endpackage PipelineTypes;