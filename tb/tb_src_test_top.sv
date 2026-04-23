`timescale 1ns / 1ps

module tb_rv32ui_top (
    input  logic        i_clk_50mhz,
    input  logic        i_cpu_clk,
    input  logic        i_rst,
    input  logic [7:0]  i_virtual_key,
    input  logic [63:0] i_virtual_sw,
    output logic [31:0] o_virtual_led,
    output logic [39:0] o_virtual_seg
);
    string irom_file;
    string dram_file;

    student_top u_dut (
        .w_cpu_clk   (i_cpu_clk),
        .w_clk_50Mhz (i_clk_50mhz),
        .w_clk_rst   (i_rst),
        .virtual_key (i_virtual_key),
        .virtual_sw  (i_virtual_sw),
        .virtual_led (o_virtual_led),
        .virtual_seg (o_virtual_seg)
    );

    initial begin
        if (!$value$plusargs("irom=%s", irom_file)) begin
            $fatal(1, "missing +irom=<hex>");
        end
        $readmemh(irom_file, u_dut.Mem_IROM.mem);

        if ($value$plusargs("dram=%s", dram_file)) begin
            $readmemh(dram_file, u_dut.bridge_inst.dram_driver_inst.Mem_DRAM.mem);
        end
    end
endmodule
