`include "cpu_defines.svh"

module core_new_forward_ctrl (
    input  logic [`RF_BUS] i_idex_rs1,
    input  logic [`RF_BUS] i_idex_rs2,
    input  logic [`RF_BUS] i_exmem_rd,
    input  logic [`RF_BUS] i_m1m2_rd,
    input  logic [`RF_BUS] i_m2wb_rd,
    input  logic           i_exmem_we,
    input  logic           i_m1m2_we,
    input  logic           i_m2wb_we,
    input  logic           i_src2_is_imm,
    input  logic           i_is_branch_like,
    input  logic           i_is_jalr,
    output logic [1:0]     o_fwd_rs1_sel,
    output logic [1:0]     o_fwd_rs2_sel,
    output logic [1:0]     o_fwd_branch_rs1_sel,
    output logic [1:0]     o_fwd_branch_rs2_sel,
    output logic [1:0]     o_fwd_target_base_sel
);
    function automatic [1:0] choose_sel;
        input logic [`RF_BUS] rs_addr;
        begin
            if ((rs_addr != '0) && i_exmem_we && (i_exmem_rd == rs_addr)) begin
                choose_sel = 2'b01;
            end else if ((rs_addr != '0) && i_m1m2_we && (i_m1m2_rd == rs_addr)) begin
                choose_sel = 2'b10;
            end else if ((rs_addr != '0) && i_m2wb_we && (i_m2wb_rd == rs_addr)) begin
                choose_sel = 2'b11;
            end else begin
                choose_sel = 2'b00;
            end
        end
    endfunction

    always_comb begin
        o_fwd_rs1_sel         = choose_sel(i_idex_rs1);
        o_fwd_rs2_sel         = choose_sel(i_idex_rs2);
        o_fwd_branch_rs1_sel  = i_is_branch_like ? choose_sel(i_idex_rs1) : 2'b00;
        o_fwd_branch_rs2_sel  = i_is_branch_like ? choose_sel(i_idex_rs2) : 2'b00;
        o_fwd_target_base_sel = i_is_jalr ? choose_sel(i_idex_rs1) : 2'b00;
    end
endmodule
