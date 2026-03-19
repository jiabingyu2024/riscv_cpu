/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module reg_id_ex(
    input logic                     i_clk,
    input logic                     i_rst_n,
    input logic                     i_flush,
    input logic                     i_stall,

    input logic [`DATA_BUS]         i_rs1_data,
    input logic [4:0]               i_rs1_addr,
    input logic [`DATA_BUS]         i_rs2_data,
    input logic [4:0]               i_rs2_addr,
    input logic [4:0]               i_rd_addr,

    input logic [`DATA_BUS]         i_imm,

    input logic                     i_mem_read,
    input logic                     i_reg_write,
    input logic                     i_mem_write,
    input logic                     i_wb_src,
    input logic                     i_alu2_src,  // 0: rs2, 1: imm
    input logic                     i_alu1_src,  // 0: rs1, 1: pc

    input logic [3:0]               i_alu_ctrl,
    input logic [2:0]               i_func3,

    input logic                     i_is_branch,
    input logic                     i_is_jump,
    input logic                     i_is_lui,
    input logic                     i_bcmp1_src, // 0: pc, 1: rs1   计算目标pc的bcmp的两个来源，bcmp2始终为imm
    input logic [`PC_BUS]           i_pc_d_e,
    input logic [`PC_BUS]           i_pc_predict,


    output logic [`DATA_BUS]        o_rs1_data,
    output logic [`DATA_BUS]        o_rs2_data,
    output logic [4:0]              o_rd_addr,
    output logic [4:0]              o_rs1_addr,
    output logic [4:0]              o_rs2_addr,

    output logic [`DATA_BUS]        o_imm,

    output logic                    o_mem_read,
    output logic                    o_reg_write,
    output logic                    o_mem_write,
    output logic                    o_wb_src,
    output logic                    o_alu2_src,
    output logic                    o_alu1_src,

    output logic [3:0]              o_alu_ctrl,
    output logic [2:0]              o_func3,

    output logic                    o_is_branch,
    output logic                    o_is_jump,
    output logic                    o_bcmp1_src,
    output logic [`PC_BUS]          o_pc_d_e,
    output logic [`PC_BUS]          o_pc_predict
);

endmodule