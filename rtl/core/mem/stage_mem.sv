//==============================================================================
// 模块: stage_mem
// 功能概述：
//   访存（MEM）级封装。内部例化 dram，将 EX/MEM 给出的地址、写数据、mask 转为对数据 RAM 的访问，
//   读出 load 数据供 WB 使用。
// 接口/协作审查（供采纳）：
//   - 当前仅有 i_mem_write；若使用同步读 SRAM，可视需要增加 i_mem_read 或字节使能（团队约定）。
//   - i_mem_addr 为 `RAM_ADDR_BUS`；需与 ALU 结果/对齐方式（字对齐地址 vs 字索引）一致。
//==============================================================================
`include "../../include/cpu_defines.sv"

module stage_mem (                  //仅例化dram即可
    input logic                               i_clk,
    input logic                               i_rst_n,
    input logic                               i_mem_write,
    input logic [`RAM_ADDR_BUS]               i_mem_addr,
    input logic [`DATA_BUS]                   i_mem_wdata,
    input logic [1:0]                         i_mem_mask, // 见defines
    output logic [`DATA_BUS]                  o_mem_rdata
);

endmodule