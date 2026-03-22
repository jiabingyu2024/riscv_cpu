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

    input  logic  [1:0]                     i_b1_sel,
    input  logic  [1:0]                     i_b2_sel,
    input  logic  [1:0]                     i_t1_sel,
    input  logic  [1:0]                     i_a1_sel,
    input  logic  [1:0]                     i_a2_sel,

    input  logic  [3:0]                     i_alu_ctrl,
    input  logic  [2:0]                     i_func3,

    input  logic                            i_is_branch,
    // input  logic                            i_is_jtype,
    // input  logic                            i_is_lui,
    input  logic  [3:0]                     i_inst_spec,

    output logic  [`DATA_BUS]               o_alu_res,

    output logic                            o_update_taken,
    output logic                            o_updata_en,
    output logic  [`PC_BUS]                 o_update_pc,
    output logic  [`PC_BUS]                 o_update_target                
    
);

endmodule