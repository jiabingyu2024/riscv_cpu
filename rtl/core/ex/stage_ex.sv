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
    input  logic                            i_clk,
    input  logic                            i_rst_n,
    input  logic                            i_flush,
    input  logic  [`DATA_BUS]               i_rs1_data,
    input  logic  [`DATA_BUS]               i_rs2_data,
    input  logic  [`DATA_BUS]               i_imm,
    input  logic  [`PC_BUS]                 i_pc,
    input  logic  [`DATA_BUS]               i_fwd_e_m,
    input  logic  [`DATA_BUS]               i_fwd_m_w,
    input  logic  [`DATA_BUS]               i_fwd_m_m,   //新增一个EX/MEM的前递数据输入

    input  logic  [`PC_BUS]                 i_pc_d_e,
    input  logic  [`PC_BUS]                 i_pc_target,
    input  logic  [`PC_BUS]                 i_pc_predict,

    input  logic  [1:0]                     i_rs1_fwd_sel,
    input  logic  [1:0]                     i_rs2_fwd_sel,
    input  logic  [`RF_BUS]                 i_rs1_addr,

    input  logic  [3:0]                     i_alu_ctrl,
    input  logic  [2:0]                     i_func3,

    input  logic                            i_is_branch,
    // input  logic                            i_is_jtype,
    // input  logic                            i_is_lui,
    input  logic                            i_is_rs2_imm,
    input  logic  [3:0]                     i_inst_spec,
    input  logic                            i_is_csr,
    input  logic  [2:0]                     i_csr_op,
    input  logic  [11:0]                    i_csr_addr,
    input  logic  [`DATA_BUS]               i_csr_rdata,
    input  logic  [`PC_BUS]                 i_csr_mtvec,
    input  logic  [`PC_BUS]                 i_csr_mepc,
    input  logic  [1:0]                     i_priv_mode,
    input  logic                            i_is_ecall,
    input  logic                            i_is_ebreak,
    input  logic                            i_is_mret,
    input  logic                            i_is_m_op,
    input  logic  [2:0]                     i_m_op,

    output logic  [`DATA_BUS]               o_alu_res,
    output logic  [`DATA_BUS]               o_a2_data,
    output logic                            o_ex_stall,
    output logic                            o_csr_write,
    output logic  [11:0]                    o_csr_addr,
    output logic  [`DATA_BUS]               o_csr_wdata,
    output logic                            o_csr_trap,
    output logic                            o_csr_mret,
    output logic  [`DATA_BUS]               o_csr_cause,
    output logic  [`PC_BUS]                 o_csr_epc,

    output logic                            o_update_taken,
    output logic                            o_update_en,
    output logic  [`PC_BUS]                 o_update_pc,
    output logic  [`PC_BUS]                 o_update_target,
    output logic                            o_error,
    output logic  [`PC_BUS]                 o_right_pc
    
);

    logic [`DATA_BUS] a1_data;
    logic [`DATA_BUS] a2_data;
    logic [`DATA_BUS] rs1_exec_data;
    logic [`DATA_BUS] rs2_exec_data;
    logic [`PC_BUS]   t1_data;
    logic [`DATA_BUS] alu_res_raw;
    logic [`DATA_BUS] m_res;
    logic [`DATA_BUS] m_result_q;
    logic [`DATA_BUS] csr_operand;
    logic [`DATA_BUS] csr_wdata;
    logic             csr_write_raw;
    logic             branch_error_raw;
    logic [`PC_BUS]   branch_right_pc_raw;
    logic             trap_redirect;
    logic             mret_redirect;

    typedef enum logic [2:0] {
        M_IDLE,
        M_MUL_WAIT,
        M_DIV_SEND,
        M_DIV_WAIT,
        M_DONE
    } m_state_e;

    localparam logic [5:0] MUL_WAIT_CYCLES = 6'd4;

    m_state_e             m_state_q;
    logic [5:0]           m_wait_cnt_q;
    logic [2:0]           m_op_q;
    logic [`DATA_BUS]     m_rs1_q;
    logic [`DATA_BUS]     m_rs2_q;
    logic                 m_div_by_zero_q;
    logic                 m_div_overflow_q;
    logic                 m_div_quot_neg_q;
    logic                 m_div_rem_neg_q;
    logic signed [32:0]   mul_a_ext;
    logic signed [32:0]   mul_b_ext;
    logic signed [65:0]   mul_product;
    logic [31:0]          div_abs_a;
    logic [31:0]          div_abs_b;
    logic                 div_is_signed;
    logic                 div_is_rem;
    logic                 div_by_zero;
    logic                 div_overflow;
    logic                 div_quot_neg;
    logic                 div_rem_neg;
    logic                 div_start;
    logic                 div_op_active;
    logic                 div_accept;
    logic                 div_dividend_ready;
    logic                 div_divisor_ready;
    logic                 div_dout_valid;
    logic [63:0]          div_dout_data;
    logic [31:0]          div_quot_raw;
    logic [31:0]          div_rem_raw;
    logic [31:0]          div_quot_fix;
    logic [31:0]          div_rem_fix;

    assign div_is_signed = (i_m_op == `M_OP_DIV) || (i_m_op == `M_OP_REM);
    assign div_is_rem    = (m_op_q == `M_OP_REM) || (m_op_q == `M_OP_REMU);
    assign div_by_zero   = (rs2_exec_data == 32'd0);
    assign div_overflow  = div_is_signed && (rs1_exec_data == 32'h8000_0000) && (rs2_exec_data == 32'hffff_ffff);
    assign div_quot_neg  = div_is_signed && (rs1_exec_data[31] ^ rs2_exec_data[31]);
    assign div_rem_neg   = div_is_signed && rs1_exec_data[31];
    assign div_abs_a     = (div_is_signed && rs1_exec_data[31]) ? (~rs1_exec_data + 32'd1) : rs1_exec_data;
    assign div_abs_b     = (div_is_signed && rs2_exec_data[31]) ? (~rs2_exec_data + 32'd1) : rs2_exec_data;
    assign div_op_active = i_is_m_op &&
                           ((i_m_op == `M_OP_DIV) || (i_m_op == `M_OP_DIVU) ||
                            (i_m_op == `M_OP_REM) || (i_m_op == `M_OP_REMU));
    assign div_start     = ((m_state_q == M_IDLE) && div_op_active) || (m_state_q == M_DIV_SEND);
    assign div_accept    = div_start && div_dividend_ready && div_divisor_ready;
    assign div_quot_raw  = div_dout_data[31:0];
    assign div_rem_raw   = div_dout_data[63:32];
    assign div_quot_fix  = m_div_quot_neg_q ? (~div_quot_raw + 32'd1) : div_quot_raw;
    assign div_rem_fix   = m_div_rem_neg_q ? (~div_rem_raw + 32'd1) : div_rem_raw;
    assign o_ex_stall    = (m_state_q == M_MUL_WAIT) || (m_state_q == M_DIV_SEND) ||
                           (m_state_q == M_DIV_WAIT) ||
                           ((m_state_q == M_IDLE) && i_is_m_op);

    always_comb begin
        unique case (i_rs1_fwd_sel)
            `FWD_E_M:  rs1_exec_data = i_fwd_e_m;
            `FWD_M_M:  rs1_exec_data = i_fwd_m_m;
            `FWD_M_W:  rs1_exec_data = i_fwd_m_w;
            default:   rs1_exec_data = i_rs1_data;
        endcase

        unique case (i_rs2_fwd_sel)
            `FWD_E_M:  rs2_exec_data = i_fwd_e_m;
            `FWD_M_M:  rs2_exec_data = i_fwd_m_m;
            `FWD_M_W:  rs2_exec_data = i_fwd_m_w;
            default:   rs2_exec_data = i_rs2_data;
        endcase

        t1_data = (i_inst_spec == `EX_JALR) ? rs1_exec_data : i_pc_d_e;
        a1_data = (i_inst_spec == `EX_AUIPC) ? i_pc : rs1_exec_data;
        a2_data = (i_is_rs2_imm || (i_inst_spec == `EX_AUIPC)) ? i_imm : rs2_exec_data;
    end

    alu u_alu (
        .i_alu1     (a1_data),
        .i_alu2     (a2_data),
        .i_alu_ctrl (i_alu_ctrl),
        .o_alu_res  (alu_res_raw)
    );

    MUL_0 u_mul_0 (
        .CLK (i_clk),
        .A   (mul_a_ext),
        .B   (mul_b_ext),
        .P   (mul_product)
    );

    DIV_0 u_div_0 (
        .aclk                   (i_clk),
        .s_axis_dividend_tvalid (div_start),
        .s_axis_dividend_tready (div_dividend_ready),
        .s_axis_dividend_tdata  (div_abs_a),
        .s_axis_divisor_tvalid  (div_start),
        .s_axis_divisor_tready  (div_divisor_ready),
        .s_axis_divisor_tdata   (div_by_zero ? 32'd1 : div_abs_b),
        .m_axis_dout_tvalid     (div_dout_valid),
        .m_axis_dout_tdata      (div_dout_data)
    );

    branch_cmp u_branch_cmp (
        .i_b1_data       (rs1_exec_data),
        .i_b2_data       (rs2_exec_data),
        .i_func3         (i_func3),
        .i_pc_d_e        (i_pc_d_e),
        .i_pc_target     (i_pc_target),
        .i_pc_predict    (i_pc_predict),
        .i_t1_data       (t1_data),
        .i_t2_data       (i_imm),
        .i_is_branch     (i_is_branch),
        .i_inst_spec     (i_inst_spec),
        .o_update_taken  (o_update_taken),
        .o_update_en     (o_update_en),
        .o_update_pc     (o_update_pc),
        .o_update_target (o_update_target),
        .o_error         (branch_error_raw),
        .o_right_pc      (branch_right_pc_raw)
    );

    always_comb begin
        mul_a_ext = {1'b0, rs1_exec_data};
        mul_b_ext = {1'b0, rs2_exec_data};
        if ((i_m_op == `M_OP_MULH) || (i_m_op == `M_OP_MULHSU)) begin
            mul_a_ext = {rs1_exec_data[31], rs1_exec_data};
        end
        if (i_m_op == `M_OP_MULH) begin
            mul_b_ext = {rs2_exec_data[31], rs2_exec_data};
        end
    end

    always_comb begin
        unique case (m_op_q)
            `M_OP_MUL:    m_res = mul_product[31:0];
            `M_OP_MULH,
            `M_OP_MULHSU,
            `M_OP_MULHU:  m_res = mul_product[63:32];
            `M_OP_DIV: begin
                if (m_div_by_zero_q) begin
                    m_res = 32'hffff_ffff;
                end else if (m_div_overflow_q) begin
                    m_res = 32'h8000_0000;
                end else begin
                    m_res = div_quot_fix;
                end
            end
            `M_OP_DIVU:   m_res = m_div_by_zero_q ? 32'hffff_ffff : div_quot_raw;
            `M_OP_REM: begin
                if (m_div_by_zero_q) begin
                    m_res = m_rs1_q;
                end else if (m_div_overflow_q) begin
                    m_res = 32'd0;
                end else begin
                    m_res = div_rem_fix;
                end
            end
            `M_OP_REMU:   m_res = m_div_by_zero_q ? m_rs1_q : div_rem_raw;
            default:      m_res = m_result_q;
        endcase
    end

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            m_state_q        <= M_IDLE;
            m_wait_cnt_q     <= '0;
            m_op_q           <= `M_OP_NONE;
            m_rs1_q          <= '0;
            m_rs2_q          <= '0;
            m_result_q       <= '0;
            m_div_by_zero_q  <= 1'b0;
            m_div_overflow_q <= 1'b0;
            m_div_quot_neg_q <= 1'b0;
            m_div_rem_neg_q  <= 1'b0;
        end else if (i_flush) begin
            m_state_q        <= M_IDLE;
            m_wait_cnt_q     <= '0;
            m_op_q           <= `M_OP_NONE;
            m_rs1_q          <= '0;
            m_rs2_q          <= '0;
            m_result_q       <= '0;
            m_div_by_zero_q  <= 1'b0;
            m_div_overflow_q <= 1'b0;
            m_div_quot_neg_q <= 1'b0;
            m_div_rem_neg_q  <= 1'b0;
        end else begin
            unique case (m_state_q)
                M_IDLE: begin
                    if (i_is_m_op) begin
                        m_op_q           <= i_m_op;
                        m_rs1_q          <= rs1_exec_data;
                        m_rs2_q          <= rs2_exec_data;
                        m_div_by_zero_q  <= div_by_zero;
                        m_div_overflow_q <= div_overflow;
                        m_div_quot_neg_q <= div_quot_neg;
                        m_div_rem_neg_q  <= div_rem_neg;
                        if ((i_m_op == `M_OP_MUL) || (i_m_op == `M_OP_MULH) ||
                            (i_m_op == `M_OP_MULHSU) || (i_m_op == `M_OP_MULHU)) begin
                            m_wait_cnt_q <= MUL_WAIT_CYCLES - 6'd1;
                            m_state_q    <= M_MUL_WAIT;
                        end else begin
                            m_wait_cnt_q <= '0;
                            m_state_q    <= div_accept ? M_DIV_WAIT : M_DIV_SEND;
                        end
                    end
                end

                M_DIV_SEND: begin
                    if (div_accept) begin
                        m_state_q <= M_DIV_WAIT;
                    end
                end

                M_MUL_WAIT: begin
                    if (m_wait_cnt_q == 6'd0) begin
                        m_result_q <= m_res;
                        m_state_q  <= M_DONE;
                    end else begin
                        m_wait_cnt_q <= m_wait_cnt_q - 6'd1;
                    end
                end

                M_DIV_WAIT: begin
                    if (div_dout_valid) begin
                        m_result_q <= m_res;
                        m_state_q  <= M_DONE;
                    end
                end

                M_DONE: begin
                    m_state_q <= M_IDLE;
                end

                default: begin
                    m_state_q <= M_IDLE;
                end
            endcase
        end
    end

    always_comb begin
        csr_operand = i_csr_op[2] ? {27'b0, i_rs1_addr} : rs1_exec_data;
        unique case (i_csr_op)
            `CSR_OP_RW,
            `CSR_OP_RWI: csr_wdata = csr_operand;
            `CSR_OP_RS,
            `CSR_OP_RSI: csr_wdata = i_csr_rdata | csr_operand;
            `CSR_OP_RC,
            `CSR_OP_RCI: csr_wdata = i_csr_rdata & ~csr_operand;
            default:     csr_wdata = i_csr_rdata;
        endcase

        csr_write_raw = i_is_csr &&
                        ((i_csr_op == `CSR_OP_RW) || (i_csr_op == `CSR_OP_RWI) ||
                         (csr_operand != 32'd0));
        trap_redirect = i_is_ecall || i_is_ebreak;
        mret_redirect = i_is_mret;

        o_csr_write = csr_write_raw;
        o_csr_addr  = i_csr_addr;
        o_csr_wdata = csr_wdata;
        o_csr_trap  = trap_redirect;
        o_csr_mret  = mret_redirect;
        o_csr_cause = i_is_ebreak ? 32'd3 : ((i_priv_mode == `PRIV_M) ? 32'd11 : 32'd8);
        o_csr_epc   = i_pc_d_e;
    end

    always_comb begin
        o_a2_data = rs2_exec_data;

        unique case (i_inst_spec)
            `EX_LUI:   o_alu_res = i_imm;
            `EX_JAL,
            `EX_JALR:  o_alu_res = i_pc + 32'd4;
            default: begin
                if (i_is_csr) begin
                    o_alu_res = i_csr_rdata;
                end else if (i_is_m_op) begin
                    o_alu_res = m_result_q;
                end else begin
                    o_alu_res = alu_res_raw;
                end
            end
        endcase

        o_error    = branch_error_raw || trap_redirect || mret_redirect;
        o_right_pc = trap_redirect ? {i_csr_mtvec[31:2], 2'b00} :
                     (mret_redirect ? i_csr_mepc : branch_right_pc_raw);
    end
endmodule
