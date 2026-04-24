`include "cpu_defines.svh"

module core_new_decode_stage (
    input  logic             i_clk,
    input  logic             i_rst_n,
    input  logic [`PC_BUS]   i_pc,
    input  logic [`INST_BUS] i_inst,
    input  logic             i_pred_taken,
    input  logic [`PC_BUS]   i_pred_target,
    input  logic             i_wb_we,
    input  logic [`RF_BUS]   i_wb_rd,
    input  logic [`DATA_BUS] i_wb_data,
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
    output logic [`RF_BUS]   o_rs1_addr,
    output logic [`RF_BUS]   o_rs2_addr,
    output logic [`RF_BUS]   o_rd_addr,
    output logic [`DATA_BUS] o_rs1_data,
    output logic [`DATA_BUS] o_rs2_data,
    output logic [`DATA_BUS] o_imm
);
    logic [`DATA_BUS] rs1_data;
    logic [`DATA_BUS] rs2_data;
    logic             unused_pred_taken;
    logic [`PC_BUS]   unused_pc;
    logic [`PC_BUS]   unused_pred_target;

    assign o_rs1_addr = i_inst[19:15];
    assign o_rs2_addr = i_inst[24:20];
    assign o_rd_addr  = i_inst[11:7];
    assign o_rs1_data = rs1_data;
    assign o_rs2_data = rs2_data;

    core_new_decoder u_decoder (
        .i_inst          (i_inst),
        .o_mem_read      (o_mem_read),
        .o_mem_write     (o_mem_write),
        .o_reg_write     (o_reg_write),
        .o_wb_sel        (o_wb_sel),
        .o_alu_op        (o_alu_op),
        .o_branch_type   (o_branch_type),
        .o_is_branch     (o_is_branch),
        .o_is_jal        (o_is_jal),
        .o_is_jalr       (o_is_jalr),
        .o_is_lui        (o_is_lui),
        .o_is_auipc      (o_is_auipc),
        .o_src2_is_imm   (o_src2_is_imm),
        .o_mem_size      (o_mem_size),
        .o_load_unsigned (o_load_unsigned)
    );

    core_new_imm_gen u_imm_gen (
        .i_inst (i_inst),
        .o_imm  (o_imm)
    );

    core_new_regfile u_regfile (
        .i_clk      (i_clk),
        .i_rst_n    (i_rst_n),
        .i_rs1_addr (o_rs1_addr),
        .i_rs2_addr (o_rs2_addr),
        .i_we       (i_wb_we),
        .i_w_addr   (i_wb_rd),
        .i_w_data   (i_wb_data),
        .o_rs1_data (rs1_data),
        .o_rs2_data (rs2_data)
    );

    assign unused_pred_taken = i_pred_taken;
    assign unused_pc         = i_pc;
    assign unused_pred_target = i_pred_target;
endmodule
