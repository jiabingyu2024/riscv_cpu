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
    input logic              i_valid,
    
    input logic [`PC_BUS]    i_pc,
    input logic [`PC_BUS]    i_pc_predict,
    input logic [`INST_BUS]  i_inst,


    output logic [`PC_BUS]   o_pc,
    output logic [`INST_BUS] o_inst,
    output logic [`PC_BUS]   o_pc_predict,
    output logic             o_valid          // flush  0 else 1
);

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_pc         <= '0;
            o_inst       <= '0;
            o_pc_predict <= '0;
            o_valid      <= 1'b0;
        end else begin
            o_pc         <= i_stall ? o_pc         : i_pc;
            o_inst       <= i_stall ? o_inst       : i_inst;
            o_pc_predict <= i_stall ? o_pc_predict : i_pc_predict;
            o_valid      <= i_flush ? 1'b0 : (i_stall ? o_valid : i_valid);
        end
    end

endmodule 
