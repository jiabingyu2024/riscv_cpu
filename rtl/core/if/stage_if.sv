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

    always_comb begin
        if (i_valid) begin
            o_pc         = i_pc;
            o_inst       = i_inst;
            o_pc_predict = i_pc_predict;
        end else begin
            o_pc         = '0;
            o_inst       = '0;
            o_pc_predict = '0;
        end
    end

endmodule
