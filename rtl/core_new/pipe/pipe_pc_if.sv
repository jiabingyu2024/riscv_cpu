`include "cpu_defines.svh"

module core_new_pipe_pc_if (
    input  logic           i_clk,
    input  logic           i_rst_n,
    input  logic           i_flush,
    input  logic           i_stall,
    input  logic [`PC_BUS] i_pc,
    input  logic           i_pred_valid,
    input  logic           i_pred_taken,
    input  logic [`PC_BUS] i_pred_target,
    input  logic           i_valid,
    output logic [`PC_BUS] o_pc,
    output logic           o_pred_valid,
    output logic           o_pred_is_static,
    output logic           o_pred_taken,
    output logic [`PC_BUS] o_pred_target,
    output logic           o_valid
);
    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_pc <= '0;
            o_pred_valid <= 1'b0;
            o_pred_is_static <= 1'b0;
            o_pred_taken <= 1'b0;
            o_pred_target <= '0;
            o_valid <= 1'b0;
        end else if (i_flush) begin
            o_pc <= '0;
            o_pred_valid <= 1'b0;
            o_pred_is_static <= 1'b0;
            o_pred_taken <= 1'b0;
            o_pred_target <= '0;
            o_valid <= 1'b0;
        end else if (!i_stall) begin
            o_pc <= i_pc;
            o_pred_valid <= i_pred_valid;
            o_pred_is_static <= 1'b0;
            o_pred_taken <= i_pred_taken;
            o_pred_target <= i_pred_target;
            o_valid <= i_valid;
        end
    end
endmodule
