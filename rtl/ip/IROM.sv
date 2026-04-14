`timescale 1ns / 1ps

/**
 * @module IROM
 * @description 32-bit instruction ROM, depth 4096 words (16 KiB).
 *              Addressed by word index `a` and returns combinational data on `spo`.
 *              Initialization uses `$readmemh` with a plain hex `.mem` file.
 */
module IROM #(
    parameter int unsigned ADDR_WIDTH = 12,
    parameter int unsigned DATA_WIDTH = 32,
    parameter string INIT_FILE = ""
) (
    input  logic [ADDR_WIDTH-1:0] a,
    output logic [DATA_WIDTH-1:0] spo
);
    localparam int unsigned DEPTH = (1 << ADDR_WIDTH);

    logic [DATA_WIDTH-1:0] mem [0:DEPTH-1];

    initial begin
        if (INIT_FILE != "") begin
            $readmemh(INIT_FILE, mem);
        end
    end

    assign spo = mem[a];

endmodule
