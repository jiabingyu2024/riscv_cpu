`include "cpu_defines.svh"

module core_new_redirect_ctrl (
    input  logic           i_redirect_valid,
    input  logic [`PC_BUS] i_redirect_pc,
    input  logic           i_frontend_stall,
    input  logic           i_pred_valid,
    input  logic           i_pred_taken,
    input  logic [`PC_BUS] i_pred_target,
    input  logic [`PC_BUS] i_pc_cur,
    output logic [`PC_BUS] o_next_pc,
    output logic           o_fetch_pred_valid,
    output logic           o_fetch_pred_taken,
    output logic [`PC_BUS] o_fetch_pred_target
);
    logic [`PC_BUS] seq_pc;

    assign seq_pc = i_pc_cur + 32'd4;

    always_comb begin
        o_fetch_pred_valid  = i_pred_valid;
        o_fetch_pred_taken  = i_pred_valid && i_pred_taken;
        o_fetch_pred_target = i_pred_target;

        if (i_redirect_valid) begin
            o_next_pc = i_redirect_pc;
        end else if (i_frontend_stall) begin
            o_next_pc = i_pc_cur;
        end else if (i_pred_valid && i_pred_taken) begin
            o_next_pc = i_pred_target;
        end else begin
            o_next_pc = seq_pc;
        end
    end
endmodule
