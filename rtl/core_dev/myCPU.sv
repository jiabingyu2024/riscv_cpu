`timescale 1ns / 1ps
`include "cpu_defines.svh"

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
    logic irom_ena_unused;
    logic [3:0] perip_mask_core;

    assign rst_n_int = ~cpu_rst;

    always_comb begin
        unique case (perip_mask_core)
            `MASK_BYTE: perip_mask = 2'd0;
            `MASK_HALF: perip_mask = 2'd1;
            default:    perip_mask = 2'd2;
        endcase
    end

    core u_core (
        .clk        (cpu_clk),
        .rst_n      (rst_n_int),
        .irom_data  (irom_data),
        .irom_addr  (irom_addr),
        .irom_ena   (irom_ena_unused),
        .dram_rdata (perip_rdata),
        .dram_wen   (perip_wen),
        .dram_addr  (perip_addr),
        .dram_wdata (perip_wdata),
        .dram_mask  (perip_mask_core)
    );

endmodule
