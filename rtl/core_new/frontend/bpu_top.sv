`include "cpu_defines.svh"

module core_new_bpu_top (
    input  logic             i_clk,
    input  logic             i_rst_n,
    input  logic [`PC_BUS]   i_fetch_pc,
    input  logic             i_train_valid,
    input  logic [`PC_BUS]   i_train_pc,
    input  logic             i_train_taken,
    input  logic [`PC_BUS]   i_train_target,
    output logic             o_pred_valid,
    output logic             o_pred_taken,
    output logic [`PC_BUS]   o_pred_target
);
    localparam int BPU_ENTRIES = 128;
    localparam int BPU_IDX_W   = 7;
    localparam int BPU_TAG_W   = `PC_WID - BPU_IDX_W - 2;

    logic [BPU_TAG_W-1:0] tag_mem     [0:BPU_ENTRIES-1];
    logic [`PC_BUS]       target_mem  [0:BPU_ENTRIES-1];
    logic [1:0]           counter_mem [0:BPU_ENTRIES-1];
    logic                 valid_mem   [0:BPU_ENTRIES-1];
    logic [BPU_IDX_W-1:0] rd_idx;
    logic [BPU_TAG_W-1:0] rd_tag;
    logic [BPU_IDX_W-1:0] wr_idx;
    logic [BPU_TAG_W-1:0] wr_tag;
    integer idx;

    assign rd_idx = i_fetch_pc[BPU_IDX_W+1:2];
    assign rd_tag = i_fetch_pc[`PC_WID-1:BPU_IDX_W+2];
    assign wr_idx = i_train_pc[BPU_IDX_W+1:2];
    assign wr_tag = i_train_pc[`PC_WID-1:BPU_IDX_W+2];

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            for (idx = 0; idx < BPU_ENTRIES; idx = idx + 1) begin
                tag_mem[idx]     <= '0;
                target_mem[idx]  <= '0;
                counter_mem[idx] <= 2'b01;
                valid_mem[idx]   <= 1'b0;
            end
        end else if (i_train_valid) begin
            valid_mem[wr_idx]  <= 1'b1;
            tag_mem[wr_idx]    <= wr_tag;
            target_mem[wr_idx] <= i_train_target;

            if (i_train_taken) begin
                if (counter_mem[wr_idx] != 2'b11) begin
                    counter_mem[wr_idx] <= counter_mem[wr_idx] + 2'b01;
                end
            end else if (counter_mem[wr_idx] != 2'b00) begin
                counter_mem[wr_idx] <= counter_mem[wr_idx] - 2'b01;
            end
        end
    end

    always_comb begin
        o_pred_valid  = valid_mem[rd_idx] && (tag_mem[rd_idx] == rd_tag);
        o_pred_taken  = o_pred_valid && counter_mem[rd_idx][1];
        o_pred_target = target_mem[rd_idx];
    end
endmodule
