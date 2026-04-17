//==============================================================================
// 模块: stage_if
// 功能概述：
//  纯 组合逻辑，传递reg_pc_if的输出,当valid为1时，输出pc和inst，否则输出0。
//==============================================================================
`include "cpu_defines.svh"

module stage_if(
    input  logic  [`PC_BUS]         i_pc,
    input  logic  [`INST_BUS]       i_inst,
    input  logic  [`PC_BUS]         i_pc_predict,

    input  logic                    i_valid,

    output logic  [`PC_BUS]         o_pc,
    output logic  [`INST_BUS]       o_inst,
    output logic  [`PC_BUS]         o_pc_predict

);

endmodule