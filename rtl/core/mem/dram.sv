//==============================================================================
// 模块: dram
// 功能概述：
//   数据存储器（仿真/FPGA BRAM 或后续替换 AXI）。支持按 mask 的 store 与 load 读回（具体为字/半字/字节由 mask 定）。
// 接口/协作审查（供采纳）：
//   - 与 stage_mem 端口一致；`RAM_DEPTH`=4096 字时地址宽度与宏一致。
//   - 建议明确读写时序（同步读一拍 / 组合读）以便流水线时序闭合。
//==============================================================================
`include "../../include/cpu_defines.sv"

module dram (
    input logic                               i_clk,
    input logic                               i_rst_n,
    input logic                               i_mem_write,
    input logic [`RAM_ADDR_BUS]               i_mem_addr,
    input logic [`DATA_BUS]                   i_mem_wdata,
    input logic [1:0]                         i_mem_mask, // 见defines
    output logic [`DATA_BUS]                  o_mem_rdata
);

endmodule