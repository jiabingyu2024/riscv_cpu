//==============================================================================
// 模块: div_sim_model
// 功能概述：
//   除法器仿真模型，cycle-true 等价于 Xilinx Divider Generator v5.1
//   (Radix-2, Clocks/Div=1, Detect Divide-by-Zero) 在 32-bit 配置下的行为。
//   通过参数 LATENCY 选择 36（signed）或 34（unsigned）。
//   在 i_start 那拍采样 i_rs1/i_rs2 并立即按 RV32M 规范算出商和余数（行为级），
//   然后用倒计时延迟到第 LATENCY 拍才把结果驱动到 o_quot/o_rem，确保仿真和上板
//   的发出/完成时刻完全一致。
// 接口/协作审查（供采纳）：
//   - 仅作仿真；综合视图由 div_wrapper 通过 ifdef 切到真实 Xilinx IP。
//   - 仿真覆盖 RV32M 的两类异常：除零、INT_MIN/-1 溢出（仅 SIGNED=1 路径）。
//   - i_flush 在 inflight 中拉高可立即丢弃当前操作（避免错路径产生 done 脉冲）。
//==============================================================================
`include "cpu_defines.svh"

module div_sim_model #(
    parameter int LATENCY = 36,
    parameter bit SIGNED  = 1'b1
)(
    input  logic                            i_clk,
    input  logic                            i_rst_n,
    input  logic                            i_start,
    input  logic                            i_flush,
    input  logic  [`DATA_BUS]               i_rs1,
    input  logic  [`DATA_BUS]               i_rs2,

    output logic  [`DATA_BUS]               o_quot,
    output logic  [`DATA_BUS]               o_rem
);

    localparam int CNT_W = $clog2(LATENCY + 1);

    logic [CNT_W-1:0]    cnt;
    logic                busy;
    logic [`DATA_BUS]    quot_lat;
    logic [`DATA_BUS]    rem_lat;

    logic [`DATA_BUS]    quot_now;
    logic [`DATA_BUS]    rem_now;

    always_comb begin
        if (SIGNED) begin
            if (i_rs2 == 32'b0) begin
                quot_now = 32'hFFFF_FFFF;
                rem_now  = i_rs1;
            end else if ((i_rs1 == 32'h8000_0000) && (i_rs2 == 32'hFFFF_FFFF)) begin
                quot_now = 32'h8000_0000;
                rem_now  = 32'h0000_0000;
            end else begin
                quot_now = $signed(i_rs1) / $signed(i_rs2);
                rem_now  = $signed(i_rs1) % $signed(i_rs2);
            end
        end else begin
            if (i_rs2 == 32'b0) begin
                quot_now = 32'hFFFF_FFFF;
                rem_now  = i_rs1;
            end else begin
                quot_now = i_rs1 / i_rs2;
                rem_now  = i_rs1 % i_rs2;
            end
        end
    end

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            cnt      <= '0;
            busy     <= 1'b0;
            quot_lat <= '0;
            rem_lat  <= '0;
            o_quot   <= '0;
            o_rem    <= '0;
        end else if (i_flush) begin
            cnt   <= '0;
            busy  <= 1'b0;
        end else if (i_start && !busy) begin
            cnt      <= CNT_W'(LATENCY - 1);
            busy     <= 1'b1;
            quot_lat <= quot_now;
            rem_lat  <= rem_now;
        end else if (busy) begin
            cnt <= cnt - 1'b1;
            if (cnt == CNT_W'(1)) begin
                busy   <= 1'b0;
                o_quot <= quot_lat;
                o_rem  <= rem_lat;
            end
        end
    end

endmodule
