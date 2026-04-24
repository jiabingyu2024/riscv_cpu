`include "cpu_defines.svh"

module core_new_wb_stage (
    input  logic             i_wb_sel,
    input  logic [`DATA_BUS] i_alu_res,
    input  logic [`DATA_BUS] i_load_data,
    output logic [`DATA_BUS] o_wb_data
);
    always_comb begin
        o_wb_data = (i_wb_sel == `WB_SRC_MEM) ? i_load_data : i_alu_res;
    end
endmodule
