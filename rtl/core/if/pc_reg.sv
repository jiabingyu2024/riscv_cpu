/*
pc_reg.v

生成 pc 寄存器，用于保存当前指令地址。
    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:
        实现一个 pc 寄存器，用于保存当前指令地址.

*/

module pc_reg(
    input  logic                     i_clk,
    input  logic                     i_rst_n,
    input  logic   [`PC_BUS]         i_pc_next,    
    output logic   [`PC_BUS]         o_pc_cur         // 输出当前指令地址
);

    
endmodule