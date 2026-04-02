`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/16/2025 06:21:13 PM
// Design Name: 
// Module Name: student_top
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
`include "include/cpu_defines.sv"

module student_top#(
    parameter                           P_SW_CNT            = 64,
    parameter                           P_LED_CNT           = 32,
    parameter                           P_SEG_CNT           = 40,
    parameter                           P_KEY_CNT           = 8
) (
    input                                       w_clk_50Mhz   ,
    input                                       w_clk_rst     ,
    input  [P_KEY_CNT - 1:0]                    virtual_key   ,
    input  [P_SW_CNT  - 1:0]                    virtual_sw    ,

    output [P_LED_CNT - 1:0]                    virtual_led   ,
    output [P_SEG_CNT - 1:0]                    virtual_seg   
);
     // You can revise the design below to finish your design. Let's go.
    // assign virtual_led = virtual_sw[31:0];
    // assign virtual_seg = {virtual_key, virtual_sw[63:32]};

    // If you want to know more about the function of the virtual_seg driver
    // please read Appendix 4: https://jyq2umyqyt.feishu.cn/docx/Fdkod8H4folLbexKQSCcwXbMnKc
    logic clk;
    logic rst_n;
    assign clk = w_clk_50Mhz;
    assign rst_n = ~w_clk_rst;
    
    logic  [`DATA_BUS]      irom_data;
    logic  [`PC_BUS]        irom_addr;
    logic  [`DATA_BUS]      core_dram_rdata;
    logic                   core_dram_wen;
    logic  [`RAM_ADDR_BUS]  core_dram_addr;
    logic  [`DATA_BUS]      core_dram_wdata;
    logic  [1:0]            core_dram_mask;

    // 1. 定义地址分配范围信号
    logic is_dram_addr;
    logic is_io_addr;
    assign is_dram_addr = (core_dram_addr >= 32'h8010_0000 && core_dram_addr <= 32'h8013_FFFF);
    assign is_io_addr   = (core_dram_addr >= 32'h8020_0000 && core_dram_addr <= 32'h8020_00FF);

    logic [`DATA_BUS] dram_rdata_real;

    // =========================================================
    // IROM 与 DRAM 的例化
    // =========================================================
    
    // IROM: 16KB (0x8000_0000 ~ 0x8000_3FFF)
    // 根据手册：IROM 是 Distributed RAM，当前周期出数据 (异步读)
    // 提示: 在 Vivado 中拉取 IP -> Distributed Memory Generator
    // 命名为 irom_ip, Memory Type 选 ROM, Width=32, Depth=4096 (16KB)
    //
    irom_ip u_irom (
        .a   (irom_addr[13:2]),  // 截取字地址
        .spo (irom_data)
    );
    
    // DRAM: 256KB (0x8010_0000 ~ 0x8013_FFFF)
    // 根据手册：它和外设一样归类为 perip，读当周期给出(异步读)，写在下一周期
    // 这说明 DRAM 必须也是 Distributed RAM (或者你自己用寄存器阵列实现，但用IP更好)
    // 提示: 拉取 IP -> Distributed Memory Generator
    // 命名为 dram_ip, Memory Type 选 Single Port RAM, Width=32, Depth=65536 (256KB)
    // 分布式 RAM 不支持自带 Byte Write 掩码，因此需要手工处理字节/半字写入：
    // 我们用 4 个 8-bit 的 Distributed RAM 来拼成一个 32-bit 的 DRAM 以支持 byte 写：
    // 注意：这里的深度是 65536, 所以地址截取应该是 [15:0] 作为词地址 (即原始字节地址的 [17:2])
    //
    
    // CPU 的 core_dram_addr 因为宏定义只暴露了 14 位，所以先将其填充或对齐。
    wire [15:0] dram_word_addr = {2'b0, core_dram_addr[13:0]}; // 取决于你的CPU地址是字还是字节。假设是字地址，补0
    
    dram_ip_8bit u_dram_b0 ( .a(dram_word_addr), .d(core_dram_wdata[7:0]),   .clk(clk), .we(core_dram_wen & is_dram_addr & core_dram_mask[0]), .spo(dram_rdata_real[7:0]) );
    dram_ip_8bit u_dram_b1 ( .a(dram_word_addr), .d(core_dram_wdata[15:8]),  .clk(clk), .we(core_dram_wen & is_dram_addr & core_dram_mask[1]), .spo(dram_rdata_real[15:8]) );
    dram_ip_8bit u_dram_b2 ( .a(dram_word_addr), .d(core_dram_wdata[23:16]), .clk(clk), .we(core_dram_wen & is_dram_addr & core_dram_mask[2]), .spo(dram_rdata_real[23:16]) );
    dram_ip_8bit u_dram_b3 ( .a(dram_word_addr), .d(core_dram_wdata[31:24]), .clk(clk), .we(core_dram_wen & is_dram_addr & core_dram_mask[3]), .spo(dram_rdata_real[31:24]) );

    // =========================================================
    // 外设 (MMIO) 寄存器组与读写逻辑
    // =========================================================
    logic [31:0] led_reg;
    logic [31:0] seg_reg;
    logic [31:0] counter_reg;
    logic        counter_en;

    // 写入逻辑 (只写与读写寄存器)
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            led_reg     <= 32'b0;
            seg_reg     <= 32'b0;
            counter_reg <= 32'b0;
            counter_en  <= 1'b0;
        end else begin
            // 计数器逻辑 (只要使能生效，就一直自增)
            if (counter_en) begin
                counter_reg <= counter_reg + 1'b1;
            end
            
            // 外设写请求响应
            if (core_dram_wen && is_io_addr) begin
                if (core_dram_addr == 32'h8020_0020) begin
                    seg_reg <= core_dram_wdata;
                end 
                else if (core_dram_addr == 32'h8020_0040) begin
                    led_reg <= core_dram_wdata;
                end 
                else if (core_dram_addr == 32'h8020_0050) begin
                    if (core_dram_wdata == 32'h8000_0000) begin
                        counter_en <= 1'b1;        // 表⽰计数开始
                    end else if (core_dram_wdata == 32'hFFFF_FFFF) begin
                        counter_en <= 1'b0;        // 表⽰计数结束
                    end
                end
            end
        end
    end

    // 读取逻辑 (MUX 数据分发向 core_dram_rdata)
    always_comb begin
        if (is_io_addr) begin
            case (core_dram_addr)
                32'h8020_0000: core_dram_rdata = virtual_sw[31:0];      // 低32位开关
                32'h8020_0004: core_dram_rdata = virtual_sw[63:32];     // ⾼32位开关
                32'h8020_0010: core_dram_rdata = {24'd0, virtual_key};  // 按键
                32'h8020_0020: core_dram_rdata = seg_reg;               // 数码管可读写
                32'h8020_0050: core_dram_rdata = counter_reg;           // 计数器可读写
                default:       core_dram_rdata = 32'd0;
            endcase
        end else if (is_dram_addr) begin
            // 数据段读取 DRAM 数据
            core_dram_rdata = dram_rdata_real;
        end else begin
            // 其它未知地址默认回0
            core_dram_rdata = 32'd0;
        end
    end


    assign virtual_led = led_reg[P_LED_CNT-1:0];
 
    display_seg seg_driver (
        .clk    (clk),
        .rst    (w_clk_rst),
        .s      (seg_reg), 
        .seg1   (virtual_seg[6:0]),
        .seg2   (virtual_seg[16:10]),
        .seg3   (virtual_seg[26:20]),
        .seg4   (virtual_seg[36:30]),
        .ans    ({virtual_seg[39:38], virtual_seg[29:28], virtual_seg[19:18], virtual_seg[9:8]})
    ); 

    assign virtual_seg[7] = virtual_key[0];
    assign virtual_seg[17] = virtual_key[1];
    assign virtual_seg[27] = virtual_key[2];
    assign virtual_seg[37] = virtual_key[3];

endmodule
