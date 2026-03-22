//==============================================================================
// 模块: hazard_unit
// 功能概述：
//   冒险处理单元。产生 load-use 停顿（stall）与分支预测失败/异常恢复时的流水线 flush；
//   输出下一拍 PC（o_pc_next）供 IF 使用，并与各级流水线寄存器的 i_stall/i_flush 配合。
// 接口/协作审查（供采纳）：
//   - i_predict_taken/i_predict_target：与 BPU 输出对齐，用于与 branch_cmp 的 error/right_pc 仲裁下一地址。
//   - i_rigit_pc 建议视为正确 PC（right_pc 拼写）；与 branch_cmp.o_rigit_pc 对接。
//   - 输出 4 级 stall/flush 需与 reg_* 命名一致；若某级恒不刷，实现时可 tie 0 但端口保留便于扩展。
//==============================================================================
`include "../../include/cpu_defines.sv"

module hazard_unit(
    input  logic  [`RF_BUS]                 i_rs1_addr_d,
    input  logic  [`RF_BUS]                 i_rs2_addr_d,
    input  logic  [`RF_BUS]                 i_rd_addr_e,
    input  logic                            i_mem_read_e,
    input  logic                            i_reg_write_e,//load_use

    input  logic                            i_predict_taken,
    input  logic  [`PC_BUS]                 i_predict_target,

    input  logic                            i_error,
    input  logic  [`PC_BUS]                 i_right_pc,

    output logic                            o_stall_f_d,
    output logic                            o_stall_d_e,
    output logic                            o_stall_e_m,
    output logic                            o_stall_m_w,

    output logic                            o_flush_f_d,
    output logic                            o_flush_d_e,
    output logic                            o_flush_e_m,
    output logic                            o_flush_m_w,

    output logic  [`PC_BUS]                 o_pc_next


);

endmodule