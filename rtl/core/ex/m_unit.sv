//==============================================================================
// 模块: m_unit
// 功能概述：
//   RV32M 计算单元顶层。例化 mul_pipe（3 拍）与 div_wrapper（自研 Radix-4 SRT，
//   固定 17 拍）。对外延迟按指令类型区分：mul 类 3 拍、div 类 17 拍，由 i_m_op[2]
//   区分（0=mul / 1=div）。i_start 拉单拍启动一次操作，期间 o_busy 保持高电平
//   阻止新指令进入；倒计时到 0 那拍 o_done 单拍脉冲，o_res 同拍稳定。
// 接口/协作审查（供采纳）：
//   - i_flush：上层（stage_ex）在分支误测/异常时拉高，丢弃当前 m 操作。
//   - mul/div 延迟不一致，stage_ex 直接以 o_busy 长度决定 stall 周期，无需感知。
//   - 仿真/综合的 cycle 数严格相等，由 div_srt_r4 的纯 RTL 实现保证。
//   - 乱序后端接入时可改为采用各单元自己的 done 脉冲（mul_pipe 末拍 / div_wrapper
//     的 o_done）做精确 wakeup，本顶层倒计时即可拆掉。
//==============================================================================
`include "cpu_defines.svh"

module m_unit (
    input  logic                            i_clk,
    input  logic                            i_rst_n,
    input  logic                            i_start,
    input  logic                            i_flush,
    input  logic  [`DATA_BUS]               i_rs1,
    input  logic  [`DATA_BUS]               i_rs2,
    input  logic  [`M_OP_BUS]               i_m_op,

    output logic                            o_busy,
    output logic                            o_done,
    output logic  [`DATA_BUS]               o_res
);

    localparam int MUL_LATENCY = `MUL_LATENCY;
    localparam int DIV_LATENCY = `DIV_LATENCY_R4;
    localparam int CNT_W       = $clog2(DIV_LATENCY + 1);

    logic [CNT_W-1:0]    cnt;
    logic [`M_OP_BUS]    m_op_q;
    logic                start_pulse;
    logic                is_div_start;
    logic [CNT_W-1:0]    init_cnt;

    assign start_pulse  = i_start && !o_busy;
    assign is_div_start = i_m_op[2];          // M_DIV/M_DIVU/M_REM/M_REMU 高位为 1
    assign init_cnt     = is_div_start ? CNT_W'(DIV_LATENCY - 1)
                                       : CNT_W'(MUL_LATENCY - 1);

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            cnt    <= '0;
            o_busy <= 1'b0;
            o_done <= 1'b0;
            m_op_q <= '0;
        end else if (i_flush) begin
            cnt    <= '0;
            o_busy <= 1'b0;
            o_done <= 1'b0;
        end else if (start_pulse) begin
            cnt    <= init_cnt;
            o_busy <= 1'b1;
            o_done <= 1'b0;
            m_op_q <= i_m_op;
        end else if (o_busy) begin
            cnt <= cnt - 1'b1;
            if (cnt == CNT_W'(1)) begin
                o_busy <= 1'b0;
                o_done <= 1'b1;
            end
        end else begin
            o_done <= 1'b0;
        end
    end

    // ---- Multiply path ----
    logic [`DATA_BUS] mul_res;

    mul_pipe u_mul_pipe (
        .i_clk   (i_clk),
        .i_rst_n (i_rst_n),
        .i_start (start_pulse),
        .i_rs1   (i_rs1),
        .i_rs2   (i_rs2),
        .i_m_op  (i_m_op),
        .o_res   (mul_res)
    );

    // ---- Division path ----
    logic [`DATA_BUS] div_quot;
    logic [`DATA_BUS] div_rem;
    logic             div_done_unused;

    div_wrapper u_div_wrapper (
        .i_clk   (i_clk),
        .i_rst_n (i_rst_n),
        .i_start (start_pulse),
        .i_flush (i_flush),
        .i_m_op  (i_m_op),
        .i_rs1   (i_rs1),
        .i_rs2   (i_rs2),
        .o_quot  (div_quot),
        .o_rem   (div_rem),
        .o_done  (div_done_unused)
    );

    always_comb begin
        unique case (m_op_q)
            `M_MUL,
            `M_MULH,
            `M_MULHSU,
            `M_MULHU: o_res = mul_res;
            `M_DIV,
            `M_DIVU:  o_res = div_quot;
            `M_REM,
            `M_REMU:  o_res = div_rem;
            default:  o_res = '0;
        endcase
    end

endmodule
