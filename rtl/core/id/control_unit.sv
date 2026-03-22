//==============================================================================
// 模块: control_unit
// 功能概述：
//   纯组合（或带小寄存器，视实现而定）控制译码单元。输入 32 位指令字，输出访存/写回/ALU 类型、
//   是否用立即数作 ALU 第二操作数、分支标志、func3、alu_ctrl、inst_spec 等，不含寄存器堆读写。
// 接口/协作审查（供采纳）：
//   - 与 stage_id 中控制信号应对齐；注释掉的 o_alu1_src/o_alu2_src 若后续启用，需同步流水线寄存器位宽。
//   - o_inst_spec 为 4 位自定义编码，建议文档化与 RISC-V opcode/funct 的对应关系，便于 EX/前递/分支共用。
//==============================================================================
`include "../../include/cpu_defines.sv"

module control_unit(
    input  logic  [`INST_BUS]               i_instr,

    output logic                            o_mem_read,
    output logic                            o_mem_write,
    output logic                            o_reg_write,
    output logic                            o_wb_src,
    // output logic                            o_alu1_src,
    // output logic                            o_alu2_src,
    output logic                            o_is_rs2_imm,
    output logic  [3:0]                     o_inst_spec,

    output logic  [3:0]                     o_alu_ctrl,
    output logic  [2:0]                     o_func3,

    output logic                            o_is_branch
    // output logic                            o_is_jtype,
    // output logic                            o_is_lui,
    
);

endmodule
