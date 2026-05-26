//==============================================================================
// 模块: mul_pipe
// 功能概述：
//   3 拍固定流水的 32x32 乘法器，覆盖 RV32M 中的 MUL/MULH/MULHSU/MULHU。
//   将 rs1/rs2 按 i_m_op 扩展到 33 bit（无符号补 0、有符号补符号位）后做
//   signed*signed 乘法；3 拍后根据指令选低 32 位（MUL）或高 32 位（MULH 系列）。
//   综合时三级寄存器期望被推断进 DSP48 内部流水（A/B reg → M reg → P reg）。
// 接口/协作审查（供采纳）：
//   - 无握手：i_start 拉单拍即可启动一次乘法，第 3 拍 o_res 稳定。
//   - 后续要改为 4 拍以适应 200MHz 时钟时，在 stage 之间加一级 FF 即可。
//   - 与 div_wrapper 配合时由 m_unit 用统一倒计时对齐到 36 拍。
//==============================================================================
`include "cpu_defines.svh"

module mul_pipe (
    input  logic                            i_clk,
    input  logic                            i_rst_n,
    input  logic                            i_start,
    input  logic  [`DATA_BUS]               i_rs1,
    input  logic  [`DATA_BUS]               i_rs2,
    input  logic  [`M_OP_BUS]               i_m_op,

    output logic  [`DATA_BUS]               o_res
);

    logic               rs1_sext;
    logic               rs2_sext;
    logic signed [32:0] a_ext_s1;
    logic signed [32:0] b_ext_s1;
    logic [`M_OP_BUS]   m_op_s1;
    logic               valid_s1;

    logic signed [65:0] mul_full_s2;
    logic [`M_OP_BUS]   m_op_s2;
    logic               valid_s2;

    always_comb begin
        unique case (i_m_op)
            `M_MUL:    begin rs1_sext = i_rs1[31]; rs2_sext = i_rs2[31]; end
            `M_MULH:   begin rs1_sext = i_rs1[31]; rs2_sext = i_rs2[31]; end
            `M_MULHSU: begin rs1_sext = i_rs1[31]; rs2_sext = 1'b0;      end
            `M_MULHU:  begin rs1_sext = 1'b0;      rs2_sext = 1'b0;      end
            default:   begin rs1_sext = 1'b0;      rs2_sext = 1'b0;      end
        endcase
    end

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            a_ext_s1 <= '0;
            b_ext_s1 <= '0;
            m_op_s1  <= '0;
            valid_s1 <= 1'b0;
        end else begin
            a_ext_s1 <= $signed({rs1_sext, i_rs1});
            b_ext_s1 <= $signed({rs2_sext, i_rs2});
            m_op_s1  <= i_m_op;
            valid_s1 <= i_start;
        end
    end

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            mul_full_s2 <= '0;
            m_op_s2     <= '0;
            valid_s2    <= 1'b0;
        end else begin
            mul_full_s2 <= a_ext_s1 * b_ext_s1;
            m_op_s2     <= m_op_s1;
            valid_s2    <= valid_s1;
        end
    end

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_res <= '0;
        end else if (valid_s2) begin
            unique case (m_op_s2)
                `M_MUL:    o_res <= mul_full_s2[31:0];
                `M_MULH:   o_res <= mul_full_s2[63:32];
                `M_MULHSU: o_res <= mul_full_s2[63:32];
                `M_MULHU:  o_res <= mul_full_s2[63:32];
                default:   o_res <= '0;
            endcase
        end
    end

endmodule
