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

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            o_pc         <= '0;
            o_inst       <= '0;
            o_pc_predict <= '0;
            o_valid      <= 1'b0;
        end else if (i_flush) begin
            o_pc         <= '0;
            o_inst       <= '0;
            o_pc_predict <= '0;
            o_valid      <= 1'b0;
        end else if (!i_stall) begin
            o_pc         <= i_pc;
            o_inst       <= i_inst;
            o_pc_predict <= i_pc_predict;
            o_valid      <= 1'b1;
        end
        else begin
            o_pc         <= o_pc;
            o_inst       <= o_inst;
            o_pc_predict <= o_pc_predict;
            o_valid      <= 1'b1;
        end
    end

endmodule 
