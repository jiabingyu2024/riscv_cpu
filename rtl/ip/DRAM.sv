`timescale 1ns / 1ps

module DRAM #(
    parameter int unsigned ADDR_WIDTH = 16,
    parameter int unsigned DATA_WIDTH = 32
) (
    input  logic                  clk,
    input  logic [ADDR_WIDTH-1:0] a,
    output logic [DATA_WIDTH-1:0] spo,
    input  logic                  we,
    input  logic [DATA_WIDTH-1:0] d
);
    localparam int unsigned DEPTH = 1 << ADDR_WIDTH;

    logic [DATA_WIDTH-1:0] mem [0:DEPTH-1];

    assign spo = mem[a];

    always_ff @(posedge clk) begin
        if (we) begin
            mem[a] <= d;
        end
    end
endmodule
