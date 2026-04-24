`include "cpu_defines.svh"

module core_new_mem2_stage (
    input  logic [`DATA_BUS] i_dram_rdata,
    input  logic [3:0]       i_mem_size,
    input  logic             i_load_unsigned,
    output logic [`DATA_BUS] o_load_data
);
    core_new_load_data_align u_load_data_align (
        .i_dram_rdata    (i_dram_rdata),
        .i_mem_size      (i_mem_size),
        .i_load_unsigned (i_load_unsigned),
        .o_load_data     (o_load_data)
    );
endmodule
