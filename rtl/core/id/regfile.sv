/*
    文件名: regfile.v
    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
module regfile(
    input wire              i_clk,
    input wire              i_rst_n,
    input wire              i_we,
    input wire [`RF_BUS]    i_rs1_addr,
    input wire [`RF_BUS]    i_rs2_addr,
    input wire [`RF_BUS]    i_w_addr,
    input wire [`DATA_BUS]  i_w_data,
    output wire [`DATA_BUS] o_rs1_data,
    output wire [`DATA_BUS] o_rs2_data
);

endmodule
