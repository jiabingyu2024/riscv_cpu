`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/22/2025 11:42:01 AM
// Design Name: 
// Module Name: dram_driver
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module dram_driver(
    input  logic         clk				,

    input  logic [17:0]  perip_addr			,
    input  logic [31:0]  perip_wdata		,
	input  logic [3:0]	 perip_mask			,
    input  logic         dram_wen           ,
    output logic [31:0]  perip_rdata		
);
    logic [31:0] dram_rdata;

    assign perip_rdata = dram_rdata;

    DRAM Mem_DRAM (
        .clk        (clk),
        .a          (perip_addr),
        .spo        (dram_rdata),
        .we         (dram_wen),
        .mask       (perip_mask),
        .d          (perip_wdata)
    );
endmodule
