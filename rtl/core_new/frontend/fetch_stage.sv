`include "cpu_defines.svh"

module core_new_fetch_stage (
    input  logic [`PC_BUS]   i_pc,
    input  logic [`INST_BUS] i_irom_data,
    input  logic             i_pred_valid,
    input  logic             i_pred_is_static,
    input  logic             i_pred_taken,
    input  logic [`PC_BUS]   i_pred_target,
    input  logic             i_valid,
    output logic             o_static_redirect_valid,
    output logic [`PC_BUS]   o_static_redirect_pc,
    output logic [`PC_BUS]   o_pc,
    output logic [`INST_BUS] o_inst,
    output logic             o_pred_valid,
    output logic             o_pred_is_static,
    output logic             o_pred_taken,
    output logic [`PC_BUS]   o_pred_target,
    output logic             o_valid
);
    logic [6:0] opcode;
    logic [`DATA_BUS] branch_imm;
    logic             static_taken;
    logic [`PC_BUS]   static_target;

    assign opcode       = i_irom_data[6:0];
    assign branch_imm   = {{19{i_irom_data[31]}}, i_irom_data[31], i_irom_data[7],
                           i_irom_data[30:25], i_irom_data[11:8], 1'b0};
    assign static_taken = (opcode == `OP_B_TYPE) && branch_imm[`DATA_WID-1];
    assign static_target = i_pc + branch_imm;

    always_comb begin
        o_pc             = i_valid ? i_pc : '0;
        o_inst           = i_valid ? i_irom_data : '0;
        o_static_redirect_valid = i_valid && !i_pred_valid && static_taken;
        o_static_redirect_pc    = static_target;

        if (i_valid && !i_pred_valid && static_taken) begin
            o_pred_valid     = 1'b1;
            o_pred_is_static = 1'b1;
            o_pred_taken     = 1'b1;
            o_pred_target    = static_target;
        end else begin
            o_pred_valid     = i_valid ? i_pred_valid : 1'b0;
            o_pred_is_static = i_valid ? i_pred_is_static : 1'b0;
            o_pred_taken     = i_valid ? i_pred_taken : 1'b0;
            o_pred_target    = i_valid ? i_pred_target : '0;
        end
        o_valid          = i_valid;
    end
endmodule
