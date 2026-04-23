`timescale 1ns / 1ps

module IROM #(
    parameter int unsigned ADDR_WIDTH = 12,
    parameter int unsigned DATA_WIDTH = 32
) (
    input  logic [ADDR_WIDTH-1:0] a,
    output logic [DATA_WIDTH-1:0] spo
);
    localparam int unsigned DEPTH = 1 << ADDR_WIDTH;

    logic [DATA_WIDTH-1:0] mem [0:DEPTH-1];

    assign spo = mem[a];
endmodule
