`include "cpu_defines.svh"

module core_new_alu (
    input  logic [`DATA_BUS] i_alu1,
    input  logic [`DATA_BUS] i_alu2,
    input  logic [3:0]       i_alu_op,
    output logic [`DATA_BUS] o_alu_res
);
    always_comb begin
        unique case (i_alu_op)
            `ALU_AND:  o_alu_res = i_alu1 & i_alu2;
            `ALU_OR:   o_alu_res = i_alu1 | i_alu2;
            `ALU_XOR:  o_alu_res = i_alu1 ^ i_alu2;
            `ALU_ADD:  o_alu_res = i_alu1 + i_alu2;
            `ALU_SUB:  o_alu_res = i_alu1 - i_alu2;
            `ALU_SL:   o_alu_res = i_alu1 << i_alu2[4:0];
            `ALU_SRL:  o_alu_res = i_alu1 >> i_alu2[4:0];
            `ALU_SRA:  o_alu_res = $signed(i_alu1) >>> i_alu2[4:0];
            `ALU_LT:   o_alu_res = ($signed(i_alu1) < $signed(i_alu2)) ? 32'd1 : 32'd0;
            `ALU_LTU:  o_alu_res = (i_alu1 < i_alu2) ? 32'd1 : 32'd0;
            `ALU_GTE:  o_alu_res = ($signed(i_alu1) >= $signed(i_alu2)) ? 32'd1 : 32'd0;
            `ALU_GTEU: o_alu_res = (i_alu1 >= i_alu2) ? 32'd1 : 32'd0;
            `ALU_EQ:   o_alu_res = (i_alu1 == i_alu2) ? 32'd1 : 32'd0;
            `ALU_NEQ:  o_alu_res = (i_alu1 != i_alu2) ? 32'd1 : 32'd0;
            default:   o_alu_res = '0;
        endcase
    end
endmodule
