//==============================================================================
// 模块: stage_mem
// 功能概述：
//   访存（MEM）级封装。内部例化 dram，将 EX/MEM 给出的地址、写数据、mask 转为对数据 RAM 的访问，
//   读出 load 数据供 WB 使用。
// 接口/协作审查（供采纳）：
//   - 当前仅有 i_mem_write；若使用同步读 SRAM，可视需要增加 i_mem_read 或字节使能（团队约定）。
//   - i_mem_addr 为 `RAM_ADDR_BUS`；需与 ALU 结果/对齐方式（字对齐地址 vs 字索引）一致。
//==============================================================================
`include "cpu_defines.svh"

module stage_mem (                  //仅例化dram即可
    input logic                               i_clk,
    input logic                               i_rst_n,
    input logic                               i_mem_write,
    input logic [`RAM_ADDR_BUS]               i_mem_addr,
    input logic [`DATA_BUS]                   i_mem_wdata,
    input logic [1:0]                         i_mem_mask, // 见defines
    input logic                               i_load_unsigned,

    input  logic  [`DATA_BUS]                  i_dram_rdata,
    output logic                               o_dram_wen,
    output logic  [`RAM_ADDR_BUS]              o_dram_addr,
    output logic  [`DATA_BUS]                  o_dram_wdata,
    output logic  [1:0]                        o_dram_mask,

    output logic [`DATA_BUS]                  o_mem_rdata
);

    logic [1:0]  byte_off;
    logic [7:0]  load_byte;
    logic [15:0] load_half;

    assign o_dram_wen   = i_mem_write;
    assign o_dram_addr  = i_mem_addr;
    assign o_dram_wdata = i_mem_wdata;
    assign o_dram_mask  = i_mem_mask;

    assign byte_off  = i_mem_addr[1:0];
    assign load_byte = i_dram_rdata >> (byte_off * 8);
    assign load_half = i_dram_rdata >> ({byte_off[1], 4'b0000});

    always_comb begin
        unique case (i_mem_mask)
            `MASK_BYTE: o_mem_rdata = i_load_unsigned ? {24'b0, load_byte} : {{24{load_byte[7]}}, load_byte};
            `MASK_HALF: o_mem_rdata = i_load_unsigned ? {16'b0, load_half} : {{16{load_half[15]}}, load_half};
            default:    o_mem_rdata = i_dram_rdata;
        endcase
    end
endmodule