//用于仿真的top模块，例化core,irom dram
`include "cpu_defines.svh"

module core_top #(
    parameter string IROM_INIT_FILE = "",
    parameter string DRAM_INIT_FILE = ""
)(
    input  logic          clk,
    input  logic          rst_n,
    output logic [`PC_BUS]       o_dbg_pc,
    output logic                 o_dbg_dram_wen,
    output logic [`RAM_ADDR_BUS] o_dbg_dram_addr,
    output logic [`DATA_BUS]     o_dbg_dram_wdata,
    output logic [1:0]           o_dbg_dram_mask
);
    logic [`DATA_BUS]     irom_data;
    logic [`PC_BUS]       irom_addr;
    logic [`DATA_BUS]     dram_rdata;
    logic                 dram_wen;
    logic [`RAM_ADDR_BUS] dram_addr;
    logic [`DATA_BUS]     dram_wdata;
    logic [1:0]           dram_mask;

    core u_core (
        .clk       (clk),
        .rst_n     (rst_n),
        .irom_data (irom_data),
        .irom_addr (irom_addr),
        .dram_rdata(dram_rdata),
        .dram_wen  (dram_wen),
        .dram_addr (dram_addr),
        .dram_wdata(dram_wdata),
        .dram_mask (dram_mask)
    );

    irom #(
        .INIT_FILE(IROM_INIT_FILE)
    ) u_irom (
        .i_pc    (irom_addr),
        .o_instr (irom_data)
    );

    dram #(
        .INIT_FILE(DRAM_INIT_FILE)
    ) u_dram (
        .i_clk       (clk),
        .i_rst_n     (rst_n),
        .i_mem_write (dram_wen),
        .i_mem_addr  (dram_addr),
        .i_mem_wdata (dram_wdata),
        .i_mem_mask  (dram_mask),
        .o_mem_rdata (dram_rdata)
    );

    assign o_dbg_pc         = irom_addr;
    assign o_dbg_dram_wen   = dram_wen;
    assign o_dbg_dram_addr  = dram_addr;
    assign o_dbg_dram_wdata = dram_wdata;
    assign o_dbg_dram_mask  = dram_mask;
endmodule
