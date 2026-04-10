`timescale 1ns / 1ps

/**
 * @module DRAM
 * @description 32-bit data RAM, depth 65536 words (256 KiB address space in words).
 *              Supports synchronous write and combinational read.
 *              Existing address decoding limits active window to 128 KiB in `perip_bridge`.
 */
module DRAM #(
    parameter int unsigned ADDR_WIDTH = 16,
    parameter int unsigned DATA_WIDTH = 32,
    parameter string INIT_FILE = "rtl/ip/dram.mem"
) (
    input  logic                  clk,
    input  logic [ADDR_WIDTH-1:0] a,
    output logic [DATA_WIDTH-1:0] spo,
    input  logic                  we,
    input  logic [DATA_WIDTH-1:0] d
);
    localparam int unsigned DEPTH = (1 << ADDR_WIDTH);

    logic [DATA_WIDTH-1:0] mem [0:DEPTH-1];

    initial begin
        $readmemh(INIT_FILE, mem);
    end

    always_ff @(posedge clk) begin
        if (we) begin
            mem[a] <= d;
        end
    end

    assign spo = mem[a];

endmodule
