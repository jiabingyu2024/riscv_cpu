//------------------------------------------------------------------------------
// StoreBufferIF.sv
// 作用：定义 StoreBuffer 与 Dispatch、ExecuteMem、Commit 的接口。
// 微架构定位：Dispatch 为 store 分配 entry；ExecuteMem 在地址/数据就绪后写入
// StoreBuffer，并为 load 提供同地址匹配/转发查询；Commit 按 ROB 顺序 pop store，
// 保证错误路径 store 不会提前对外可见。
//------------------------------------------------------------------------------

import BasicTypes::*;
import PipelineTypes::*;
import StoreBufferTypes::*;

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
    );


endinterface
