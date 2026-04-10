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
	input  logic [1:0]	 perip_mask			,
    input  logic         dram_wen           ,
    output logic [31:0]  perip_rdata		
);
    logic [15:0] dram_addr;
    logic [ 1:0] offset;
    logic [31:0] dram_data, dram_rdata_raw;
    logic [ 3:0] dram_wea;

    assign dram_addr = perip_addr[17:2];
    assign offset = perip_addr[1:0];
    
    // DRAM BRAM 输出直接接回 CPU 内部做字对齐和符号扩展
    assign perip_rdata = dram_rdata_raw;

    // 修改 BRAM 例化，适配 Block Memory Generator 和 Byte Write Enable (BWE)
    DRAM Mem_DRAM (
        .clka       (clk),
        .ena        (1'b1),
        .wea        (dram_wea),
        .addra      (dram_addr),
        .dina       (dram_data),
        .douta      (dram_rdata_raw)
    );

    // 修改写使能，利用 BRAM 的字节写使能 (BWE) 进行修改，不再读后修改
    always_comb begin
        if (dram_wen) begin
            case (perip_mask)
                2'b00: // sb
                    case (offset)
                        2'b00:  dram_wea = 4'b0001;
                        2'b01:  dram_wea = 4'b0010;
                        2'b10:  dram_wea = 4'b0100;
                        2'b11:  dram_wea = 4'b1000;
                        default: dram_wea = 4'b0000;
                    endcase
                2'b01: // sh
                    case (offset[1])
                        1'b0:  dram_wea = 4'b0011;
                        1'b1:  dram_wea = 4'b1100;
                    endcase
                2'b10: // sw
                    dram_wea = 4'b1111;
                default: dram_wea = 4'b0000;
            endcase
        end else begin
            dram_wea = 4'b0000;
        end
    end

    // 修改写入数据对齐
    always_comb begin
        case (perip_mask)
            2'b10: dram_data = perip_wdata;                 // sw
            2'b01: dram_data = {perip_wdata[15:0], perip_wdata[15:0]};  // sh: 铺满半字
            2'b00: dram_data = {perip_wdata[7:0], perip_wdata[7:0], perip_wdata[7:0], perip_wdata[7:0]};  // sb: 铺满字节
            default: dram_data = perip_wdata;
        endcase
    end
endmodule
