//==============================================================================
// 模块: bpu_top
// 功能概述:
//   分支预测器顶层。
//   - 条件分支方向: 全局 gshare 与局部历史的竞争预测器。
//   - 目标地址: 64 项 BTB，缺失时预测顺序执行 PC+4。
//   - 返回地址: 简单 RAS。由于 IROM 同步读，return 在 IF 拿到指令后一拍重定向。
//==============================================================================
`include "cpu_defines.svh"

module bpu_top (
    input  logic                                    i_clk,
    input  logic                                    i_rst_n,

    input  logic  [`PC_BUS]                         i_pc_cur,

    input  logic                                    i_f_valid,
    input  logic  [`PC_BUS]                         i_f_pc,
    input  logic  [`INST_BUS]                       i_f_inst,

    input  logic                                    i_update_en,
    input  logic                                    i_update_taken,
    input  logic  [`PC_BUS]                         i_update_target,
    input  logic  [`PC_BUS]                         i_update_pc,
    input  logic                                    i_update_is_branch,
    input  logic  [3:0]                             i_update_inst_spec,
    input  logic  [`RF_BUS]                         i_update_rd_addr,
    input  logic  [`RF_BUS]                         i_update_rs1_addr,
    input  logic  [7:0]                              i_update_pht_idx,
    input  logic  [7:0]                              i_update_local_pht_idx,
    input  logic  [7:0]                              i_update_choice_idx,
    input  logic                                    i_update_global_pred_taken,
    input  logic                                    i_update_local_pred_taken,

    output logic                                    o_predict_taken,
    output logic  [`PC_BUS]                         o_predict_target,
    output logic  [7:0]                              o_pht_idx,
    output logic  [7:0]                              o_local_pht_idx,
    output logic  [7:0]                              o_choice_idx,
    output logic                                    o_global_pred_taken,
    output logic                                    o_local_pred_taken,
    output logic                                    o_ras_redirect,
    output logic  [`PC_BUS]                         o_ras_target
);

    localparam int BTB_ENTRIES = 128;
    localparam int BTB_IDX_W   = 7;
    localparam int BTB_TAG_W   = `PC_WID - BTB_IDX_W - 2;

    localparam int GHR_W       = 8;
    localparam int PHT_ENTRIES = 256;
    localparam int LHT_ENTRIES = 128;
    localparam int LHT_IDX_W   = 7;
    localparam int CHOICE_ENTRIES = 256;

    localparam int RAS_DEPTH   = 8;
    localparam int RAS_CNT_W   = 4;
    localparam int RAS_IDX_W   = $clog2(RAS_DEPTH);
    localparam logic [RAS_CNT_W-1:0] RAS_DEPTH_VALUE = RAS_CNT_W'(RAS_DEPTH);
    localparam logic [RAS_IDX_W-1:0] RAS_IDX_ONE = {{(RAS_IDX_W-1){1'b0}}, 1'b1};

    localparam logic [1:0] BTB_TYPE_COND = 2'b00;
    localparam logic [1:0] BTB_TYPE_JAL  = 2'b01;

    logic [BTB_TAG_W-1:0] tag_mem    [0:BTB_ENTRIES-1];
    logic [`PC_BUS]       target_mem [0:BTB_ENTRIES-1];
    logic [1:0]           type_mem   [0:BTB_ENTRIES-1];
    logic                 valid_mem  [0:BTB_ENTRIES-1];

    logic [1:0]           pht_mem        [0:PHT_ENTRIES-1];
    logic [GHR_W-1:0]     local_hist_mem [0:LHT_ENTRIES-1];
    logic [1:0]           local_pht_mem  [0:PHT_ENTRIES-1];
    logic [1:0]           choice_mem     [0:CHOICE_ENTRIES-1];
    logic [GHR_W-1:0]     ghr;

    logic [`PC_BUS]       ras_stack  [0:RAS_DEPTH-1];
    logic [RAS_CNT_W-1:0] ras_count;
    logic [RAS_IDX_W-1:0] ras_top_idx;
    logic [RAS_IDX_W-1:0] ras_push_idx;

    logic [BTB_IDX_W-1:0] rd_idx;
    logic [BTB_TAG_W-1:0] rd_tag;
    logic [BTB_IDX_W-1:0] wr_idx;
    logic [BTB_TAG_W-1:0] wr_tag;
    logic [LHT_IDX_W-1:0] local_hist_rd_idx;
    logic [LHT_IDX_W-1:0] local_hist_wr_idx;
    logic [GHR_W-1:0]     pht_rd_idx;
    logic [GHR_W-1:0]     local_pht_rd_idx;
    logic [GHR_W-1:0]     choice_rd_idx;
    logic                 btb_hit;
    logic                 pht_predict_taken;
    logic                 local_predict_taken;
    logic                 choice_use_local;
    logic                 selected_predict_taken;
    logic                 update_cond_branch;
    logic                 update_jal;
    logic                 ras_push;
    logic                 ras_pop;
    logic                 f_is_return;
    integer idx;

    assign rd_idx = i_pc_cur[BTB_IDX_W+1:2];
    assign rd_tag = i_pc_cur[`PC_WID-1:BTB_IDX_W+2];
    assign wr_idx = i_update_pc[BTB_IDX_W+1:2];
    assign wr_tag = i_update_pc[`PC_WID-1:BTB_IDX_W+2];
    assign local_hist_rd_idx = i_pc_cur[LHT_IDX_W+1:2];
    assign local_hist_wr_idx = i_update_pc[LHT_IDX_W+1:2];

    assign pht_rd_idx = i_pc_cur[GHR_W+1:2] ^ ghr;
    assign local_pht_rd_idx = i_pc_cur[GHR_W+1:2] ^ local_hist_mem[local_hist_rd_idx];
    assign choice_rd_idx = i_pc_cur[GHR_W+1:2];
    assign ras_top_idx = ras_count[RAS_IDX_W-1:0] - RAS_IDX_ONE;
    assign ras_push_idx = ras_count[RAS_IDX_W-1:0];
    assign o_pht_idx = pht_rd_idx;
    assign o_local_pht_idx = local_pht_rd_idx;
    assign o_choice_idx = choice_rd_idx;

    assign btb_hit = valid_mem[rd_idx] && (tag_mem[rd_idx] == rd_tag);
    assign pht_predict_taken = pht_mem[pht_rd_idx][1];
    assign local_predict_taken = local_pht_mem[local_pht_rd_idx][1];
    assign choice_use_local = choice_mem[choice_rd_idx][1];
    assign selected_predict_taken = choice_use_local ? local_predict_taken : pht_predict_taken;
    assign o_global_pred_taken = pht_predict_taken;
    assign o_local_pred_taken = local_predict_taken;

    assign update_cond_branch = i_update_en && i_update_is_branch;
    assign update_jal = i_update_en && (i_update_inst_spec == `EX_JAL);

    assign ras_push = update_jal &&
                      ((i_update_rd_addr == 5'd1) || (i_update_rd_addr == 5'd5));

    assign ras_pop = i_update_en &&
                     (i_update_inst_spec == `EX_JALR) &&
                     ((i_update_rs1_addr == 5'd1) || (i_update_rs1_addr == 5'd5)) &&
                     (i_update_rd_addr == 5'd0);

    assign f_is_return = i_f_valid &&
                         (i_f_inst[6:0] == `OP_JALR) &&
                         ((i_f_inst[19:15] == 5'd1) || (i_f_inst[19:15] == 5'd5)) &&
                         (i_f_inst[11:7] == 5'd0);

    always_comb begin
        o_predict_taken  = 1'b0;
        o_predict_target = i_pc_cur + 32'd4;

        if (btb_hit) begin
            unique case (type_mem[rd_idx])
                BTB_TYPE_COND: begin
                    o_predict_taken  = selected_predict_taken;
                    o_predict_target = selected_predict_taken ? target_mem[rd_idx] : (i_pc_cur + 32'd4);
                end
                BTB_TYPE_JAL: begin
                    o_predict_taken  = 1'b1;
                    o_predict_target = target_mem[rd_idx];
                end
                default: begin
                    o_predict_taken  = 1'b0;
                    o_predict_target = i_pc_cur + 32'd4;
                end
            endcase
        end
    end

    always_comb begin
        o_ras_redirect = f_is_return && (ras_count != '0);
        if (ras_count != '0) begin
            o_ras_target = ras_stack[ras_top_idx];
        end else begin
            o_ras_target = i_f_pc + 32'd4;
        end
    end

    always_ff @(posedge i_clk or negedge i_rst_n) begin
        if (!i_rst_n) begin
            ghr       <= '0;
            ras_count <= '0;
            for (idx = 0; idx < BTB_ENTRIES; idx = idx + 1) begin
                tag_mem[idx]    <= '0;
                target_mem[idx] <= '0;
                type_mem[idx]   <= BTB_TYPE_COND;
                valid_mem[idx]  <= 1'b0;
            end
            for (idx = 0; idx < PHT_ENTRIES; idx = idx + 1) begin
                pht_mem[idx]       <= 2'b01;
                local_pht_mem[idx] <= 2'b01;
                choice_mem[idx]    <= 2'b01;
            end
            for (idx = 0; idx < LHT_ENTRIES; idx = idx + 1) begin
                local_hist_mem[idx] <= '0;
            end
            for (idx = 0; idx < RAS_DEPTH; idx = idx + 1) begin
                ras_stack[idx] <= '0;
            end
        end else begin
            if (update_cond_branch) begin
                if (i_update_taken) begin
                    valid_mem[wr_idx]  <= 1'b1;
                    tag_mem[wr_idx]    <= wr_tag;
                    target_mem[wr_idx] <= i_update_target;
                    type_mem[wr_idx]   <= BTB_TYPE_COND;
                    if (pht_mem[i_update_pht_idx] != 2'b11) begin
                        pht_mem[i_update_pht_idx] <= pht_mem[i_update_pht_idx] + 2'b01;
                    end
                    if (local_pht_mem[i_update_local_pht_idx] != 2'b11) begin
                        local_pht_mem[i_update_local_pht_idx] <= local_pht_mem[i_update_local_pht_idx] + 2'b01;
                    end
                end else begin
                    if (pht_mem[i_update_pht_idx] != 2'b00) begin
                        pht_mem[i_update_pht_idx] <= pht_mem[i_update_pht_idx] - 2'b01;
                    end
                    if (local_pht_mem[i_update_local_pht_idx] != 2'b00) begin
                        local_pht_mem[i_update_local_pht_idx] <= local_pht_mem[i_update_local_pht_idx] - 2'b01;
                    end
                end
                if (i_update_global_pred_taken != i_update_local_pred_taken) begin
                    if ((i_update_local_pred_taken == i_update_taken) && (choice_mem[i_update_choice_idx] != 2'b11)) begin
                        choice_mem[i_update_choice_idx] <= choice_mem[i_update_choice_idx] + 2'b01;
                    end else if ((i_update_global_pred_taken == i_update_taken) && (choice_mem[i_update_choice_idx] != 2'b00)) begin
                        choice_mem[i_update_choice_idx] <= choice_mem[i_update_choice_idx] - 2'b01;
                    end
                end
                local_hist_mem[local_hist_wr_idx] <= {local_hist_mem[local_hist_wr_idx][GHR_W-2:0], i_update_taken};
                ghr <= {ghr[GHR_W-2:0], i_update_taken};
            end else if (update_jal) begin
                valid_mem[wr_idx]  <= 1'b1;
                tag_mem[wr_idx]    <= wr_tag;
                target_mem[wr_idx] <= i_update_target;
                type_mem[wr_idx]   <= BTB_TYPE_JAL;
            end

            if (ras_pop && (ras_count != '0)) begin
                ras_count <= ras_count - 1'b1;
            end else if (ras_push) begin
                if (ras_count == RAS_DEPTH_VALUE) begin
                    ras_stack[RAS_DEPTH-1] <= i_update_pc + 32'd4;
                end else begin
                    ras_stack[ras_push_idx] <= i_update_pc + 32'd4;
                    ras_count <= ras_count + 1'b1;
                end
            end
        end
    end
endmodule
