/*
core_top.v
例化各个模块，并连接信号

规范性要求：
    1. 例化模块加前缀 u_
    2. 连接pipeline_regs 的信号线均 命名为 F D E M W 例如： F_clk
    3. 顶层尽量不出现逻辑功能，仅做连线

*/
`include "../../include/cpu_defines.sv"

module core_top(
    input  logic        clk,
    input  logic        rst_n
);
endmodule