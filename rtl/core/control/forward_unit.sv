/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module forward_unit (

    input  logic  [`RF_BUS]                 i_rs1_addr,
    input  logic  [`RF_BUS]                 i_rs2_addr,
    input  logic  [`RF_BUS]                 i_rd_addr_e_m,
    input  logic  [`RF_BUS]                 i_rd_addr_m_w,

    input  logic                            i_reg_write_e_m,
    input  logic                            i_reg_write_m_w,

    input  logic                            i_is_rs2_imm,
    input  logic  [3:0]                     i_inst_spec,



    output logic  [1:0]                     o_b1_sel,
    output logic  [1:0]                     o_b2_sel,
    output logic  [1:0]                     o_t1_sel,
    output logic  [1:0]                     o_a1_sel,
    output logic  [1:0]                     o_a2_sel
);

endmodule