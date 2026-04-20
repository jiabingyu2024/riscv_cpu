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
    logic [15:0] dram_addr;
    logic [31:0] dram_wdata;
    logic [31:0] dram_rdata;
    logic [3:0]  dram_wea;
    logic [1:0]  offset, offset_q;
    logic [3:0]  mask_q;

    assign dram_addr = perip_addr[17:2];
    assign offset = perip_addr[1:0];

    always_comb begin
        dram_wea = 4'b0000;
        dram_wdata = 32'b0;

        if (dram_wen) begin
            unique case (perip_mask)
                4'b0001: begin
                    dram_wea = 4'b0001 << offset;
                    unique case (offset)
                        2'b00: dram_wdata = {24'b0, perip_wdata[7:0]};
                        2'b01: dram_wdata = {16'b0, perip_wdata[7:0], 8'b0};
                        2'b10: dram_wdata = {8'b0, perip_wdata[7:0], 16'b0};
                        2'b11: dram_wdata = {perip_wdata[7:0], 24'b0};
                    endcase
                end
                4'b0011: begin
                    dram_wea = offset[1] ? 4'b1100 : 4'b0011;
                    dram_wdata = offset[1] ? {perip_wdata[15:0], 16'b0} : {16'b0, perip_wdata[15:0]};
                end
                4'b1111: begin
                    dram_wea = 4'b1111;
                    dram_wdata = perip_wdata;
                end
                default: begin
                    dram_wea = 4'b0000;
                    dram_wdata = 32'b0;
                end
            endcase
        end
    end

    always_ff @(posedge clk) begin
        offset_q <= offset;
        mask_q <= perip_mask;
    end

    always_comb begin
        perip_rdata = 32'b0;

        unique case (mask_q)
            4'b0001: begin
                unique case (offset_q)
                    2'b00: perip_rdata = {24'b0, dram_rdata[7:0]};
                    2'b01: perip_rdata = {24'b0, dram_rdata[15:8]};
                    2'b10: perip_rdata = {24'b0, dram_rdata[23:16]};
                    2'b11: perip_rdata = {24'b0, dram_rdata[31:24]};
                endcase
            end
            4'b0011: perip_rdata = offset_q[1] ? {16'b0, dram_rdata[31:16]} : {16'b0, dram_rdata[15:0]};
            4'b1111: perip_rdata = dram_rdata;
            default: perip_rdata = 32'b0;
        endcase
    end

    DRAM_0 Mem_DRAM (
        .addra      (dram_addr),
        .clka       (clk),
        .dina       (dram_wdata),
        .ena        (1'b1),
        .wea        (dram_wea),
        .douta      (dram_rdata)
    );
endmodule
