import BasicTypes::*;
import PipelineTypes::*;

package RenameTypes;


    localparam SPECRAT_READ_PORT_NUM =  WAY_NUM * 3;  
    localparam SPECRAT_WRITE_PORT_NUM = WAY_NUM;

    localparam SPECRAT_ENTRY_NUM = LOGICREG_NUM;

    localparam ARCHRAT_WRITE_PORT_NUM = WAY_NUM;

    // update RAT
    typedef struct packed {
        logic            UpdateEn;
        PhyRegNumPath    UpdatePhyRegNum;
        LgcRegNumPath    UpdateLgcRegNum;
    } RATUpdatePath;

    // READ

    typedef struct packed {
        logic          ReadEn;
        LgcRegNumPath  ReadLgcRegNum;
    } RATReadPath;

    


    // checkpoint
    localparam CHECKPOINT_NUM = 8;
    localparam CHECKPOINT_WIDTH = $clog2(CHECKPINT_NUM);

    typedef logic [CHECKPOINT_WIDTH-1:0] ChkptIndexPath;

    typedef struct packed {
        logic          ChkptCreateEn;
        ChkptIndexPath ChkptCreateIndex;
    }ChkptCreatePath; 
    typedef struct packed {
        logic          ChkptRecoverEn;
        ChkptIndexPath ChkptRecoverIndex;
    }ChkptRecoveryPath;
    typedef struct packed {
        logic          ChkptFreeEn;
        ChkptIndexPath ChkptFreeIndex;
    }ChkptFreePath;

    // FreeList

    localparam FREE_LIST_WIDTH = $clog2(PHYREG_NUM);
    typedef logic [FREE_LIST_WIDTH-1:0] FreeListCountPath;


    typedef struct packed {
        logic          allocValid;
        PhyRegNumPath  allocPhyRegNum;
    } FreeListAllocPath;

    typedef struct packed {
        logic         freeReq;
        PhyRegNumPath freePhyRegNum;
    } FreeListFreePath;





    

endpackage : RenameTypes