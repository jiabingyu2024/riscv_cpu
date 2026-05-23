import BasicTypes::*;
import PipelineTypes::*;

interface StoreBufferIF( input logic clk, rst );
    
    logic    allocReq;
    logic    allocRdy;
    StoreBufferIndexPath allocIndex;

    StoreBufferPushReqPath  StoreBufferPushReq;

    StoreBufferPopReqPath   StoreBufferPopReq;

    StoreBufferMatchInPath  StoreBufferMatchIn;
    StoreBufferMatchOutPath StoreBufferMatchOut;  

    modport StoreBuffer(
        input
            clk,
            rst,
            allocReq,
            StoreBufferPushReq,
            StoreBufferPopReq,
            StoreBufferMatchIn,
        output
            allocRdy,
            allocIndex,
            StoreBufferMatchOut
    );

    modport DispatchStage(
        input 
            allocRdy,
            allocIndex,
        output  
            allocReq
    );

    modport ExecuteMemStage(
        input
            StoreBufferMatchOut,
        output
            StoreBufferMatchIn,
            StoreBufferPushReq

    );

    modport CommitStage(
        output
            StoreBufferPopReq
    )


endinterface