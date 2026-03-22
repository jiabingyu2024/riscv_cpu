//==============================================================================
// 模块: stage_ex
// 功能概述：
//   执行（EX）级顶层。根据前递选择信号从 rs1/rs2/imm/pc、EX/M、M/W 结果中选择操作数，送 ALU；
//   分支类指令配合 branch_cmp 产生是否更新预测表、正确目标等；输出 ALU 结果供 MEM/WB 使用。
// 接口/协作审查（供采纳）：
//   - i_rs1_data/i_rs2_data 与 i_fwd_e_m/i_fwd_m_w 的分工：实现时需明确是否“原始寄存器值 + 旁路 MUX”在内部合并。
//   - o_updata_en 建议视为 o_update_en（拼写）；与 bpu_top 的 i_update_en 应对接。
//   - i_pc_d_e 与 i_pc：前者多为 ID/EX 寄存器中的 PC，后者为当前 EX 指令 PC，用于 AUIPC/JAL 等，团队需统一连法。
//==============================================================================
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
    output logic  [`DATA_BUS]               o_a2_data,

    output logic                            o_update_taken,
    output logic                            o_update_en,
    output logic  [`PC_BUS]                 o_update_pc,
    output logic  [`PC_BUS]                 o_update_target                
    
);

endmodule