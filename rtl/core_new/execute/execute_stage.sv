`include "cpu_defines.svh"

module core_new_execute_stage (
    input  logic [`PC_BUS]   i_pc,
    input  logic [`DATA_BUS] i_rs1_data,
    input  logic [`DATA_BUS] i_rs2_data,
    input  logic [`DATA_BUS] i_imm,
    input  logic [`RF_BUS]   i_rd_addr,
    input  logic             i_reg_write,
    input  logic             i_mem_read,
    input  logic             i_mem_write,
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
    input  logic             i_pred_taken,
    input  logic [`PC_BUS]   i_pred_target,
    input  logic [`DATA_BUS] i_fwd_exmem_data,
    input  logic [`DATA_BUS] i_fwd_m1m2_data,
    input  logic [`DATA_BUS] i_fwd_m2wb_data,
    input  logic [1:0]       i_fwd_rs1_sel,
    input  logic [1:0]       i_fwd_rs2_sel,
    input  logic [1:0]       i_fwd_branch_rs1_sel,
    input  logic [1:0]       i_fwd_branch_rs2_sel,
    input  logic [1:0]       i_fwd_target_base_sel,
    output logic [`DATA_BUS] o_alu_res,
    output logic [`DATA_BUS] o_store_data,
    output logic [`RF_BUS]   o_rd_addr,
    output logic             o_reg_write,
    output logic             o_mem_read,
    output logic             o_mem_write,
    output logic             o_wb_sel,
    output logic [3:0]       o_mem_size,
    output logic             o_load_unsigned,
    output logic             o_redirect_valid,
    output logic [`PC_BUS]   o_redirect_pc,
    output logic             o_train_valid,
    output logic             o_train_taken,
    output logic [`PC_BUS]   o_train_pc,
    output logic [`PC_BUS]   o_train_target
);
    logic [`DATA_BUS] rs1_alu_data;
    logic [`DATA_BUS] rs2_alu_data;
    logic [`DATA_BUS] rs1_branch_data;
    logic [`DATA_BUS] rs2_branch_data;
    logic [`DATA_BUS] target_base_data;
    logic [`DATA_BUS] alu_src2;
    logic [`DATA_BUS] alu_raw;
    logic             branch_valid_unused;
    logic             actual_taken_unused;
    logic [`PC_BUS]   actual_target_unused;

    function automatic [`DATA_WID-1:0] sel_fwd_data;
        input logic [`DATA_BUS] rf_data;
        input logic [`DATA_BUS] exmem_data;
        input logic [`DATA_BUS] m1m2_data;
        input logic [`DATA_BUS] m2wb_data;
        input logic [1:0]       sel;
        begin
            unique case (sel)
                2'b01:   sel_fwd_data = exmem_data;
                2'b10:   sel_fwd_data = m1m2_data;
                2'b11:   sel_fwd_data = m2wb_data;
                default: sel_fwd_data = rf_data;
            endcase
        end
    endfunction

    assign rs1_alu_data    = sel_fwd_data(i_rs1_data, i_fwd_exmem_data, i_fwd_m1m2_data, i_fwd_m2wb_data, i_fwd_rs1_sel);
    assign rs2_alu_data    = sel_fwd_data(i_rs2_data, i_fwd_exmem_data, i_fwd_m1m2_data, i_fwd_m2wb_data, i_fwd_rs2_sel);
    assign rs1_branch_data = sel_fwd_data(i_rs1_data, i_fwd_exmem_data, i_fwd_m1m2_data, i_fwd_m2wb_data, i_fwd_branch_rs1_sel);
    assign rs2_branch_data = sel_fwd_data(i_rs2_data, i_fwd_exmem_data, i_fwd_m1m2_data, i_fwd_m2wb_data, i_fwd_branch_rs2_sel);
    assign target_base_data = sel_fwd_data(i_rs1_data, i_fwd_exmem_data, i_fwd_m1m2_data, i_fwd_m2wb_data, i_fwd_target_base_sel);
    assign alu_src2 = i_src2_is_imm ? i_imm : rs2_alu_data;

    core_new_alu u_alu (
        .i_alu1   (i_is_auipc ? i_pc : rs1_alu_data),
        .i_alu2   (alu_src2),
        .i_alu_op (i_alu_op),
        .o_alu_res(alu_raw)
    );

    core_new_branch_unit u_branch_unit (
        .i_is_branch    (i_is_branch),
        .i_is_jal       (i_is_jal),
        .i_is_jalr      (i_is_jalr),
        .i_pc           (i_pc),
        .i_imm          (i_imm),
        .i_branch_rs1   (rs1_branch_data),
        .i_branch_rs2   (rs2_branch_data),
        .i_target_base  (target_base_data),
        .i_branch_type  (i_branch_type),
        .i_pred_taken   (i_pred_taken),
        .i_pred_target  (i_pred_target),
        .o_branch_valid (branch_valid_unused),
        .o_actual_taken (actual_taken_unused),
        .o_actual_target(actual_target_unused),
        .o_redirect_valid(o_redirect_valid),
        .o_redirect_pc  (o_redirect_pc),
        .o_train_valid  (o_train_valid),
        .o_train_taken  (o_train_taken),
        .o_train_target (o_train_target)
    );

    always_comb begin
        o_alu_res = alu_raw;
        if (i_is_lui) begin
            o_alu_res = i_imm;
        end else if (i_is_jal || i_is_jalr) begin
            o_alu_res = i_pc + 32'd4;
        end
    end

    assign o_store_data    = rs2_alu_data;
    assign o_rd_addr       = i_rd_addr;
    assign o_reg_write     = i_reg_write;
    assign o_mem_read      = i_mem_read;
    assign o_mem_write     = i_mem_write;
    assign o_wb_sel        = i_wb_sel;
    assign o_mem_size      = i_mem_size;
    assign o_load_unsigned = i_load_unsigned;
    assign o_train_pc      = i_pc;
endmodule
