`include "cpu_defines.svh"

module core_new_pc_stage (
    input  logic             i_clk,
    input  logic             i_rst_n,
    input  logic             i_stall,
    input  logic             i_redirect,
    input  logic [`PC_BUS]   i_next_pc,
    output logic [`PC_BUS]   o_pc
);
    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_pc <= 32'h8000_0000;
        end else if (i_redirect || !i_stall) begin
            o_pc <= i_next_pc;
        end
    end
endmodule
