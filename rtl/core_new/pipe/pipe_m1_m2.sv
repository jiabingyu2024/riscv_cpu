`include "cpu_defines.svh"

module core_new_pipe_m1_m2 (
    input  logic             i_clk,
    input  logic             i_rst_n,
    input  logic             i_flush,
    input  logic             i_stall,
    input  logic [`DATA_BUS] i_alu_res,
    input  logic [`RF_BUS]   i_rd_addr,
    input  logic             i_reg_write,
    input  logic             i_wb_sel,
    input  logic [3:0]       i_mem_size,
    input  logic             i_load_unsigned,
    input  logic             i_valid,
    output logic [`DATA_BUS] o_alu_res,
    output logic [`RF_BUS]   o_rd_addr,
    output logic             o_reg_write,
    output logic             o_wb_sel,
    output logic [3:0]       o_mem_size,
    output logic             o_load_unsigned,
    output logic             o_valid
);
    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_alu_res <= '0;
            o_rd_addr <= '0;
            o_reg_write <= 1'b0;
            o_wb_sel <= `WB_SRC_ALU;
            o_mem_size <= `MASK_WORD;
            o_load_unsigned <= 1'b0;
            o_valid <= 1'b0;
        end else if (i_flush) begin
            o_alu_res <= '0;
            o_rd_addr <= '0;
            o_reg_write <= 1'b0;
            o_wb_sel <= `WB_SRC_ALU;
            o_mem_size <= `MASK_WORD;
            o_load_unsigned <= 1'b0;
            o_valid <= 1'b0;
        end else if (!i_stall) begin
            o_alu_res <= i_alu_res;
            o_rd_addr <= i_rd_addr;
            o_reg_write <= i_reg_write;
            o_wb_sel <= i_wb_sel;
            o_mem_size <= i_mem_size;
            o_load_unsigned <= i_load_unsigned;
            o_valid <= i_valid;
        end
    end
endmodule
