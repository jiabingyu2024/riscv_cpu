/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module reg_if_id(
    input logic              i_clk,
    input logic              i_rst_n,
    input logic              i_flush,
    input logic              i_stall,
    
    input logic [`PC_BUS]    i_pc_f_d,
    input logic [`INST_BUS]  i_inst_f_d,
    input logic [`PC_BUS]    i_pc_predict,


    output logic [`PC_BUS]   o_pc_f_d,
    output logic [`INST_BUS] o_inst_f_d,
    output logic [`PC_BUS]   o_pc_predict,
);
endmodule