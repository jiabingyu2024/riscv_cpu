`include "cpu_defines.svh"

module core_new_load_data_align (
    input  logic [`DATA_BUS] i_dram_rdata,
    input  logic [3:0]       i_mem_size,
    input  logic             i_load_unsigned,
    output logic [`DATA_BUS] o_load_data
);
    logic [7:0]  load_byte;
    logic [15:0] load_half;

    assign load_byte = i_dram_rdata[7:0];
    assign load_half = i_dram_rdata[15:0];

    always_comb begin
        unique case (i_mem_size)
            `MASK_BYTE: o_load_data = i_load_unsigned ? {24'b0, load_byte} : {{24{load_byte[7]}}, load_byte};
            `MASK_HALF: o_load_data = i_load_unsigned ? {16'b0, load_half} : {{16{load_half[15]}}, load_half};
            default:    o_load_data = i_dram_rdata;
        endcase
    end
endmodule
