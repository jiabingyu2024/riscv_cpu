`include "cpu_defines.svh"

module core_new_pipeline_ctrl (
    input  logic i_load_use_stall,
    input  logic i_redirect_valid_f,
    input  logic i_redirect_valid_d,
    input  logic i_redirect_valid_x,
    output logic o_stall_pc_if,
    output logic o_stall_if_id,
    output logic o_flush_pc_if,
    output logic o_flush_if_id,
    output logic o_flush_id_ex,
    output logic o_flush_ex_m1
);
    always_comb begin
        o_stall_pc_if = i_load_use_stall && !i_redirect_valid_d && !i_redirect_valid_x;
        o_stall_if_id = i_load_use_stall && !i_redirect_valid_d && !i_redirect_valid_x;
        o_flush_pc_if = i_redirect_valid_f || i_redirect_valid_d || i_redirect_valid_x;
        o_flush_if_id = i_redirect_valid_d || i_redirect_valid_x;
        o_flush_id_ex = i_redirect_valid_x || i_load_use_stall;
        o_flush_ex_m1 = 1'b0;
    end
endmodule
