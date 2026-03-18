/*
    模块名: rom_instr
    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:
        此模块用于仿真指令ROM，输出指令的32位编码。后续被ip 替换

*/
module rom_instr(
    input  logic [`PC_BUS]              i_pc,
    output logic [`INST_BUS]            o_instr
);

endmodule