`include "cpu_defines.svh"

module core_new_hazard_ctrl (
    input  logic [`RF_BUS] i_id_rs1,
    input  logic [`RF_BUS] i_id_rs2,
    input  logic [`RF_BUS] i_ex_rd,
    input  logic           i_ex_mem_read,
    input  logic [`RF_BUS] i_m1_rd,
    input  logic           i_m1_mem_read,
    output logic           o_load_use_stall
);
    logic hit_ex;
    logic hit_m1;

    assign hit_ex = i_ex_mem_read && (i_ex_rd != '0) &&
                    ((i_ex_rd == i_id_rs1) || (i_ex_rd == i_id_rs2));
    assign hit_m1 = i_m1_mem_read && (i_m1_rd != '0) &&
                    ((i_m1_rd == i_id_rs1) || (i_m1_rd == i_id_rs2));
    assign o_load_use_stall = hit_ex || hit_m1;
endmodule
