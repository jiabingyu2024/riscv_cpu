//------------------------------------------------------------------------------
// WriteBackStageIF.sv
// 作用：定义 WriteBackStage 对 ROB/Commit 可见的写回完成信息。
// 微架构定位：WriteBackStage 汇总各执行管线结果，形成多端口 RobDoneReq，通知
// ROB 对应 entry 已完成、是否异常、分支真实方向/目标。实际结果前递通过 BypassIF，
// 提交态更新仍由 CommitStage 从 ROB head 有序完成。
//------------------------------------------------------------------------------

import  BasicTypes::*;
import  PipelineTypes::*;
import  ROBTypes::*;


interface WriteBackStageIF( input logic clk, rst );

    localparam int WB_ROB_DONE_PORT_NUM = WAY_NUM * 5;

    RobDoneReqPath RobDoneReq [WB_ROB_DONE_PORT_NUM];

    modport WriteBackStage(
        input
            clk,
            rst,
        output
            RobDoneReq
    );

    modport CommitStage(
        input
            RobDoneReq
    );

    modport ROB(
        input
            RobDoneReq
    );
    

endinterface
