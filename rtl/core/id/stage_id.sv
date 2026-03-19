/*
control_unit.v

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module stage_id(
    input  logic  [`PC_BUS]                 i_pc_f_d,
    input  logic  [`INST_BUS]               i_inst_f_d,
    input  logic  [`PC_BUS]                 i_pc_predict,

    input  logic                            i_we,
    input  logic  [`RF_BUS]                 i_w_addr,
    input  logic  [`DATA_BUS]               i_w_data,

    output logic                            o_mem_read,   // from control
    output logic                            o_mem_write,
    output logic                            o_reg_write,
    output logic                            o_wb_src,
    output logic                            o_alu1_src,
    output logic                            o_alu2_src,

    output logic  [3:0]                     o_alu_ctrl,
    output logic  [2:0]                     o_func3,

    output logic                            o_is_branch,
    output logic                            o_is_jump,
    output logic                            o_is_lui,
    output logic                            o_bcmp1_src,

    output logic  [`DATA_BUS]               o_imm,
    output logic  [`DATA_BUS]               o_rs1_data,
    output logic  [4:0]                     o_rs1_addr,
    output logic  [`DATA_BUS]               o_rs2_data,
    output logic  [4:0]                     o_rs2_addr,
    output logic  [4:0]                     o_rd_addr,
);

endmodule