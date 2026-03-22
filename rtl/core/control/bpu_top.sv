//==============================================================================
// 模块: bpu_top
// 功能概述：
//   分支预测器顶层（BTB/BHT 等具体结构在内部实现）。根据当前 PC 给出是否预测跳转及目标地址；
//   在分支解析后根据 i_update_en、i_update_taken、i_update_pc、i_update_target 更新表项。
// 接口/协作审查（供采纳）：
//   - **i_pc_cur 当前声明为 1 位 logic，应为 `PC_BUS` 宽度的取指 PC**，否则无法索引 BTB/预测 RAM。
//   - i_update_* 与 branch_cmp/stage_ex 输出对接时序需约定（EX 级更新或 WB 级更新）。
//==============================================================================
/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module bpu_top (
    input  logic                                    i_clk,
    input  logic                                    i_rst_n,

    input  logic  [`PC_BUS]                         i_pc_cur,

    input  logic                                    i_update_en,
    input  logic                                    i_update_taken,
    input  logic  [`PC_BUS]                         i_update_target,
    input  logic  [`PC_BUS]                         i_update_pc,
    
    output logic                                    o_predict_taken,
    output logic  [`PC_BUS]                         o_predict_target
);

endmodule