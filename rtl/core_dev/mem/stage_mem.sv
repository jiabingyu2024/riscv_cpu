//==============================================================================
// 模块: stage_mem
// 功能概述：

//==============================================================================
`include "cpu_defines.svh"

module stage_mem (                  //仅例化dram即可
    input logic                               i_clk,
    input logic                               i_rst_n,
    input logic                               i_load_unsigned,
    inout logic [`DATA_BUS]                   i_dram_rdata,

    output logic [`DATA_BUS]                  o_mem_rdata
);

    logic [7:0]  load_byte;
    logic [15:0] load_half;


    assign load_byte = i_dram_rdata[7:0];
    assign load_half = i_dram_rdata[15:0];

    always_comb begin
        unique case (i_mem_mask)
            `MASK_BYTE: o_mem_rdata = i_load_unsigned ? {24'b0, load_byte} : {{24{load_byte[7]}}, load_byte};
            `MASK_HALF: o_mem_rdata = i_load_unsigned ? {16'b0, load_half} : {{16{load_half[15]}}, load_half};
            default:    o_mem_rdata = i_dram_rdata;
        endcase
    end
endmodule