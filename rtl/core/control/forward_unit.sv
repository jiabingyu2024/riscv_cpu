//==============================================================================
// 模块: forward_unit
// 功能概述：
//   旁路（前递）控制。比较 ID/EX 级 rs1/rs2 与 EX/M、M/W 级目的寄存器及写使能，产生 b1/b2/t1/a1/a2
//   选择信号（见 `B1_*`、`A2_*` 等宏），供 EX 级 MUX 选用寄存器堆、旁路或 PC/立即数。
// 接口/协作审查（供采纳）：
//   - i_is_rs2_imm：部分指令第二操作数为 imm 而非 rs2，前递应对 rs2 无关时置为不关心或固定选 imm。
//   - load-use 通常不能仅从 M 级前递到 EX 使用 load 数据，需 hazard 停顿；forward 与 hazard 分工需一致。
//   - i_rd_addr_e_m / i_rd_addr_m_w 命名表示来自 E/M 与 M/W 流水级的 rd（与 regfile 写地址同源）。
//==============================================================================
`include "cpu_defines.svh"

module forward_unit (

    input  logic  [`RF_BUS]                 i_rs1_addr,
    input  logic  [`RF_BUS]                 i_rs2_addr,
    input  logic  [`RF_BUS]                 i_rd_addr_e_m,
    input  logic  [`RF_BUS]                 i_rd_addr_m_w,

    input  logic                            i_reg_write_e_m,
    input  logic                            i_reg_write_m_w,

    input  logic                            i_is_rs2_imm,
    input  logic  [3:0]                     i_inst_spec,



    output logic  [2:0]                     o_b1_sel,
    output logic  [2:0]                     o_b2_sel,
    output logic  [2:0]                     o_t1_sel,
    output logic  [2:0]                     o_a1_sel,
    output logic  [2:0]                     o_a2_sel
);

    logic hit_rs1_e_m;
    logic hit_rs1_m_w;
    logic hit_rs2_e_m;
    logic hit_rs2_m_w;

    assign hit_rs1_e_m = i_reg_write_e_m && (i_rd_addr_e_m != '0) && (i_rd_addr_e_m == i_rs1_addr);
    assign hit_rs1_m_w = i_reg_write_m_w && (i_rd_addr_m_w != '0) && (i_rd_addr_m_w == i_rs1_addr);
    assign hit_rs2_e_m = i_reg_write_e_m && (i_rd_addr_e_m != '0) && (i_rd_addr_e_m == i_rs2_addr);
    assign hit_rs2_m_w = i_reg_write_m_w && (i_rd_addr_m_w != '0) && (i_rd_addr_m_w == i_rs2_addr);

    always_comb begin
        o_b1_sel = `B1_RS1;
        o_b2_sel = `B2_RS2;
        o_t1_sel = `T1_PC;
        o_a1_sel = `A1_RS1;
        o_a2_sel = i_is_rs2_imm ? `A2_imm : `A2_RS2;

        if (hit_rs1_e_m) begin
            o_b1_sel = `B1_E_M;
            o_a1_sel = `A1_E_M;
        end else if (hit_rs1_m_w) begin
            o_b1_sel = `B1_M_W;
            o_a1_sel = `A1_M_W;
        end

        if (hit_rs2_e_m) begin
            o_b2_sel = `B2_E_M;
            if (!i_is_rs2_imm) begin
                o_a2_sel = `A2_E_M;
            end
        end else if (hit_rs2_m_w) begin
            o_b2_sel = `B2_M_W;
            if (!i_is_rs2_imm) begin
                o_a2_sel = `A2_M_W;
            end
        end

        unique case (i_inst_spec)
            `EX_AUIPC: begin
                o_t1_sel = `T1_PC;
                o_a1_sel = `A1_PC;
                o_a2_sel = `A2_imm;
            end
            `EX_JAL: begin
                o_t1_sel = `T1_PC;
                o_a1_sel = `A1_PC;
                o_a2_sel = `A2_imm;
            end
            `EX_JALR: begin
                o_a2_sel = `A2_imm;
                if (hit_rs1_e_m) begin
                    o_t1_sel = `T1_E_M;
                    o_a1_sel = `A1_E_M;
                end else if (hit_rs1_m_w) begin
                    o_t1_sel = `T1_M_W;
                    o_a1_sel = `A1_M_W;
                end else begin
                    o_t1_sel = `T1_RS1;
                    o_a1_sel = `A1_RS1;
                end
            end
            default: begin
            end
        endcase
    end
endmodule
