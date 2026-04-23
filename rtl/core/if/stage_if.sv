//==============================================================================
// 模块: stage_if
// 功能概述：
//   取指（IF）级封装模块。内部通常例化 pc_reg 与 rom_instr（或后续替换为真实 I$/ICache IP）：
//   根据 i_pc_next 更新 PC，输出当前 PC 与对应 32 位指令。
// 接口/协作审查（供采纳）：
//   - i_pc_next 来源：复位初值、顺序 PC+4、分支纠正、BPU 预测目标等由顶层/hazard 汇总后接入。
//   - 若 ROM 按字寻址，顶层需统一 PC 与 rom 地址映射（对齐/右移），本模块保持“地址入、指令出”即可。
//==============================================================================
`include "cpu_defines.svh"

module stage_if(
    input  logic                    i_clk,
    input  logic                    i_rst_n,
    input  logic  [`PC_BUS]         i_pc_next,

    input  logic  [`INST_BUS]       i_irom_data, 
    

    output logic  [`INST_BUS]       o_instr,
    output logic  [`PC_BUS]         o_pc_cur
);

    pc_reg u_pc_reg (
        .i_clk     (i_clk),
        .i_rst_n   (i_rst_n),
        .i_pc_next (i_pc_next),
        .o_pc_cur  (o_pc_cur)
    );

    assign o_instr = i_irom_data;
endmodule