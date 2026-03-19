/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module stage_ex(
    input  logic  [`DATA_BUS]               i_rs1_data,
    input  logic  [`DATA_BUS]               i_rs2_data,
    input  logic  [`DATA_BUS]               i_imm,
    input  logic  [`PC_BUS]                 i_pc,
    input  logic  [`DATA_BUS]               i_fwd_e_m,
    input  logic  [`DATA_BUS]               i_fwd_m_w,

    input  logic  [`PC_BUS]                 i_pc_d_e,
    input  logic  [`PC_BUS]                 i_pc_predict,

    input  logic                            i_alu1_src,
    input  logic                            i_alu2_src,

    input  logic  [3:0]                     i_alu_ctrl,
    input  logic  [2:0]                     i_func3,

    input  logic                            i_is_branch,
    input  logic                            i_is_jump,
    input  logic                            i_is_lui,
    input  logic                            i_bcmp1_src, // 0: pc, 1: rs1   计算目标pc的bcmp的两个来源，bcmp2始终为imm

    output logic  [`DATA_BUS]               o_alu_res,

    output logic                            o_hit,
    output logic                            o_hit_valid,
    output logic  [`PC_BUS]                 o_pc_target                    
    
);

endmodule