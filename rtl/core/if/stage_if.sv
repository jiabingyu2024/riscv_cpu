//==============================================================================
// 模块: stage_if
// 功能概述：
//  纯组合逻辑。valid 为 1 时输出已对齐的 PC、IROM instruction 和预测 PC，否则输出 0。
//==============================================================================
`include "cpu_defines.svh"

module stage_if(
    input  logic  [`PC_BUS]         i_pc,
    input  logic  [`INST_BUS]       i_inst,
    input  logic  [`PC_BUS]         i_pc_predict,
    input  logic  [7:0]             i_pht_idx,
    input  logic  [7:0]             i_local_pht_idx,
    input  logic  [7:0]             i_choice_idx,
    input  logic                    i_global_pred_taken,
    input  logic                    i_local_pred_taken,

    input  logic                    i_valid,

    output logic  [`PC_BUS]         o_pc,
    output logic  [`INST_BUS]       o_inst,
    output logic  [`PC_BUS]         o_pc_predict,
    output logic  [7:0]             o_pht_idx,
    output logic  [7:0]             o_local_pht_idx,
    output logic  [7:0]             o_choice_idx,
    output logic                    o_global_pred_taken,
    output logic                    o_local_pred_taken

);

    always_comb begin
        if (i_valid) begin
            o_pc         = i_pc;
            o_inst       = i_inst;
            o_pc_predict = i_pc_predict;
            o_pht_idx    = i_pht_idx;
            o_local_pht_idx = i_local_pht_idx;
            o_choice_idx = i_choice_idx;
            o_global_pred_taken = i_global_pred_taken;
            o_local_pred_taken = i_local_pred_taken;
        end else begin
            o_pc         = '0;
            o_inst       = '0;
            o_pc_predict = '0;
            o_pht_idx    = '0;
            o_local_pht_idx = '0;
            o_choice_idx = '0;
            o_global_pred_taken = 1'b0;
            o_local_pred_taken = 1'b0;
        end
    end

endmodule
