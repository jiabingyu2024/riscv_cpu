`timescale 1ns / 1ps

module myCPU (
    input  logic        cpu_rst,
    input  logic        cpu_clk,

    // Interface to IROM
    output logic [31:0] irom_addr,
    input  logic [31:0] irom_data,

    // Interface to DRAM & peripheral bridge
    output logic [31:0] perip_addr,
    output logic        perip_wen,
    output logic [1:0]  perip_mask,
    output logic [31:0] perip_wdata,
    input  logic [31:0] perip_rdata
);
    logic rst_n_int;
    assign rst_n_int = ~cpu_rst;

    core u_core (
        .clk        (cpu_clk),
        .rst_n      (rst_n_int),
        .irom_data  (irom_data),
        .irom_addr  (irom_addr),
        .dram_rdata (perip_rdata),
        .dram_wen   (perip_wen),
        .dram_addr  (perip_addr),
        .dram_wdata (perip_wdata),
        .dram_mask  (perip_mask)
    );

endmodule