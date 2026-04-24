//==============================================================================
// 模块: core_top
// 功能概述：
//   SoC/CPU 核顶层。仅例化 IF/ID/EX/MEM/WB、流水线寄存器、前递单元、冒险单元、BPU
//   等子模块并完成信号互连；不包含组合功能逻辑（仲裁、译码等应在下级模块实现）。
// 接口/协作审查（供采纳）：
//   - 当前仅 clk/rst_n；外设、总线、中断等按赛题在顶层或外层 wrapper 扩展。
//   - 命名：子模块例化前缀 u_；流水线相关时钟/复位/控制建议 F/D/E/M/W 分级命名便于 debug。
//==============================================================================
`include "cpu_defines.svh"

module core(
    input  logic                                     clk,
    input  logic                                     rst_n,

    input  logic  [`DATA_BUS]                        irom_data,
    output logic  [`PC_BUS]                          irom_addr,

    input  logic  [`DATA_BUS]                        dram_rdata,
    output logic                                     dram_wen,
    output logic  [`RAM_ADDR_BUS]                    dram_addr,
    output logic  [`DATA_BUS]                        dram_wdata,
    output logic  [1:0]                              dram_mask

);
    logic [`PC_BUS]   pc_next_hz;
    logic [`PC_BUS]   pc_predict_f;
    logic [`INST_BUS] inst_f;
    logic             predict_taken_f;
    logic [`PC_BUS]   predict_target_f;
    logic             btb_hit_f;
    logic             frontend_predict_taken_f;

    logic [`PC_BUS]   pc_d;
    logic [`INST_BUS] inst_d;
    logic [`PC_BUS]   pc_predict_d;
    logic             use_rs1_d;
    logic             use_rs2_d;

    logic             mem_read_d;
    logic             mem_write_d;
    logic             reg_write_d;
    logic             wb_src_d;
    logic             is_rs2_imm_d;
    logic [3:0]       inst_spec_d;
    logic [3:0]       alu_ctrl_d;
    logic [2:0]       func3_d;
    logic [1:0]       mem_mask_d;
    logic             load_unsigned_d;
    logic             is_branch_d;
    logic [`DATA_BUS] imm_d;
    logic [`PC_BUS]   pc_plus_imm_d;
    logic [`DATA_BUS] rs1_data_d;
    logic [`RF_BUS]   rs1_addr_d;
    logic [`DATA_BUS] rs2_data_d;
    logic [`RF_BUS]   rs2_addr_d;
    logic [`RF_BUS]   rd_addr_d;

    logic [`DATA_BUS] rs1_data_e;
    logic [`DATA_BUS] rs2_data_e;
    logic [`RF_BUS]   rd_addr_e;
    logic [`RF_BUS]   rs1_addr_e;
    logic [`RF_BUS]   rs2_addr_e;
    logic [`DATA_BUS] imm_e;
    logic [`PC_BUS]   pc_plus_imm_e;
    logic             mem_read_e;
    logic             reg_write_e;
    logic             mem_write_e;
    logic             wb_src_e;
    logic             is_rs2_imm_e;
    logic [3:0]       inst_spec_e;
    logic [3:0]       alu_ctrl_e;
    logic [2:0]       func3_e;
    logic [1:0]       mem_mask_e;
    logic             load_unsigned_e;
    logic             is_branch_e;
    logic [`PC_BUS]   pc_e;
    logic [`PC_BUS]   pc_predict_e;

    logic [2:0]       b1_sel_e;
    logic [2:0]       b2_sel_e;
    logic [2:0]       t1_sel_e;
    logic [2:0]       a1_sel_e;
    logic [2:0]       a2_sel_e;

    logic [`DATA_BUS] alu_res_e;
    logic [`DATA_BUS] a2_data_e;
    logic             update_taken_e;
    logic             update_en_e;
    logic [`PC_BUS]   update_pc_e;
    logic [`PC_BUS]   update_target_e;
    logic             error_e;
    logic [`PC_BUS]   right_pc_e;

    logic [`RF_BUS]   rd_addr_m;
    logic [`DATA_BUS] alu_res_m;
    logic [`DATA_BUS] a2_data_m;
    logic             mem_read_m;
    logic             mem_write_m;
    logic             wb_src_m;
    logic             reg_write_m;
    logic [1:0]       mem_mask_m;
    logic             load_unsigned_m;
    logic [`DATA_BUS] mem_data_m;
    logic             update_taken_m;
    logic             update_en_m;
    logic [`PC_BUS]   update_pc_m;
    logic [`PC_BUS]   update_target_m;
    logic             error_m;
    logic [`PC_BUS]   right_pc_m;

    logic [`DATA_BUS] alu_res_w;
    logic [`RF_BUS]   rd_addr_w;
    logic [`DATA_BUS] mem_data_w;
    logic             wb_src_w;
    logic             reg_write_w;
    logic [`DATA_BUS] wb_data_w;

    logic             stall_f_d;
    logic             stall_d_e;
    logic             stall_e_m;
    logic             stall_m_w;
    logic             flush_f_d;
    logic             flush_d_e;
    logic             flush_e_m;
    logic             flush_m_w;
    logic             inst_valid_e;
    logic             flush_any;

    logic [63:0]      cycle_count;
    logic [63:0]      instret_count;
    logic [63:0]      branch_count;
    logic [63:0]      btb_hit_count;
    logic [63:0]      predict_taken_count;
    logic [63:0]      branch_mispredict_count;
    logic [63:0]      load_use_stall_count;
    logic [63:0]      data_hazard_stall_count;
    logic [63:0]      flush_count;

    stage_if u_stage_if (
        .i_clk       (clk),
        .i_rst_n     (rst_n),
        .i_pc_next   (pc_next_hz),
        .i_irom_data (irom_data),
        .o_instr     (inst_f),
        .o_pc_cur    (irom_addr)
    );

    bpu_top u_bpu_top (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_pc_cur        (irom_addr),
        .i_update_en     (update_en_m),
        .i_update_taken  (update_taken_m),
        .i_update_target (update_target_m),
        .i_update_pc     (update_pc_m),
        .o_btb_hit       (btb_hit_f),
        .o_predict_taken (predict_taken_f),
        .o_predict_target(predict_target_f)
    );

    hazard_unit u_hazard_unit (
        .i_pc_cur        (irom_addr),
        .i_inst_f        (inst_f),
        .i_rs1_addr_d    (rs1_addr_d),
        .i_rs2_addr_d    (rs2_addr_d),
        .i_use_rs1_d     (use_rs1_d),
        .i_use_rs2_d     (use_rs2_d),
        .i_rd_addr_e     (rd_addr_e),
        .i_mem_read_e    (mem_read_e),
        .i_reg_write_e   (reg_write_e),
        .i_btb_hit       (btb_hit_f),
        .i_predict_taken (predict_taken_f),
        .i_predict_target(predict_target_f),
        .i_error         (error_m),
        .i_right_pc      (right_pc_m),
        .o_stall_f_d     (stall_f_d),
        .o_stall_d_e     (stall_d_e),
        .o_stall_e_m     (stall_e_m),
        .o_stall_m_w     (stall_m_w),
        .o_flush_f_d     (flush_f_d),
        .o_flush_d_e     (flush_d_e),
        .o_flush_e_m     (flush_e_m),
        .o_flush_m_w     (flush_m_w),
        .o_predict_taken_final(frontend_predict_taken_f),
        .o_pc_next       (pc_next_hz),
        .o_pc_predict    (pc_predict_f)
    );

    reg_if_id u_reg_if_id (
        .i_clk        (clk),
        .i_rst_n      (rst_n),
        .i_flush      (flush_f_d),
        .i_stall      (stall_f_d),
        .i_pc_f_d     (irom_addr),
        .i_inst_f_d   (inst_f),
        .i_pc_predict (pc_predict_f),
        .o_pc_f_d     (pc_d),
        .o_inst_f_d   (inst_d),
        .o_pc_predict (pc_predict_d)
    );

    stage_id u_stage_id (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_pc_f_d        (pc_d),
        .i_inst_f_d      (inst_d),
        .i_pc_predict    (pc_predict_d),
        .i_we            (reg_write_w),
        .i_w_addr        (rd_addr_w),
        .i_w_data        (wb_data_w),
        .o_mem_read      (mem_read_d),
        .o_mem_write     (mem_write_d),
        .o_reg_write     (reg_write_d),
        .o_wb_src        (wb_src_d),
        .o_is_rs2_imm    (is_rs2_imm_d),
        .o_inst_spec     (inst_spec_d),
        .o_alu_ctrl      (alu_ctrl_d),
        .o_func3         (func3_d),
        .o_mem_mask      (mem_mask_d),
        .o_load_unsigned (load_unsigned_d),
        .o_use_rs1       (use_rs1_d),
        .o_use_rs2       (use_rs2_d),
        .o_is_branch     (is_branch_d),
        .o_imm           (imm_d),
        .o_pc_plus_imm   (pc_plus_imm_d),
        .o_rs1_data      (rs1_data_d),
        .o_rs1_addr      (rs1_addr_d),
        .o_rs2_data      (rs2_data_d),
        .o_rs2_addr      (rs2_addr_d),
        .o_rd_addr       (rd_addr_d)
    );

    reg_id_ex u_reg_id_ex (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_flush         (flush_d_e),
        .i_stall         (stall_d_e),
        .i_rs1_data      (rs1_data_d),
        .i_rs1_addr      (rs1_addr_d),
        .i_rs2_data      (rs2_data_d),
        .i_rs2_addr      (rs2_addr_d),
        .i_rd_addr       (rd_addr_d),
        .i_imm           (imm_d),
        .i_pc_plus_imm   (pc_plus_imm_d),
        .i_mem_read      (mem_read_d),
        .i_reg_write     (reg_write_d),
        .i_mem_write     (mem_write_d),
        .i_wb_src        (wb_src_d),
        .i_is_rs2_imm    (is_rs2_imm_d),
        .i_inst_spec     (inst_spec_d),
        .i_alu_ctrl      (alu_ctrl_d),
        .i_func3         (func3_d),
        .i_mem_mask      (mem_mask_d),
        .i_load_unsigned (load_unsigned_d),
        .i_is_branch     (is_branch_d),
        .i_pc_d_e        (pc_d),
        .i_pc_predict    (pc_predict_d),
        .o_rs1_data      (rs1_data_e),
        .o_rs2_data      (rs2_data_e),
        .o_rd_addr       (rd_addr_e),
        .o_rs1_addr      (rs1_addr_e),
        .o_rs2_addr      (rs2_addr_e),
        .o_imm           (imm_e),
        .o_pc_plus_imm   (pc_plus_imm_e),
        .o_mem_read      (mem_read_e),
        .o_reg_write     (reg_write_e),
        .o_mem_write     (mem_write_e),
        .o_wb_src        (wb_src_e),
        .o_is_rs2_imm    (is_rs2_imm_e),
        .o_inst_spec     (inst_spec_e),
        .o_alu_ctrl      (alu_ctrl_e),
        .o_func3         (func3_e),
        .o_mem_mask      (mem_mask_e),
        .o_load_unsigned (load_unsigned_e),
        .o_is_branch     (is_branch_e),
        .o_pc_d_e        (pc_e),
        .o_pc_predict    (pc_predict_e)
    );

    forward_unit u_forward_unit (
        .i_rs1_addr      (rs1_addr_e),
        .i_rs2_addr      (rs2_addr_e),
        .i_rd_addr_e_m   (rd_addr_m),
        .i_rd_addr_m_w   (rd_addr_w),
        .i_reg_write_e_m (reg_write_m),
        .i_reg_write_m_w (reg_write_w),
        .i_is_rs2_imm    (is_rs2_imm_e),
        .i_inst_spec     (inst_spec_e),
        .o_b1_sel        (b1_sel_e),
        .o_b2_sel        (b2_sel_e),
        .o_t1_sel        (t1_sel_e),
        .o_a1_sel        (a1_sel_e),
        .o_a2_sel        (a2_sel_e)
    );

    stage_ex u_stage_ex (
        .i_rs1_data      (rs1_data_e),
        .i_rs2_data      (rs2_data_e),
        .i_imm           (imm_e),
        .i_pc            (pc_e),
        .i_pc_plus_imm   (pc_plus_imm_e),
        .i_fwd_e_m       (alu_res_m),
        .i_fwd_m_w       (wb_data_w),
        .i_pc_d_e        (pc_e),
        .i_pc_predict    (pc_predict_e),
        .i_b1_sel        (b1_sel_e),
        .i_b2_sel        (b2_sel_e),
        .i_t1_sel        (t1_sel_e),
        .i_a1_sel        (a1_sel_e),
        .i_a2_sel        (a2_sel_e),
        .i_alu_ctrl      (alu_ctrl_e),
        .i_func3         (func3_e),
        .i_is_branch     (is_branch_e),
        .i_inst_spec     (inst_spec_e),
        .o_alu_res       (alu_res_e),
        .o_a2_data       (a2_data_e),
        .o_update_taken  (update_taken_e),
        .o_update_en     (update_en_e),
        .o_update_pc     (update_pc_e),
        .o_update_target (update_target_e),
        .o_error         (error_e),
        .o_right_pc      (right_pc_e)
    );

    reg_ex_mem u_reg_ex_mem (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_flush         (flush_e_m),
        .i_stall         (stall_e_m),
        .i_rd_addr       (rd_addr_e),
        .i_alu_res       (alu_res_e),
        .i_A2_data       (a2_data_e),
        .i_cf_update_taken(update_taken_e),
        .i_cf_update_en  (update_en_e),
        .i_cf_update_pc  (update_pc_e),
        .i_cf_update_target(update_target_e),
        .i_cf_error      (error_e),
        .i_cf_right_pc   (right_pc_e),
        .i_mem_read      (mem_read_e),
        .i_mem_write     (mem_write_e),
        .i_wb_src        (wb_src_e),
        .i_reg_write     (reg_write_e),
        .i_mem_mask      (mem_mask_e),
        .i_load_unsigned (load_unsigned_e),
        .o_rd_addr       (rd_addr_m),
        .o_alu_res       (alu_res_m),
        .o_a2_data       (a2_data_m),
        .o_cf_update_taken(update_taken_m),
        .o_cf_update_en  (update_en_m),
        .o_cf_update_pc  (update_pc_m),
        .o_cf_update_target(update_target_m),
        .o_cf_error      (error_m),
        .o_cf_right_pc   (right_pc_m),
        .o_mem_read      (mem_read_m),
        .o_mem_write     (mem_write_m),
        .o_wb_src        (wb_src_m),
        .o_reg_write     (reg_write_m),
        .o_mem_mask      (mem_mask_m),
        .o_load_unsigned (load_unsigned_m)
    );

    stage_mem u_stage_mem (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_mem_write     (mem_write_m),
        .i_mem_addr      (alu_res_m[`RAM_ADDR_BUS]),
        .i_mem_wdata     (a2_data_m),
        .i_mem_mask      (mem_mask_m),
        .i_load_unsigned (load_unsigned_m),
        .i_dram_rdata    (dram_rdata),
        .o_dram_wen      (dram_wen),
        .o_dram_addr     (dram_addr),
        .o_dram_wdata    (dram_wdata),
        .o_dram_mask     (dram_mask),
        .o_mem_rdata     (mem_data_m)
    );

    reg_mem_wb u_reg_mem_wb (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_flush         (flush_m_w),
        .i_stall         (stall_m_w),
        .i_reg_write     (reg_write_m),
        .i_wb_src        (wb_src_m),
        .i_alu_res       (alu_res_m),
        .i_rd_addr       (rd_addr_m),
        .i_mem_data      (mem_data_m),
        .o_alu_res       (alu_res_w),
        .o_rd_addr       (rd_addr_w),
        .o_mem_data      (mem_data_w),
        .o_wb_src        (wb_src_w),
        .o_reg_write     (reg_write_w)
    );

    stage_wb u_stage_wb (
        .i_alu_res       (alu_res_w),
        .i_mem_data      (mem_data_w),
        .i_wb_src        (wb_src_w),
        .o_wb_data       (wb_data_w)
    );

    assign inst_valid_e = !flush_e_m && (reg_write_e || mem_write_e || update_en_e);
    assign flush_any = flush_f_d || flush_d_e || flush_e_m || flush_m_w;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cycle_count              <= '0;
            instret_count            <= '0;
            branch_count             <= '0;
            btb_hit_count            <= '0;
            predict_taken_count      <= '0;
            branch_mispredict_count  <= '0;
            load_use_stall_count     <= '0;
            data_hazard_stall_count  <= '0;
            flush_count              <= '0;
        end else begin
            cycle_count <= cycle_count + 64'd1;

            if (inst_valid_e) begin
                instret_count <= instret_count + 64'd1;
            end
            if (update_en_m) begin
                branch_count <= branch_count + 64'd1;
            end
            if (btb_hit_f) begin
                btb_hit_count <= btb_hit_count + 64'd1;
            end
            if (frontend_predict_taken_f && !stall_f_d) begin
                predict_taken_count <= predict_taken_count + 64'd1;
            end
            if (update_en_m && error_m) begin
                branch_mispredict_count <= branch_mispredict_count + 64'd1;
            end
            if (stall_f_d) begin
                data_hazard_stall_count <= data_hazard_stall_count + 64'd1;
                if (mem_read_e && reg_write_e) begin
                    load_use_stall_count <= load_use_stall_count + 64'd1;
                end
            end
            if (flush_any) begin
                flush_count <= flush_count + 64'd1;
            end
        end
    end
endmodule
