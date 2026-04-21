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
`include "cpu_defines.svh"

module stage_ex(
    input  logic  [`DATA_BUS]               i_rs1_data,
    input  logic  [`DATA_BUS]               i_rs2_data,
    input  logic  [`DATA_BUS]               i_imm,
    input  logic  [`PC_BUS]                 i_pc,
    input  logic  [`DATA_BUS]               i_fwd_e_m,
    input  logic  [`DATA_BUS]               i_fwd_m_w,
    input  logic  [`DATA_BUS]               i_fwd_m_m,   //新增一个EX/MEM的前递数据输入

    input  logic  [`PC_BUS]                 i_pc_d_e,
    input  logic  [`PC_BUS]                 i_pc_predict,

    input  logic  [2:0]                     i_b1_sel,   //均增加一个i_fwd_m_m,同时修改 cpu_defines.svh
    input  logic  [2:0]                     i_b2_sel,
    input  logic  [2:0]                     i_t1_sel,
    input  logic  [2:0]                     i_a1_sel,
    input  logic  [2:0]                     i_a2_sel,

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
    output logic  [`PC_BUS]                 o_update_target,
    output logic                            o_error,
    output logic  [`PC_BUS]                 o_right_pc
    
);

    logic [`DATA_BUS] b1_data;
    logic [`DATA_BUS] b2_data;
    logic [`DATA_BUS] a1_data;
    logic [`DATA_BUS] a2_data;
    logic [`PC_BUS]   t1_data;
    logic [`DATA_BUS] alu_res_raw;

    always_comb begin
        unique case (i_b1_sel)
            `B1_E_M:   b1_data = i_fwd_e_m;
            `B1_M_W:   b1_data = i_fwd_m_w;
            `B1_M_M:   b1_data = i_fwd_m_m;
            default:   b1_data = i_rs1_data;
        endcase

        unique case (i_b2_sel)
            `B2_E_M:   b2_data = i_fwd_e_m;
            `B2_M_W:   b2_data = i_fwd_m_w;
            `B2_M_M:   b2_data = i_fwd_m_m;
            default:   b2_data = i_rs2_data;
        endcase

        unique case (i_t1_sel)
            `T1_RS1:   t1_data = i_rs1_data;
            `T1_E_M:   t1_data = i_fwd_e_m;
            `T1_M_W:   t1_data = i_fwd_m_w;
            `T1_M_M:   t1_data = i_fwd_m_m;
            default:   t1_data = i_pc_d_e;
        endcase

        unique case (i_a1_sel)
            `A1_E_M:   a1_data = i_fwd_e_m;
            `A1_M_W:   a1_data = i_fwd_m_w;
            `A1_M_M:   a1_data = i_fwd_m_m;
            `A1_PC:    a1_data = i_pc;
            default:   a1_data = i_rs1_data;
        endcase

        unique case (i_a2_sel)
            `A2_E_M:   a2_data = i_fwd_e_m;
            `A2_M_W:   a2_data = i_fwd_m_w;
            `A2_M_M:   a2_data = i_fwd_m_m;
            `A2_imm:   a2_data = i_imm;
            default:   a2_data = i_rs2_data;
        endcase
    end

    alu u_alu (
        .i_alu1     (a1_data),
        .i_alu2     (a2_data),
        .i_alu_ctrl (i_alu_ctrl),
        .o_alu_res  (alu_res_raw)
    );

    branch_cmp u_branch_cmp (
        .i_b1_data       (b1_data),
        .i_b2_data       (b2_data),
        .i_func3         (i_func3),
        .i_pc_d_e        (i_pc_d_e),
        .i_pc_predict    (i_pc_predict),
        .i_t1_data       (t1_data),
        .i_t2_data       (i_imm),
        .i_is_branch     (i_is_branch),
        .i_inst_spec     (i_inst_spec),
        .o_update_taken  (o_update_taken),
        .o_update_en     (o_update_en),
        .o_update_pc     (o_update_pc),
        .o_update_target (o_update_target),
        .o_error         (o_error),
        .o_right_pc      (o_right_pc)
    );

    always_comb begin
        o_a2_data = b2_data;

        unique case (i_inst_spec)
            `EX_LUI:   o_alu_res = i_imm;
            `EX_JAL,
            `EX_JALR:  o_alu_res = i_pc + 32'd4;
            default:     o_alu_res = alu_res_raw;
        endcase
    end
endmodule
