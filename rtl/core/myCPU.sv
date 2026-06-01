`timescale 1ns / 1ps
`include "cpu_defines.svh"

import BasicTypes::*;

module myCPU (
    input  logic        cpu_rst,
    input  logic        cpu_clk,

    // Interface to IROM
    output logic [31:0] irom_addrA,
    input  logic [31:0] irom_dataA,
    output logic        irom_enaA,
    output logic [31:0] irom_addrB,
    input  logic [31:0] irom_dataB,
    output logic        irom_enaB,


    // Interface to DRAM & peripheral bridge
    output logic [31:0] perip_addr,
    output logic        perip_wen,
    output logic [3:0]  perip_mask,
    output logic [31:0] perip_wdata,
    input  logic [31:0] perip_rdata
);

    IromAccessIF iromAccess(cpu_clk, cpu_rst);
    DramAccessIF dromAccess(cpu_clk, cpu_rst);
    DebugIF      debugIF(cpu_clk, cpu_rst);
    PerfIF       perfIF(cpu_clk, cpu_rst);

    assign debugIF.halt = 1'b0;

    always_comb begin
        irom_addrA = iromAccess.iromAddr;
        irom_addrB = iromAccess.iromAddr + 32'd4;
        irom_enaA = iromAccess.ena;
        irom_enaB = iromAccess.ena;

        iromAccess.inst[0] = irom_dataA;
        iromAccess.inst[1] = irom_dataB;
    end

    always_comb begin
        perip_addr = dromAccess.req ? dromAccess.addr : '0;
        perip_wen = dromAccess.req && dromAccess.we;
        perip_mask = perip_wen ? dromAccess.wstrb : '0;
        perip_wdata = dromAccess.wdata;

        dromAccess.rdata = perip_rdata;
        dromAccess.ready = 1'b1;
    end

    core u_core (
        .clk        (cpu_clk),
        .rst        (cpu_rst),
        .iromAccess (iromAccess),
        .dromAccess (dromAccess),
        .debug      (debugIF),
        .perf       (perfIF)
    );

endmodule
