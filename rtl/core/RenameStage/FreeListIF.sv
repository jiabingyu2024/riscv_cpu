

import BasicTypes::*;
import PipelineTypes::*;
import RenameTypes::*;

interface FreeListIF( input logic clk, rst );

    //FreeList接口
    FreeListAllocPath   freeListAlloc[WAY_NUM];
    FreeListFreePath    freeListFree[WAY_NUM];
    logic               freeListAllocReq[WAY_NUM];
    FreeListCountPath   freeListCount; //FreeList剩余物理寄存器数量
    ChkptCreatePath     freeListChkptCreate;
    logic               freeListChkptCreateEn;
    ChkptRecoveryPath   freeListChkptRecover;
    ChkptFreePath       freeListChkptFree;

    modport FreeList(
    input
        clk,
        rst,
        freeListAllocReq,
        freeListFree,
        freeListChkptCreateEn,
        freeListChkptRecover,
        freeListChkptFree,
    output
        freeListAlloc,
        freeListCount,
        freeListChkptCreate
    );


    modport RenameStage(
    input
        freeListAlloc,
        freeListCount,
        freeListChkptCreate
    output
        freeListAllocReq,
        freeListChkptCreateEn
    );
    
    modport CommitStage(
    output
        freeListFree,
        freeListChkptFree
    );

    modport RecoveryManager(
    output
        freeListChkptRecover
    )
    

endinterface