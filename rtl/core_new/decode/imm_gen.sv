`include "cpu_defines.svh"

module core_new_imm_gen (
    input  logic [`INST_BUS] i_inst,
    output logic [`DATA_BUS] o_imm
);
    logic [6:0] opcode;

    assign opcode = i_inst[6:0];

    always_comb begin
        unique case (opcode)
            `OP_I_TYPE, `OP_L_TYPE, `OP_JALR:
                o_imm = {{20{i_inst[31]}}, i_inst[31:20]};
            `OP_S_TYPE:
                o_imm = {{20{i_inst[31]}}, i_inst[31:25], i_inst[11:7]};
            `OP_B_TYPE:
                o_imm = {{19{i_inst[31]}}, i_inst[31], i_inst[7], i_inst[30:25], i_inst[11:8], 1'b0};
            `OP_LUI, `OP_AUIPC:
                o_imm = {i_inst[31:12], 12'b0};
            `OP_JAL:
                o_imm = {{11{i_inst[31]}}, i_inst[31], i_inst[19:12], i_inst[20], i_inst[30:21], 1'b0};
            default:
                o_imm = '0;
        endcase
    end
endmodule
