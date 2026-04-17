`timescale 1ns / 1ps

/**
 * @module DRAM
 * @description 32-bit data RAM, depth 65536 words (256 KiB address space in words).
 *              Registers word address on the rising clock edge, reads by that
 *              registered address, and handles byte/half/word mask internally.
 *              Existing address decoding limits active window to 128 KiB in `perip_bridge`.
 */
module DRAM #(
    parameter int unsigned ADDR_WIDTH = 18,
    parameter int unsigned DATA_WIDTH = 32,
    parameter string INIT_FILE = ""
) (
    input  logic                  clk,
    input  logic [ADDR_WIDTH-1:0] a,
    output logic [DATA_WIDTH-1:0] spo,
    input  logic                  we,
    input  logic [DATA_WIDTH/8-1:0] mask,
    input  logic [DATA_WIDTH-1:0] d
);
    localparam int unsigned BYTE_COUNT = DATA_WIDTH / 8;
    localparam int unsigned BYTE_OFFSET_WIDTH = $clog2(BYTE_COUNT);
    localparam int unsigned WORD_ADDR_WIDTH = ADDR_WIDTH - BYTE_OFFSET_WIDTH;
    localparam int unsigned DEPTH = (1 << WORD_ADDR_WIDTH);

    logic [DATA_WIDTH-1:0] mem [0:DEPTH-1];
    logic [WORD_ADDR_WIDTH-1:0] word_addr;
    logic [BYTE_OFFSET_WIDTH-1:0] offset, offset_q;
    logic [DATA_WIDTH-1:0] wdata;
    logic [DATA_WIDTH-1:0] rdata;
    logic [WORD_ADDR_WIDTH-1:0] addr_q;
    logic [BYTE_COUNT-1:0] byte_we;
    logic [BYTE_COUNT-1:0] mask_q;

    assign word_addr = a[ADDR_WIDTH-1:BYTE_OFFSET_WIDTH];
    assign offset = a[BYTE_OFFSET_WIDTH-1:0];

    initial begin
        if (INIT_FILE != "") begin
            $readmemh(INIT_FILE, mem);
        end
    end

    always_comb begin
        byte_we = '0;
        wdata = '0;

        if (we) begin
            unique case (mask)
                4'b0001: begin
                    byte_we = 4'b0001 << offset;
                    unique case (offset)
                        2'b00: wdata = {24'b0, d[7:0]};
                        2'b01: wdata = {16'b0, d[7:0], 8'b0};
                        2'b10: wdata = {8'b0, d[7:0], 16'b0};
                        2'b11: wdata = {d[7:0], 24'b0};
                    endcase
                end
                4'b0011: begin
                    byte_we = offset[1] ? 4'b1100 : 4'b0011;
                    wdata = offset[1] ? {d[15:0], 16'b0} : {16'b0, d[15:0]};
                end
                4'b1111: begin
                    byte_we = 4'b1111;
                    wdata = d;
                end
                default: begin
                    byte_we = '0;
                    wdata = '0;
                end
            endcase
        end
    end

    always_ff @(posedge clk) begin
        addr_q <= word_addr;
        offset_q <= offset;
        mask_q <= mask;
        for (int idx = 0; idx < BYTE_COUNT; idx++) begin
            if (byte_we[idx]) begin
                mem[word_addr][idx*8 +: 8] <= wdata[idx*8 +: 8];
            end
        end
    end

    always_comb begin
        rdata = mem[addr_q];
        spo = '0;

        unique case (mask_q)
            4'b0001: begin
                unique case (offset_q)
                    2'b00: spo = {24'b0, rdata[7:0]};
                    2'b01: spo = {24'b0, rdata[15:8]};
                    2'b10: spo = {24'b0, rdata[23:16]};
                    2'b11: spo = {24'b0, rdata[31:24]};
                endcase
            end
            4'b0011: spo = offset_q[1] ? {16'b0, rdata[31:16]} : {16'b0, rdata[15:0]};
            4'b1111: spo = rdata;
            default: spo = '0;
        endcase
    end

endmodule
