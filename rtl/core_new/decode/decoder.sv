`include "cpu_defines.svh"

module core_new_decoder (
    input  logic [`INST_BUS] i_inst,
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
    output logic             o_load_unsigned
);
    logic [6:0] opcode;
    logic [2:0] func3;
    logic [6:0] func7;

    assign opcode = i_inst[6:0];
    assign func3  = i_inst[14:12];
    assign func7  = i_inst[31:25];

    always_comb begin
        o_mem_read      = 1'b0;
        o_mem_write     = 1'b0;
        o_reg_write     = 1'b0;
        o_wb_sel        = `WB_SRC_ALU;
        o_alu_op        = `ALU_ADD;
        o_branch_type   = func3;
        o_is_branch     = 1'b0;
        o_is_jal        = 1'b0;
        o_is_jalr       = 1'b0;
        o_is_lui        = 1'b0;
        o_is_auipc      = 1'b0;
        o_src2_is_imm   = 1'b0;
        o_mem_size      = `MASK_WORD;
        o_load_unsigned = 1'b0;

        unique case (opcode)
            `OP_R_TYPE: begin
                o_reg_write = 1'b1;
                unique case (func3)
                    `FUNC3_ADD_SUB: o_alu_op = (func7 == `FUNC7_SUB) ? `ALU_SUB : `ALU_ADD;
                    `FUNC3_SLT:     o_alu_op = `ALU_LT;
                    `FUNC3_SLTU:    o_alu_op = `ALU_LTU;
                    `FUNC3_AND:     o_alu_op = `ALU_AND;
                    `FUNC3_OR:      o_alu_op = `ALU_OR;
                    `FUNC3_XOR:     o_alu_op = `ALU_XOR;
                    `FUNC3_SLL:     o_alu_op = `ALU_SL;
                    `FUNC3_SRL_SRA: o_alu_op = (func7 == `FUNC7_SRA) ? `ALU_SRA : `ALU_SRL;
                    default:        o_alu_op = `ALU_ADD;
                endcase
            end
            `OP_I_TYPE: begin
                o_reg_write   = 1'b1;
                o_src2_is_imm = 1'b1;
                unique case (func3)
                    `FUNC3_ADD_SUB: o_alu_op = `ALU_ADD;
                    `FUNC3_SLT:     o_alu_op = `ALU_LT;
                    `FUNC3_SLTU:    o_alu_op = `ALU_LTU;
                    `FUNC3_AND:     o_alu_op = `ALU_AND;
                    `FUNC3_OR:      o_alu_op = `ALU_OR;
                    `FUNC3_XOR:     o_alu_op = `ALU_XOR;
                    `FUNC3_SLL:     o_alu_op = `ALU_SL;
                    `FUNC3_SRL_SRA: o_alu_op = i_inst[30] ? `ALU_SRA : `ALU_SRL;
                    default:        o_alu_op = `ALU_ADD;
                endcase
            end
            `OP_L_TYPE: begin
                o_mem_read      = 1'b1;
                o_reg_write     = 1'b1;
                o_wb_sel        = `WB_SRC_MEM;
                o_src2_is_imm   = 1'b1;
                o_load_unsigned = func3[2];
                unique case (func3)
                    `FUNC3_LB, `FUNC3_LBU: o_mem_size = `MASK_BYTE;
                    `FUNC3_LH, `FUNC3_LHU: o_mem_size = `MASK_HALF;
                    default:               o_mem_size = `MASK_WORD;
                endcase
            end
            `OP_S_TYPE: begin
                o_mem_write   = 1'b1;
                o_src2_is_imm = 1'b1;
                unique case (func3)
                    `FUNC3_SB: o_mem_size = `MASK_BYTE;
                    `FUNC3_SH: o_mem_size = `MASK_HALF;
                    default:   o_mem_size = `MASK_WORD;
                endcase
            end
            `OP_B_TYPE: begin
                o_is_branch = 1'b1;
            end
            `OP_JAL: begin
                o_reg_write = 1'b1;
                o_is_jal    = 1'b1;
            end
            `OP_JALR: begin
                o_reg_write   = 1'b1;
                o_is_jalr     = 1'b1;
                o_src2_is_imm = 1'b1;
            end
            `OP_LUI: begin
                o_reg_write   = 1'b1;
                o_is_lui      = 1'b1;
                o_src2_is_imm = 1'b1;
            end
            `OP_AUIPC: begin
                o_reg_write   = 1'b1;
                o_is_auipc    = 1'b1;
                o_src2_is_imm = 1'b1;
            end
            default: begin
            end
        endcase
    end
endmodule
