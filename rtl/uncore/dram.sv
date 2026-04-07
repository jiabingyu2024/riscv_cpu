//==============================================================================
// 模块: dram
// 功能概述：
//   数据存储器（仿真/FPGA BRAM 或后续替换 AXI）。支持按 mask 的 store 与 load 读回（具体为字/半字/字节由 mask 定）。
// 接口/协作审查（供采纳）：
//   - 与 stage_mem 端口一致；`RAM_DEPTH`=4096 字时地址宽度与宏一致。
//   - 建议明确读写时序（同步读一拍 / 组合读）以便流水线时序闭合。
//==============================================================================
`include "cpu_defines.svh"

module dram #(
    parameter string INIT_FILE = ""
) (
    input logic                               i_clk,
    input logic                               i_rst_n,
    input logic                               i_mem_write,
    input logic [`RAM_ADDR_BUS]               i_mem_addr,
    input logic [`DATA_BUS]                   i_mem_wdata,
    input logic [1:0]                         i_mem_mask, // 见defines
    output logic [`DATA_BUS]                  o_mem_rdata
);

    localparam int WORD_DEPTH = (`RAM_DEPTH / 4);
    localparam int WORD_ADDR_WID = $clog2(WORD_DEPTH);

    logic [`DATA_BUS] mem_words [0:WORD_DEPTH-1];
    logic [WORD_ADDR_WID-1:0] word_addr;
    logic [1:0] byte_off;
    logic [`DATA_BUS] cur_word;
    logic [`DATA_BUS] write_data_shifted;
    logic [`DATA_BUS] write_mask;
    logic [`DATA_BUS] merged_word;
    string load_file;
    integer idx;

    assign word_addr = i_mem_addr[`RAM_ADDR_WID-1:2];
    assign byte_off = i_mem_addr[1:0];
    assign cur_word = mem_words[word_addr];
    assign write_data_shifted = i_mem_wdata << (byte_off * 8);

    always_comb begin
        unique case (i_mem_mask)
            `MASK_BYTE: write_mask = 32'h0000_00ff << (byte_off * 8);
            `MASK_HALF: write_mask = 32'h0000_ffff << (byte_off * 8);
            default:    write_mask = 32'hffff_ffff;
        endcase
    end

    assign merged_word = (cur_word & ~write_mask) | (write_data_shifted & write_mask);

    initial begin
        for (idx = 0; idx < WORD_DEPTH; idx = idx + 1) begin
            mem_words[idx] = '0;
        end

        load_file = INIT_FILE;
        if (!$value$plusargs("DRAM=%s", load_file)) begin
            load_file = INIT_FILE;
        end

        if (load_file != "") begin
            $readmemh(load_file, mem_words);
        end
    end

    always @(posedge i_clk) begin
        if (i_mem_write) begin
            mem_words[word_addr] <= merged_word;
        end
    end

    always_comb begin
        unique case (i_mem_mask)
            `MASK_BYTE: o_mem_rdata = {24'b0, cur_word[byte_off*8 +: 8]};
            `MASK_HALF: o_mem_rdata = {16'b0, cur_word[byte_off[1]*16 +: 16]};
            default:    o_mem_rdata = cur_word;
        endcase
    end
endmodule