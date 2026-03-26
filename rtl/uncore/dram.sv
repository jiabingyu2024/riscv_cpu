//==============================================================================
// 模块: dram
// 功能概述：
//   数据存储器（仿真/FPGA BRAM 或后续替换 AXI）。支持按 mask 的 store 与 load 读回（具体为字/半字/字节由 mask 定）。
// 接口/协作审查（供采纳）：
//   - 与 stage_mem 端口一致；`RAM_DEPTH`=4096 字时地址宽度与宏一致。
//   - 建议明确读写时序（同步读一拍 / 组合读）以便流水线时序闭合。
//==============================================================================
`include "include/cpu_defines.sv"

module dram #(
    parameter string INIT_FILE = ""
) (
    input logic                               i_clk,
    input logic                               i_rst_n,
    input logic                               i_mem_write,
    input logic [`RAM_ADDR_BUS]               i_mem_addr,
    input logic [`DATA_BUS]                   i_mem_wdata,
    input logic [1:0]                         i_mem_mask, // 见defines
    output logic [`DATA_BUS]                  o_mem_rdata
);

    logic [7:0] mem_bytes [0:`RAM_DEPTH-1];
    logic [`RAM_ADDR_BUS] base_addr;
    string load_file;
    integer idx;

    assign base_addr = {i_mem_addr[`RAM_ADDR_WID-1:2], 2'b00};

    initial begin
        for (idx = 0; idx < `RAM_DEPTH; idx = idx + 1) begin
            mem_bytes[idx] = '0;
        end

        load_file = INIT_FILE;
        if (!$value$plusargs("DRAM=%s", load_file)) begin
            load_file = INIT_FILE;
        end

        if (load_file != "") begin
            $readmemh(load_file, mem_bytes);
        end
    end

    always @(posedge i_clk) begin
        if (i_mem_write) begin
            unique case (i_mem_mask)
                `MASK_BYTE: begin
                    mem_bytes[i_mem_addr] <= i_mem_wdata[7:0];
                end
                `MASK_HALF: begin
                    mem_bytes[i_mem_addr]         <= i_mem_wdata[7:0];
                    mem_bytes[i_mem_addr + 14'd1] <= i_mem_wdata[15:8];
                end
                default: begin
                    mem_bytes[i_mem_addr]         <= i_mem_wdata[7:0];
                    mem_bytes[i_mem_addr + 14'd1] <= i_mem_wdata[15:8];
                    mem_bytes[i_mem_addr + 14'd2] <= i_mem_wdata[23:16];
                    mem_bytes[i_mem_addr + 14'd3] <= i_mem_wdata[31:24];
                end
            endcase
        end
    end

    always_comb begin
        o_mem_rdata = {
            mem_bytes[base_addr + 14'd3],
            mem_bytes[base_addr + 14'd2],
            mem_bytes[base_addr + 14'd1],
            mem_bytes[base_addr]
        };
    end
endmodule