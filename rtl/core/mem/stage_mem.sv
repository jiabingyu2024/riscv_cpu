/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
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