//==============================================================================
// 模块: div_wrapper
// 功能概述：
//   除法器封装层。例化自研 div_srt_r4（固定 17 拍 Radix-4 SRT 除法器），
//   仿真与综合走同一份 RTL，cycle 严格相等，不再依赖 Xilinx Divider Generator IP。
//   wrapper 内根据 i_m_op 译出 i_signed（DIV/REM=1，DIVU/REMU=0），并把唯一一组
//   {o_quot, o_rem} 与 o_done 透传给上层 m_unit。
// 接口/协作审查（供采纳）：
//   - 端口相对旧版（4 路 quot_s/rem_s/quot_u/rem_u）已合并为单路 quot/rem，
//     上层 m_unit 末段 mux 同步精简。
//   - o_done 暴露给 m_unit，但当前 m_unit 仍用其内置倒计时统一发 done；
//     乱序后端接入时可直接采本 o_done 做精确 wakeup。
//   - i_flush 透传至 div_srt_r4：inflight 操作立即丢弃，不产生 o_done。
//==============================================================================
`include "cpu_defines.svh"

module div_wrapper (
    input  logic                    i_clk,
    input  logic                    i_rst_n,
    input  logic                    i_start,
    input  logic                    i_flush,
    input  logic  [`M_OP_BUS]       i_m_op,
    input  logic  [`DATA_BUS]       i_rs1,
    input  logic  [`DATA_BUS]       i_rs2,

    output logic  [`DATA_BUS]       o_quot,
    output logic  [`DATA_BUS]       o_rem,
    output logic                    o_done
);

    // DIV/REM 走 signed 路径；DIVU/REMU 走 unsigned 路径
    logic is_signed;
    assign is_signed = (i_m_op == `M_DIV) || (i_m_op == `M_REM);

    div_srt_r4 u_div (
        .i_clk    (i_clk),
        .i_rst_n  (i_rst_n),
        .i_start  (i_start),
        .i_flush  (i_flush),
        .i_signed (is_signed),
        .i_rs1    (i_rs1),
        .i_rs2    (i_rs2),
        .o_quot   (o_quot),
        .o_rem    (o_rem),
        .o_done   (o_done)
    );

endmodule
