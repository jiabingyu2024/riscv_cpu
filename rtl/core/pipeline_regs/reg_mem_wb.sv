/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module reg_mem_wb(
    input  logic                         i_clk,
    input  logic                         i_rst_n,
    input  logic                         i_flush,
    input  logic                         i_stall,

    input  logic                         i_reg_write,
    input  logic                         i_wb_src,

    input  logic [`DATA_BUS]             i_alu_res,
    input  logic [`RF_BUS]               i_rd_addr,
    input  logic [`DATA_BUS]             i_mem_data,

    output logic [`DATA_BUS]             o_alu_res,
    output logic [`RF_BUS]               o_rd_addr,
    output logic [`DATA_BUS]             o_mem_data,

    output logic                         o_wb_src,
    output logic                         o_reg_write


);

endmodule