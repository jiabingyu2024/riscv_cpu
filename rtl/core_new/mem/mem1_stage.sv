`include "cpu_defines.svh"

module core_new_mem1_stage (
    input  logic [`DATA_BUS]     i_alu_res,
    input  logic [`DATA_BUS]     i_store_data,
    input  logic                 i_mem_write,
    input  logic [3:0]           i_mem_size,
    output logic                 o_dram_wen,
    output logic [`RAM_ADDR_BUS] o_dram_addr,
    output logic [`DATA_BUS]     o_dram_wdata,
    output logic [3:0]           o_dram_mask
);
    assign o_dram_wen   = i_mem_write;
    assign o_dram_addr  = i_alu_res[`RAM_ADDR_BUS];
    assign o_dram_wdata = i_store_data;
    assign o_dram_mask  = i_mem_size;
endmodule
