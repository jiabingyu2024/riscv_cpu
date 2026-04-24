`include "cpu_defines.svh"

module core_new_regfile (
    input  logic             i_clk,
    input  logic             i_rst_n,
    input  logic [`RF_BUS]   i_rs1_addr,
    input  logic [`RF_BUS]   i_rs2_addr,
    input  logic             i_we,
    input  logic [`RF_BUS]   i_w_addr,
    input  logic [`DATA_BUS] i_w_data,
    output logic [`DATA_BUS] o_rs1_data,
    output logic [`DATA_BUS] o_rs2_data
);
    logic [`DATA_BUS] rf_mem [0:`RF_DEPTH-1];
    integer idx;

    always_ff @(negedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            for (idx = 0; idx < `RF_DEPTH; idx = idx + 1) begin
                rf_mem[idx] <= '0;
            end
        end else if (i_we && (i_w_addr != '0)) begin
            rf_mem[i_w_addr] <= i_w_data;
        end
    end

    assign o_rs1_data = (i_rs1_addr == '0) ? '0 : rf_mem[i_rs1_addr];
    assign o_rs2_data = (i_rs2_addr == '0) ? '0 : rf_mem[i_rs2_addr];
endmodule
