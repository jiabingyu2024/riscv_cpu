//==============================================================================
// 模块: reg_ex_mem
// 功能概述：
//   EX/MEM 流水线寄存器。锁存 ALU 结果、store 用的 rs2 数据、rd、访存与写回控制，供 MEM 级地址/写数据与旁路使用。
// 接口/协作审查（供采纳）：
//   - i_rs2_data 用于 store：需与 forward 对 store 数据的旁路约定一致（通常旁路到 EX 再打入此寄存器）。ok
//==============================================================================
`include "cpu_defines.svh"

module reg_ex_mem (
    input logic                               i_clk,
    input logic                               i_rst_n,
    input logic                               i_flush,
    input logic                               i_stall,

    input logic [`RF_BUS]                     i_rd_addr,
    input logic [`DATA_BUS]                   i_alu_res,
    input logic [`DATA_BUS]                   i_A2_data,
    input logic                               i_cf_update_taken,
    input logic                               i_cf_update_en,
    input logic [`PC_BUS]                     i_cf_update_pc,
    input logic [`PC_BUS]                     i_cf_update_target,
    input logic                               i_cf_error,
    input logic [`PC_BUS]                     i_cf_right_pc,

    input logic                               i_mem_read,
    input logic                               i_mem_write,
    input logic                               i_wb_src,
    input logic                               i_reg_write,
    input logic  [1:0]                        i_mem_mask,
    input logic                               i_load_unsigned,

    output logic [`RF_BUS]                    o_rd_addr,
    output logic [`DATA_BUS]                  o_alu_res,
    output logic [`DATA_BUS]                  o_a2_data,
    output logic                              o_cf_update_taken,
    output logic                              o_cf_update_en,
    output logic [`PC_BUS]                    o_cf_update_pc,
    output logic [`PC_BUS]                    o_cf_update_target,
    output logic                              o_cf_error,
    output logic [`PC_BUS]                    o_cf_right_pc,

    output logic                              o_mem_read,
    output logic                              o_mem_write,
    output logic                              o_wb_src,
    output logic                              o_reg_write,
    output logic  [1:0]                       o_mem_mask,
    output logic                              o_load_unsigned

);

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_rd_addr       <= '0;
            o_alu_res       <= '0;
            o_a2_data       <= '0;
            o_cf_update_taken <= 1'b0;
            o_cf_update_en    <= 1'b0;
            o_cf_update_pc    <= '0;
            o_cf_update_target<= '0;
            o_cf_error        <= 1'b0;
            o_cf_right_pc     <= '0;
            o_mem_read      <= 1'b0;
            o_mem_write     <= 1'b0;
            o_wb_src        <= `WB_SRC_ALU;
            o_reg_write     <= 1'b0;
            o_mem_mask      <= `MASK_WORD;
            o_load_unsigned <= 1'b0;
        end else if (i_flush) begin
            o_rd_addr       <= '0;
            o_alu_res       <= '0;
            o_a2_data       <= '0;
            o_cf_update_taken <= 1'b0;
            o_cf_update_en    <= 1'b0;
            o_cf_update_pc    <= '0;
            o_cf_update_target<= '0;
            o_cf_error        <= 1'b0;
            o_cf_right_pc     <= '0;
            o_mem_read      <= 1'b0;
            o_mem_write     <= 1'b0;
            o_wb_src        <= `WB_SRC_ALU;
            o_reg_write     <= 1'b0;
            o_mem_mask      <= `MASK_WORD;
            o_load_unsigned <= 1'b0;
        end else if (!i_stall) begin
            o_rd_addr       <= i_rd_addr;
            o_alu_res       <= i_alu_res;
            o_a2_data       <= i_A2_data;
            o_cf_update_taken <= i_cf_update_taken;
            o_cf_update_en    <= i_cf_update_en;
            o_cf_update_pc    <= i_cf_update_pc;
            o_cf_update_target<= i_cf_update_target;
            o_cf_error        <= i_cf_error;
            o_cf_right_pc     <= i_cf_right_pc;
            o_mem_read      <= i_mem_read;
            o_mem_write     <= i_mem_write;
            o_wb_src        <= i_wb_src;
            o_reg_write     <= i_reg_write;
            o_mem_mask      <= i_mem_mask;
            o_load_unsigned <= i_load_unsigned;
        end
    end
endmodule
