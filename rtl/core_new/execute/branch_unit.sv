`include "cpu_defines.svh"

module core_new_branch_unit (
    input  logic             i_is_branch,
    input  logic             i_is_jal,
    input  logic             i_is_jalr,
    input  logic [`PC_BUS]   i_pc,
    input  logic [`DATA_BUS] i_imm,
    input  logic [`DATA_BUS] i_branch_rs1,
    input  logic [`DATA_BUS] i_branch_rs2,
    input  logic [`DATA_BUS] i_target_base,
    input  logic [2:0]       i_branch_type,
    input  logic             i_pred_taken,
    input  logic [`PC_BUS]   i_pred_target,
    output logic             o_branch_valid,
    output logic             o_actual_taken,
    output logic [`PC_BUS]   o_actual_target,
    output logic             o_redirect_valid,
    output logic [`PC_BUS]   o_redirect_pc,
    output logic             o_train_valid,
    output logic             o_train_taken,
    output logic [`PC_BUS]   o_train_target
);
    logic branch_taken;
    logic [`PC_BUS] branch_target;
    logic target_mismatch;

    always_comb begin
        branch_taken  = 1'b0;
        branch_target = i_pc + i_imm;

        if (i_is_branch) begin
            unique case (i_branch_type)
                `FUNC3_BEQ:  branch_taken = (i_branch_rs1 == i_branch_rs2);
                `FUNC3_BNE:  branch_taken = (i_branch_rs1 != i_branch_rs2);
                `FUNC3_BLT:  branch_taken = ($signed(i_branch_rs1) <  $signed(i_branch_rs2));
                `FUNC3_BGE:  branch_taken = ($signed(i_branch_rs1) >= $signed(i_branch_rs2));
                `FUNC3_BLTU: branch_taken = (i_branch_rs1 <  i_branch_rs2);
                `FUNC3_BGEU: branch_taken = (i_branch_rs1 >= i_branch_rs2);
                default:     branch_taken = 1'b0;
            endcase
        end else if (i_is_jal) begin
            branch_taken  = 1'b1;
            branch_target = i_pc + i_imm;
        end else if (i_is_jalr) begin
            branch_taken  = 1'b1;
            branch_target = (i_target_base + i_imm) & ~32'd1;
        end
    end

    assign o_branch_valid  = i_is_branch || i_is_jal || i_is_jalr;
    assign o_actual_taken  = branch_taken;
    assign o_actual_target = branch_taken ? branch_target : (i_pc + 32'd4);
    assign target_mismatch = o_actual_taken && (o_actual_target != i_pred_target);
    assign o_redirect_valid = o_branch_valid &&
                              ((o_actual_taken != i_pred_taken) || (i_pred_taken && target_mismatch));
    assign o_redirect_pc    = o_actual_target;
    assign o_train_valid    = o_branch_valid;
    assign o_train_taken    = o_actual_taken;
    assign o_train_target   = o_actual_target;
endmodule
