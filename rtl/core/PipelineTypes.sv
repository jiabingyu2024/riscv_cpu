

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

    typedef struct 


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

endpackage PipelineTypes;