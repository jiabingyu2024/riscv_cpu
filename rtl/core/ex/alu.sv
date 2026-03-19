/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module alu(
    input  logic [`DATA_BUS]                i_alu1,
    input  logic [`DATA_BUS]                i_alu2,
    input  logic [3:0]                      i_alu_ctrl,
    
    output logic [`DATA_BUS]                o_alu_res
);

endmodule