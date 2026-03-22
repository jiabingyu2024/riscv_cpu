/*

    规范性要求:
        1. 输入输出端口信号均加前缀 "i_" 或 "o_"，以区分输入输出信号。
        2. 信号名全部小写，单词之间用下划线连接。
        3. 注意运用cpu_defines.v中的宏定义，增强可读性
    功能要求:

*/
`include "../../include/cpu_defines.sv"

module branch_cmp(
    input  logic  [`DATA_BUS]               i_b1_data,
    input  logic  [`DATA_BUS]               i_b2_data,
    input  logic  [2:0]                     i_func3,

    input  logic  [`PC_BUS]                 i_pc_d_e,
    input  logic  [`PC_BUS]                 i_pc_predict,

    input  logic  [`PC_BUS]                 i_t1_data,
    input  logic  [`PC_BUS]                 i_t2_data,

    input  logic                            i_is_branch,
    // input  logic                            i_is_jtype,
    input  logic  [3:0]                     i_inst_spec,

    output logic                            o_update_taken,  // for BTB BHB
    output logic                            o_updata_en,
    output logic  [`PC_BUS]                 o_update_pc,
    output logic  [`PC_BUS]                 o_update_target,

    output logic                            o_error,          // for hazard_unit
    output logic  [`PC_BUS]                 o_rigit_pc
);

endmodule