//==============================================================================
// 模块: div_srt_r4
// 功能概述：
//   固定 17 拍延迟的 32-bit 除法器，cycle-true 等价于 RV32M 规范的 DIV/REM
//   行为（含除零、INT_MIN÷-1 溢出特判）。每个迭代拍组合执行 2 次非恢复式
//   radix-2 sub-iteration（两级 33-bit 减法器串接），等效 radix-4 吞吐；共
//   16 个迭代拍 × 2 = 32 个 sub-iter，覆盖 32 bit 商。
//   时序约定与 m_unit 倒计时一致：i_start 在 T0 拉单拍，o_done 在 T17 拉单拍。
//     T0       ：组合预处理（abs / 符号 / 特判），FF 锁存初值 cnt=15、busy=1
//     T1..T15  ：每拍 1 次 dual sub-iter，cnt 递减；共 15 个 dual-iter
//     T16      ：第 16 个 dual-iter 与输出寄存同拍完成（使用组合的 R_nxt/Q_nxt
//                做符号修正/特判旁路，注册到 o_quot/o_rem，o_done<=1）
//     T17      ：o_done / o_quot / o_rem 对外可见
//   仿真和综合走同一份 RTL，cycle 严格相等，便于乱序后端做精确 wakeup。
// 接口/协作审查（供采纳）：
//   - i_signed 由上层 (div_wrapper) 按 i_m_op 译出：DIV/REM=1，DIVU/REMU=0。
//   - i_flush 在 inflight 中拉高将立即清空 busy_int 与 cnt_int，丢弃当前操作，
//     不会产生 o_done 脉冲。与 m_unit 的 i_flush 同源（来自 stage_ex 误测/异常）。
//   - 关键路径：每拍两级 33-bit 减法器 + 选择 mux，5ns/200MHz 余量充足；若上板
//     timing 紧，可将 dual-iter 拆为 single-iter（变 33 拍）或在两 sub-iter 之间
//     插一级 FF（变 33 拍）。
//==============================================================================
`include "cpu_defines.svh"

module div_srt_r4 (
    input  logic                    i_clk,
    input  logic                    i_rst_n,
    input  logic                    i_start,
    input  logic                    i_flush,
    input  logic                    i_signed,
    input  logic  [`DATA_BUS]       i_rs1,    // dividend
    input  logic  [`DATA_BUS]       i_rs2,    // divisor

    output logic  [`DATA_BUS]       o_quot,
    output logic  [`DATA_BUS]       o_rem,
    output logic                    o_done
);

// Radix-4 SRT

    logic        sign_a, sign_b;
    logic [31:0] abs_a,  abs_b;
    logic        is_div_zero;
    logic        is_signed_overflow;
    logic        sign_q_pre, sign_r_pre;

    assign sign_a = i_signed && i_rs1[31];
    assign sign_b = i_signed && i_rs2[31];
    assign abs_a  = sign_a ? (~i_rs1 + 32'd1) : i_rs1;
    assign abs_b  = sign_b ? (~i_rs2 + 32'd1) : i_rs2;

    assign is_div_zero        = (i_rs2 == 32'd0);
    assign is_signed_overflow = i_signed
                              && (i_rs1 == 32'h8000_0000)
                              && (i_rs2 == 32'hFFFF_FFFF);

    assign sign_q_pre = sign_a ^ sign_b;
    assign sign_r_pre = sign_a;

    logic              busy_int;
    logic [4:0]        cnt_int;          // 15..0
    logic [32:0]       R_q;              
    logic [31:0]       Q_q;              
    logic [31:0]       B_q;              // |divisor|
    logic              sign_q_q;
    logic              sign_r_q;
    logic              spec_dz_q;
    logic              spec_ov_q;
    logic [31:0]       a_q;              // |dividend|

    //   if ((R<<1 | Q[31]) >= B): R = (R<<1 | Q[31]) - B; q_bit = 1
    //   else                    : R = (R<<1 | Q[31]);     q_bit = 0
    //   Q = (Q<<1) | q_bit
    function automatic void sub_iter (
        input  logic [32:0] R_in,
        input  logic [31:0] Q_in,
        input  logic [31:0] B,
        output logic [32:0] R_out,
        output logic [31:0] Q_out
    );
        logic [32:0] R_shift;
        logic [33:0] R_sub;    
        logic        q_bit;
        R_shift = {R_in[31:0], Q_in[31]};
        R_sub   = {1'b0, R_shift} - {2'b0, B};
        q_bit   = ~R_sub[33];  
        R_out   = q_bit ? R_sub[32:0] : R_shift;
        Q_out   = {Q_in[30:0], q_bit};
    endfunction

    logic [32:0] R_mid,  R_nxt;
    logic [31:0] Q_mid,  Q_nxt;

    always_comb begin
        sub_iter(R_q,   Q_q,   B_q, R_mid, Q_mid);
        sub_iter(R_mid, Q_mid, B_q, R_nxt, Q_nxt);
    end

    logic [31:0] quot_abs, rem_abs;
    logic [31:0] quot_fix, rem_fix;
    logic [31:0] quot_final, rem_final;

    assign quot_abs = Q_nxt;
    assign rem_abs  = R_nxt[31:0];
    assign quot_fix = sign_q_q ? (~quot_abs + 32'd1) : quot_abs;
    assign rem_fix  = sign_r_q ? (~rem_abs  + 32'd1) : rem_abs;

    always_comb begin
        if (spec_dz_q) begin
            quot_final = 32'hFFFF_FFFF;
            rem_final  = sign_r_q ? (~a_q + 32'd1) : a_q;
        end else if (spec_ov_q) begin
            quot_final = 32'h8000_0000;
            rem_final  = 32'h0000_0000;
        end else begin
            quot_final = quot_fix;
            rem_final  = rem_fix;
        end
    end

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            busy_int  <= 1'b0;
            cnt_int   <= 5'd0;
            R_q       <= 33'd0;
            Q_q       <= 32'd0;
            B_q       <= 32'd0;
            sign_q_q  <= 1'b0;
            sign_r_q  <= 1'b0;
            spec_dz_q <= 1'b0;
            spec_ov_q <= 1'b0;
            a_q       <= 32'd0;
            o_quot    <= 32'd0;
            o_rem     <= 32'd0;
            o_done    <= 1'b0;
        end else if (i_flush) begin
            busy_int <= 1'b0;
            cnt_int  <= 5'd0;
            o_done   <= 1'b0;
        end else if (i_start && !busy_int) begin
            busy_int  <= 1'b1;
            cnt_int   <= 5'd15;
            R_q       <= 33'd0;
            Q_q       <= abs_a;
            B_q       <= abs_b;
            sign_q_q  <= sign_q_pre;
            sign_r_q  <= sign_r_pre;
            spec_dz_q <= is_div_zero;
            spec_ov_q <= is_signed_overflow;
            a_q       <= abs_a;
            o_done    <= 1'b0;
        end else if (busy_int) begin
            if (cnt_int != 5'd0) begin
                R_q     <= R_nxt;
                Q_q     <= Q_nxt;
                cnt_int <= cnt_int - 5'd1;
                o_done  <= 1'b0;
            end else begin
                o_quot   <= quot_final;
                o_rem    <= rem_final;
                busy_int <= 1'b0;
                o_done   <= 1'b1;
            end
        end else begin
            o_done <= 1'b0;
        end
    end

endmodule
