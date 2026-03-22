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
`include "../../include/cpu_defines.sv"

module forward_unit (

    input  logic  [`RF_BUS]                 i_rs1_addr,
    input  logic  [`RF_BUS]                 i_rs2_addr,
    input  logic  [`RF_BUS]                 i_rd_addr_e_m,
    input  logic  [`RF_BUS]                 i_rd_addr_m_w,

    input  logic                            i_reg_write_e_m,
    input  logic                            i_reg_write_m_w,

    input  logic                            i_is_rs2_imm,
    input  logic  [3:0]                     i_inst_spec,



    output logic  [1:0]                     o_b1_sel,
    output logic  [1:0]                     o_b2_sel,
    output logic  [1:0]                     o_t1_sel,
    output logic  [1:0]                     o_a1_sel,
    output logic  [1:0]                     o_a2_sel
);

endmodule