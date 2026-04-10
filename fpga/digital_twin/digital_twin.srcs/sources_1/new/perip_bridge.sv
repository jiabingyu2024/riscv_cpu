`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/04/22 10:25:24
// Design Name: 
// Module Name: perip_bridge
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

module perip_bridge(
    input  logic         clk				,
    input  logic         cnt_clk			,
    input  logic         rst                ,

    input  logic [31:0]  perip_addr			,
    input  logic [31:0]  perip_wdata		,
    input  logic         perip_wen			,
	input  logic [1:0]	 perip_mask			,
    output logic [31:0]  perip_rdata		,

    input  logic [63:0]  virtual_sw_input	,
    input  logic [7:0]   virtual_key_input	,	

	output logic [39:0]  virtual_seg_output	,
    output logic [31:0]  virtual_led_output
);
    localparam DRAM_ADDR_START = 32'h8010_0000;
    localparam DRAM_ADDR_END   = 32'h8013_FFFF;
    localparam SW0_ADDR  = 32'h8020_0000;  // sw[31:0]
    localparam SW1_ADDR  = 32'h8020_0004;  // sw[63:32]
    localparam KEY_ADDR  = 32'h8020_0010;  // key[7:0]
    localparam SEG_ADDR  = 32'h8020_0020;  // seg
    localparam LED_ADDR  = 32'h8020_0040;  // led[31:0]
    localparam CNT_ADDR  = 32'h8020_0050;  // counter

    logic [31:0] LED;
    logic [31:0] seg_wdata, cnt_rdata, mmio_rdata, dram_rdata;
    logic [39:0] seg_output;

    // 因为 perip_addr 已经被核前置到了 EX 阶段（从而满足 BRAM 的地址时序）
    // 而组合逻辑的外设（如 SW/KEY/SEG的回读）需要在下一拍 MEM 阶段出数据
    // 所以需要把地址打一拍留存到 MEM 阶段使用
    logic [31:0] mem_addr;
    always_ff @(posedge clk) begin
        mem_addr <= perip_addr;
    end

    // we don't care perip_mask in LED, SEG, SW & KEY, only care in DRAM
    // write process (Write is combinationally sampled at Edge M, effectively writing in MEM stage)
    always_ff @(posedge clk) begin
        if (perip_wen) begin
            case (perip_addr)
                LED_ADDR:   LED <= perip_wdata;
                SEG_ADDR:   seg_wdata <= perip_wdata;
            endcase
        end
    end

    // read process: in one cycle
    // Note: mem_addr must be used since we are in the MEM cycle!
    always_comb begin
        // 这里可以直接根据地址判断
        case (mem_addr)
            SW0_ADDR:  mmio_rdata = virtual_sw_input[31:0];
            SW1_ADDR:  mmio_rdata = virtual_sw_input[63:32];
            KEY_ADDR:  mmio_rdata = {24'd0, virtual_key_input};
            SEG_ADDR:  mmio_rdata = seg_wdata;
            default:   mmio_rdata = 32'hDEAD_BEEF;
        endcase
    end

    // seg driver
    display_seg seg_driver (
        .clk    (clk),
        .rst    (rst),
        .s      (seg_wdata),
        .seg1   (seg_output[6:0]),
        .seg2   (seg_output[16:10]),
        .seg3   (seg_output[26:20]),
        .seg4   (seg_output[36:30]),
        .ans    ({seg_output[39:38], seg_output[29:28], seg_output[19:18], seg_output[9:8]})
    ); 
   
    assign seg_output[7]  = 0;
    assign seg_output[17] = 0;
    assign seg_output[27] = 0;
    assign seg_output[37] = 0;
    

    // dram rw
    dram_driver dram_driver_inst (
        .clk				(clk),
        .perip_addr			(perip_addr[17:0]),
        .perip_wdata		(perip_wdata),
        .perip_mask			(perip_mask),
        .dram_wen 			(perip_wen & (perip_addr >= DRAM_ADDR_START && perip_addr < DRAM_ADDR_END)),
        .perip_rdata		(dram_rdata)
    );

    // counter rw
    counter counter_inst (
        .clk				(cnt_clk),
        .rst                (rst),
        .perip_wdata		(perip_wdata),
        .cnt_wen 			(perip_wen & (perip_addr == CNT_ADDR)),
        .perip_rdata		(cnt_rdata)
    );

    assign perip_rdata = {32{mem_addr == SW0_ADDR}} & mmio_rdata |
                        {32{mem_addr == SW1_ADDR}} & mmio_rdata |
                        {32{mem_addr == KEY_ADDR}} & mmio_rdata |
                        {32{mem_addr == SEG_ADDR}} & mmio_rdata |
                        {32{mem_addr >= DRAM_ADDR_START && mem_addr < DRAM_ADDR_END}} & dram_rdata |
                        {32{mem_addr == CNT_ADDR}} & cnt_rdata;
    
    assign virtual_led_output = LED;
    assign virtual_seg_output = seg_output;

endmodule
