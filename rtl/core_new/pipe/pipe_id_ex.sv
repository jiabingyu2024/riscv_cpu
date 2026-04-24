`include "cpu_defines.svh"

module core_new_pipe_id_ex (
    input  logic             i_clk,
    input  logic             i_rst_n,
    input  logic             i_flush,
    input  logic             i_stall,
    input  logic [`PC_BUS]   i_pc,
    input  logic             i_pred_valid,
    input  logic             i_pred_is_static,
    input  logic             i_pred_taken,
    input  logic [`PC_BUS]   i_pred_target,
    input  logic [`DATA_BUS] i_rs1_data,
    input  logic [`DATA_BUS] i_rs2_data,
    input  logic [`RF_BUS]   i_rs1_addr,
    input  logic [`RF_BUS]   i_rs2_addr,
    input  logic [`RF_BUS]   i_rd_addr,
    input  logic [`DATA_BUS] i_imm,
    input  logic             i_mem_read,
    input  logic             i_mem_write,
    input  logic             i_reg_write,
    input  logic             i_wb_sel,
    input  logic [3:0]       i_alu_op,
    input  logic [2:0]       i_branch_type,
    input  logic             i_is_branch,
    input  logic             i_is_jal,
    input  logic             i_is_jalr,
    input  logic             i_is_lui,
    input  logic             i_is_auipc,
    input  logic             i_src2_is_imm,
    input  logic [3:0]       i_mem_size,
    input  logic             i_load_unsigned,
    input  logic             i_valid,
    output logic [`PC_BUS]   o_pc,
    output logic             o_pred_valid,
    output logic             o_pred_is_static,
    output logic             o_pred_taken,
    output logic [`PC_BUS]   o_pred_target,
    output logic [`DATA_BUS] o_rs1_data,
    output logic [`DATA_BUS] o_rs2_data,
    output logic [`RF_BUS]   o_rs1_addr,
    output logic [`RF_BUS]   o_rs2_addr,
    output logic [`RF_BUS]   o_rd_addr,
    output logic [`DATA_BUS] o_imm,
    output logic             o_mem_read,
    output logic             o_mem_write,
    output logic             o_reg_write,
    output logic             o_wb_sel,
    output logic [3:0]       o_alu_op,
    output logic [2:0]       o_branch_type,
    output logic             o_is_branch,
    output logic             o_is_jal,
    output logic             o_is_jalr,
    output logic             o_is_lui,
    output logic             o_is_auipc,
    output logic             o_src2_is_imm,
    output logic [3:0]       o_mem_size,
    output logic             o_load_unsigned,
    output logic             o_valid
);
    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_pc <= '0;
            o_pred_valid <= 1'b0;
            o_pred_is_static <= 1'b0;
            o_pred_taken <= 1'b0;
            o_pred_target <= '0;
            o_rs1_data <= '0;
            o_rs2_data <= '0;
            o_rs1_addr <= '0;
            o_rs2_addr <= '0;
            o_rd_addr <= '0;
            o_imm <= '0;
            o_mem_read <= 1'b0;
            o_mem_write <= 1'b0;
            o_reg_write <= 1'b0;
            o_wb_sel <= `WB_SRC_ALU;
            o_alu_op <= `ALU_ADD;
            o_branch_type <= 3'b000;
            o_is_branch <= 1'b0;
            o_is_jal <= 1'b0;
            o_is_jalr <= 1'b0;
            o_is_lui <= 1'b0;
            o_is_auipc <= 1'b0;
            o_src2_is_imm <= 1'b0;
            o_mem_size <= `MASK_WORD;
            o_load_unsigned <= 1'b0;
            o_valid <= 1'b0;
        end else if (i_flush) begin
            o_pc <= '0;
            o_pred_valid <= 1'b0;
            o_pred_is_static <= 1'b0;
            o_pred_taken <= 1'b0;
            o_pred_target <= '0;
            o_rs1_data <= '0;
            o_rs2_data <= '0;
            o_rs1_addr <= '0;
            o_rs2_addr <= '0;
            o_rd_addr <= '0;
            o_imm <= '0;
            o_mem_read <= 1'b0;
            o_mem_write <= 1'b0;
            o_reg_write <= 1'b0;
            o_wb_sel <= `WB_SRC_ALU;
            o_alu_op <= `ALU_ADD;
            o_branch_type <= 3'b000;
            o_is_branch <= 1'b0;
            o_is_jal <= 1'b0;
            o_is_jalr <= 1'b0;
            o_is_lui <= 1'b0;
            o_is_auipc <= 1'b0;
            o_src2_is_imm <= 1'b0;
            o_mem_size <= `MASK_WORD;
            o_load_unsigned <= 1'b0;
            o_valid <= 1'b0;
        end else if (!i_stall) begin
            o_pc <= i_pc;
            o_pred_valid <= i_pred_valid;
            o_pred_is_static <= i_pred_is_static;
            o_pred_taken <= i_pred_taken;
            o_pred_target <= i_pred_target;
            o_rs1_data <= i_rs1_data;
            o_rs2_data <= i_rs2_data;
            o_rs1_addr <= i_rs1_addr;
            o_rs2_addr <= i_rs2_addr;
            o_rd_addr <= i_rd_addr;
            o_imm <= i_imm;
            o_mem_read <= i_mem_read;
            o_mem_write <= i_mem_write;
            o_reg_write <= i_reg_write;
            o_wb_sel <= i_wb_sel;
            o_alu_op <= i_alu_op;
            o_branch_type <= i_branch_type;
            o_is_branch <= i_is_branch;
            o_is_jal <= i_is_jal;
            o_is_jalr <= i_is_jalr;
            o_is_lui <= i_is_lui;
            o_is_auipc <= i_is_auipc;
            o_src2_is_imm <= i_src2_is_imm;
            o_mem_size <= i_mem_size;
            o_load_unsigned <= i_load_unsigned;
            o_valid <= i_valid;
        end
    end
endmodule
