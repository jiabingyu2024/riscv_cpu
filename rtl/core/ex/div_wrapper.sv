//==============================================================================
// 模块: div_wrapper
// 功能概述：
//   除法器封装层。i_start 拉单拍后同时启动两条独立的除法器实例：signed 路径
//   （LATENCY=36）服务 DIV/REM；unsigned 路径（LATENCY=34）服务 DIVU/REMU。
//   unsigned 路径的商/余数通过两级 FF 拖到第 36 拍，使四路结果在同一拍齐发，
//   由上层 m_unit 按 i_m_op 选取。
//   仿真使用 div_sim_model（行为级 + 倒计时）；综合时通过 SYNTHESIS 宏切到
//   Xilinx Divider Generator IP（div_32_signed_36 / div_32_unsigned_34）。
// 接口/协作审查（供采纳）：
//   - 不暴露 done：上层 m_unit 自带 36 拍倒计时统一对齐。
//   - i_flush 仅在仿真路径生效（行为模型支持丢弃）。综合路径 IP 内部状态会
//     被后续 i_start 覆盖，本工程不接 ARESETN。
//   - 四个输出 quot_s/rem_s/quot_u/rem_u 在第 36 拍同时有效，外部 mux 选用。
//==============================================================================
`include "cpu_defines.svh"

module div_wrapper (
    input  logic                            i_clk,
    input  logic                            i_rst_n,
    input  logic                            i_start,
    input  logic                            i_flush,
    input  logic  [`DATA_BUS]               i_rs1,
    input  logic  [`DATA_BUS]               i_rs2,

    output logic  [`DATA_BUS]               o_quot_s,
    output logic  [`DATA_BUS]               o_rem_s,
    output logic  [`DATA_BUS]               o_quot_u,
    output logic  [`DATA_BUS]               o_rem_u
);

    logic [`DATA_BUS] quot_s_raw;
    logic [`DATA_BUS] rem_s_raw;
    logic [`DATA_BUS] quot_u_raw;
    logic [`DATA_BUS] rem_u_raw;

`ifdef SYNTHESIS
    // ---- for synthesis: Xilinx Divider Generator IP ----
    logic [63:0] dout_s_tdata;
    logic [63:0] dout_u_tdata;

    div_32_signed_36 u_div_s (
        .aclk                   (i_clk),
        .s_axis_dividend_tvalid (i_start),
        .s_axis_dividend_tdata  (i_rs1),
        .s_axis_divisor_tvalid  (i_start),
        .s_axis_divisor_tdata   (i_rs2),
        .m_axis_dout_tvalid     (),
        .m_axis_dout_tdata      (dout_s_tdata)
    );

    div_32_unsigned_34 u_div_u (
        .aclk                   (i_clk),
        .s_axis_dividend_tvalid (i_start),
        .s_axis_dividend_tdata  (i_rs1),
        .s_axis_divisor_tvalid  (i_start),
        .s_axis_divisor_tdata   (i_rs2),
        .m_axis_dout_tvalid     (),
        .m_axis_dout_tdata      (dout_u_tdata)
    );

    assign quot_s_raw = dout_s_tdata[63:32];
    assign rem_s_raw  = dout_s_tdata[31:0];
    assign quot_u_raw = dout_u_tdata[63:32];
    assign rem_u_raw  = dout_u_tdata[31:0];
`else
    // ---- only for simulation ----
    div_sim_model #(.LATENCY(36), .SIGNED(1'b1)) u_div_s (
        .i_clk   (i_clk),
        .i_rst_n (i_rst_n),
        .i_start (i_start),
        .i_flush (i_flush),
        .i_rs1   (i_rs1),
        .i_rs2   (i_rs2),
        .o_quot  (quot_s_raw),
        .o_rem   (rem_s_raw)
    );

    div_sim_model #(.LATENCY(34), .SIGNED(1'b0)) u_div_u (
        .i_clk   (i_clk),
        .i_rst_n (i_rst_n),
        .i_start (i_start),
        .i_flush (i_flush),
        .i_rs1   (i_rs1),
        .i_rs2   (i_rs2),
        .o_quot  (quot_u_raw),
        .o_rem   (rem_u_raw)
    );
`endif

    assign o_quot_s = quot_s_raw;
    assign o_rem_s  = rem_s_raw;

    logic [`DATA_BUS] quot_u_d1, rem_u_d1;

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            quot_u_d1 <= '0;
            rem_u_d1  <= '0;
            o_quot_u  <= '0;
            o_rem_u   <= '0;
        end else begin
            quot_u_d1 <= quot_u_raw;
            rem_u_d1  <= rem_u_raw;
            o_quot_u  <= quot_u_d1;
            o_rem_u   <= rem_u_d1;
        end
    end

endmodule
