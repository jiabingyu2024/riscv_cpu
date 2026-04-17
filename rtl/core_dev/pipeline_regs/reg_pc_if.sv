//==============================================================================
// 模块: reg_pc_if
// 功能概述：
//==============================================================================
`include "cpu_defines.svh"

module reg_pc_if(
    input logic              i_clk,
    input logic              i_rst_n,
    input logic              i_flush,
    input logic              i_stall,
    
    input logic [`PC_BUS]    i_pc,
    input logic [`PC_BUS]    i_pc_predict,
    input logic [`INST_BUS]  i_inst,


    output logic [`PC_BUS]   o_pc,
    output logic [`INST_BUS] o_inst,
    output logic [`PC_BUS]   o_pc_predict,
    output logic             o_valid          // flush  0 else 1
);


endmodule 
