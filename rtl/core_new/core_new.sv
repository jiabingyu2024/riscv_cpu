`include "cpu_defines.svh"

module core_new (
    input  logic                     clk,
    input  logic                     rst_n,

    input  logic [`DATA_BUS]         irom_data,
    output logic [`PC_BUS]           irom_addr,
    output logic                     irom_ena,

    input  logic [`DATA_BUS]         dram_rdata,
    output logic                     dram_wen,
    output logic [`RAM_ADDR_BUS]     dram_addr,
    output logic [`DATA_BUS]         dram_wdata,
    output logic [3:0]               dram_mask
);
    // Compatibility probes for existing simulation tooling.
    logic                            update_en_e;
    logic                            error_e;
    logic                            flush_e_m;

    logic [`PC_BUS] pc_cur_p;
    logic [`PC_BUS] pc_next_p;
    logic           redirect_valid_p;
    logic [`PC_BUS] redirect_pc_p;

    logic        pred_valid_p;
    logic        pred_taken_p;
    logic [`PC_BUS] pred_target_p;
    logic        fetch_pred_valid_p;
    logic        pred_valid_pf;
    logic        pred_is_static_pf;
    logic        fetch_pred_taken_p;
    logic [`PC_BUS] fetch_pred_target_p;

    logic stall_pc_if;
    logic stall_if_id;
    logic flush_pc_if;
    logic flush_if_id;
    logic flush_id_ex;
    logic flush_ex_m1;

    logic [`PC_BUS] pc_pf;
    logic           pred_taken_pf;
    logic [`PC_BUS] pred_target_pf;
    logic           valid_pf;

    logic [`PC_BUS] pc_f;
    logic [`INST_BUS] inst_f;
    logic           static_redirect_valid_f;
    logic [`PC_BUS] static_redirect_pc_f;
    logic           pred_valid_f;
    logic           pred_is_static_f;
    logic           pred_taken_f;
    logic [`PC_BUS] pred_target_f;
    logic           valid_f;

    logic [`PC_BUS] pc_d;
    logic [`INST_BUS] inst_d;
    logic           pred_valid_d;
    logic           pred_is_static_d;
    logic           pred_taken_d;
    logic [`PC_BUS] pred_target_d;
    logic           valid_d;

    logic           mem_read_d;
    logic           mem_write_d;
    logic           reg_write_d;
    logic           wb_sel_d;
    logic [3:0]     alu_op_d;
    logic [2:0]     branch_type_d;
    logic           is_branch_d;
    logic           is_jal_d;
    logic           is_jalr_d;
    logic           is_lui_d;
    logic           is_auipc_d;
    logic           src2_is_imm_d;
    logic           use_rs1_d;
    logic           use_rs2_d;
    logic [3:0]     mem_size_d;
    logic           load_unsigned_d;
    logic [`DATA_BUS] imm_d;
    logic [`RF_BUS] rs1_addr_d;
    logic [`RF_BUS] rs2_addr_d;
    logic [`RF_BUS] rd_addr_d;
    logic [`DATA_BUS] rs1_data_d;
    logic [`DATA_BUS] rs2_data_d;
    logic [`PC_BUS] jal_target_d;
    logic           redirect_valid_d;
    logic [`PC_BUS] redirect_pc_d;
    logic           pred_taken_issue_d;
    logic [`PC_BUS] pred_target_issue_d;

    logic [`PC_BUS] pc_e;
    logic           pred_valid_e;
    logic           pred_is_static_e;
    logic           pred_taken_e;
    logic [`PC_BUS] pred_target_e;
    logic [`DATA_BUS] rs1_data_e;
    logic [`DATA_BUS] rs2_data_e;
    logic [`RF_BUS] rs1_addr_e;
    logic [`RF_BUS] rs2_addr_e;
    logic [`RF_BUS] rd_addr_e;
    logic [`DATA_BUS] imm_e;
    logic           mem_read_e;
    logic           mem_write_e;
    logic           reg_write_e;
    logic           wb_sel_e;
    logic [3:0]     alu_op_e;
    logic [2:0]     branch_type_e;
    logic           is_branch_e;
    logic           is_jal_e;
    logic           is_jalr_e;
    logic           is_lui_e;
    logic           is_auipc_e;
    logic           src2_is_imm_e;
    logic [3:0]     mem_size_e;
    logic           load_unsigned_e;
    logic           valid_e;

    logic [1:0]     fwd_rs1_sel_e;
    logic [1:0]     fwd_rs2_sel_e;
    logic [1:0]     fwd_branch_rs1_sel_e;
    logic [1:0]     fwd_branch_rs2_sel_e;
    logic [1:0]     fwd_target_base_sel_e;

    logic [`DATA_BUS] alu_res_x;
    logic [`DATA_BUS] store_data_x;
    logic           reg_write_x;
    logic           mem_read_x;
    logic           mem_write_x;
    logic           wb_sel_x;
    logic [3:0]     mem_size_x;
    logic           load_unsigned_x;
    logic [`RF_BUS] rd_addr_x;
    logic           redirect_valid_x;
    logic [`PC_BUS] redirect_pc_x;
    logic           train_valid_x;
    logic           train_taken_x;
    logic [`PC_BUS] train_pc_x;
    logic [`PC_BUS] train_target_x;

    logic [`DATA_BUS] alu_res_m1;
    logic [`DATA_BUS] store_data_m1;
    logic           reg_write_m1;
    logic           mem_read_m1;
    logic           mem_write_m1;
    logic           wb_sel_m1;
    logic [3:0]     mem_size_m1;
    logic           load_unsigned_m1;
    logic [`RF_BUS] rd_addr_m1;
    logic           train_valid_m1;
    logic           train_taken_m1;
    logic [`PC_BUS] train_pc_m1;
    logic [`PC_BUS] train_target_m1;
    logic           valid_m1;

    logic           dram_wen_m1;
    logic [`RAM_ADDR_BUS] dram_addr_m1;
    logic [`DATA_BUS] dram_wdata_m1;
    logic [3:0]     dram_mask_m1;

    logic [`DATA_BUS] alu_res_m2;
    logic           reg_write_m2;
    logic           wb_sel_m2;
    logic [3:0]     mem_size_m2;
    logic           load_unsigned_m2;
    logic [`RF_BUS] rd_addr_m2;
    logic           valid_m2;
    logic [`DATA_BUS] load_data_m2;

    logic [`DATA_BUS] alu_res_w;
    logic [`DATA_BUS] load_data_w;
    logic           reg_write_w;
    logic           wb_sel_w;
    logic [`RF_BUS] rd_addr_w;
    logic           valid_w;
    logic [`DATA_BUS] wb_data_w;

    logic load_use_stall;

    assign irom_addr = pc_cur_p;
    assign irom_ena  = !stall_pc_if;
    assign dram_wen   = dram_wen_m1;
    assign dram_addr  = dram_addr_m1;
    assign dram_wdata = dram_wdata_m1;
    assign dram_mask  = dram_mask_m1;
    assign update_en_e = train_valid_x && valid_e;
    assign error_e     = redirect_valid_x && valid_e;
    assign flush_e_m   = flush_ex_m1;
    assign jal_target_d    = pc_d + imm_d;
    assign redirect_valid_d = valid_d && is_jal_d &&
                              (!pred_taken_d || (pred_target_d != jal_target_d));
    assign redirect_pc_d    = jal_target_d;
    assign pred_taken_issue_d  = is_jal_d ? 1'b1 : pred_taken_d;
    assign pred_target_issue_d = is_jal_d ? jal_target_d : pred_target_d;
    assign redirect_valid_p = (redirect_valid_x && valid_e) || redirect_valid_d;
    assign redirect_pc_p    = (redirect_valid_x && valid_e) ? redirect_pc_x : redirect_pc_d;

    core_new_bpu_top u_bpu_top (
        .i_clk          (clk),
        .i_rst_n        (rst_n),
        .i_fetch_pc     (pc_cur_p),
        .i_train_valid  (train_valid_m1 && valid_m1),
        .i_train_pc     (train_pc_m1),
        .i_train_taken  (train_taken_m1),
        .i_train_target (train_target_m1),
        .o_pred_valid   (pred_valid_p),
        .o_pred_taken   (pred_taken_p),
        .o_pred_target  (pred_target_p)
    );

    core_new_redirect_ctrl u_redirect_ctrl (
        .i_redirect_valid   (redirect_valid_p),
        .i_redirect_pc      (redirect_pc_p),
        .i_if_redirect_valid(static_redirect_valid_f),
        .i_if_redirect_pc   (static_redirect_pc_f),
        .i_frontend_stall   (stall_pc_if),
        .i_pred_valid       (pred_valid_p),
        .i_pred_taken       (pred_taken_p),
        .i_pred_target      (pred_target_p),
        .i_pc_cur           (pc_cur_p),
        .o_next_pc          (pc_next_p),
        .o_fetch_pred_valid (fetch_pred_valid_p),
        .o_fetch_pred_taken (fetch_pred_taken_p),
        .o_fetch_pred_target(fetch_pred_target_p)
    );

    core_new_pipeline_ctrl u_pipeline_ctrl (
        .i_load_use_stall (load_use_stall),
        .i_redirect_valid_f(static_redirect_valid_f),
        .i_redirect_valid_d(redirect_valid_d),
        .i_redirect_valid_x(redirect_valid_x && valid_e),
        .o_stall_pc_if    (stall_pc_if),
        .o_stall_if_id    (stall_if_id),
        .o_flush_pc_if    (flush_pc_if),
        .o_flush_if_id    (flush_if_id),
        .o_flush_id_ex    (flush_id_ex),
        .o_flush_ex_m1    (flush_ex_m1)
    );

    core_new_pc_stage u_pc_stage (
        .i_clk     (clk),
        .i_rst_n   (rst_n),
        .i_stall   (stall_pc_if),
        .i_redirect(redirect_valid_p),
        .i_next_pc (pc_next_p),
        .o_pc      (pc_cur_p)
    );

    core_new_pipe_pc_if u_pipe_pc_if (
        .i_clk         (clk),
        .i_rst_n       (rst_n),
        .i_flush       (flush_pc_if),
        .i_stall       (stall_pc_if),
        .i_pc          (pc_cur_p),
        .i_pred_valid  (fetch_pred_valid_p),
        .i_pred_is_static(1'b0),
        .i_pred_taken  (fetch_pred_taken_p),
        .i_pred_target (fetch_pred_target_p),
        .i_valid       (1'b1),
        .o_pc          (pc_pf),
        .o_pred_valid  (pred_valid_pf),
        .o_pred_is_static(pred_is_static_pf),
        .o_pred_taken  (pred_taken_pf),
        .o_pred_target (pred_target_pf),
        .o_valid       (valid_pf)
    );

    core_new_fetch_stage u_fetch_stage (
        .i_pc          (pc_pf),
        .i_irom_data   (irom_data),
        .i_pred_valid  (pred_valid_pf),
        .i_pred_is_static(pred_is_static_pf),
        .i_pred_taken  (pred_taken_pf),
        .i_pred_target (pred_target_pf),
        .i_valid       (valid_pf),
        .o_static_redirect_valid(static_redirect_valid_f),
        .o_static_redirect_pc(static_redirect_pc_f),
        .o_pc          (pc_f),
        .o_inst        (inst_f),
        .o_pred_valid  (pred_valid_f),
        .o_pred_is_static(pred_is_static_f),
        .o_pred_taken  (pred_taken_f),
        .o_pred_target (pred_target_f),
        .o_valid       (valid_f)
    );

    core_new_pipe_if_id u_pipe_if_id (
        .i_clk         (clk),
        .i_rst_n       (rst_n),
        .i_flush       (flush_if_id),
        .i_stall       (stall_if_id),
        .i_pc          (pc_f),
        .i_inst        (inst_f),
        .i_pred_valid  (pred_valid_f),
        .i_pred_is_static(pred_is_static_f),
        .i_pred_taken  (pred_taken_f),
        .i_pred_target (pred_target_f),
        .i_valid       (valid_f),
        .o_pc          (pc_d),
        .o_inst        (inst_d),
        .o_pred_valid  (pred_valid_d),
        .o_pred_is_static(pred_is_static_d),
        .o_pred_taken  (pred_taken_d),
        .o_pred_target (pred_target_d),
        .o_valid       (valid_d)
    );

    core_new_decode_stage u_decode_stage (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_pc            (pc_d),
        .i_inst          (inst_d),
        .i_pred_taken    (pred_taken_issue_d),
        .i_pred_target   (pred_target_issue_d),
        .i_wb_we         (reg_write_w && valid_w),
        .i_wb_rd         (rd_addr_w),
        .i_wb_data       (wb_data_w),
        .o_mem_read      (mem_read_d),
        .o_mem_write     (mem_write_d),
        .o_reg_write     (reg_write_d),
        .o_wb_sel        (wb_sel_d),
        .o_alu_op        (alu_op_d),
        .o_branch_type   (branch_type_d),
        .o_is_branch     (is_branch_d),
        .o_is_jal        (is_jal_d),
        .o_is_jalr       (is_jalr_d),
        .o_is_lui        (is_lui_d),
        .o_is_auipc      (is_auipc_d),
        .o_src2_is_imm   (src2_is_imm_d),
        .o_use_rs1       (use_rs1_d),
        .o_use_rs2       (use_rs2_d),
        .o_mem_size      (mem_size_d),
        .o_load_unsigned (load_unsigned_d),
        .o_rs1_addr      (rs1_addr_d),
        .o_rs2_addr      (rs2_addr_d),
        .o_rd_addr       (rd_addr_d),
        .o_rs1_data      (rs1_data_d),
        .o_rs2_data      (rs2_data_d),
        .o_imm           (imm_d)
    );

    core_new_hazard_ctrl u_hazard_ctrl (
        .i_id_rs1       (rs1_addr_d),
        .i_id_rs2       (rs2_addr_d),
        .i_id_use_rs1   (use_rs1_d),
        .i_id_use_rs2   (use_rs2_d),
        .i_ex_rd        (rd_addr_e),
        .i_ex_mem_read  (mem_read_e && valid_e),
        .i_m1_rd        (rd_addr_m1),
        .i_m1_mem_read  (mem_read_m1 && valid_m1),
        .o_load_use_stall(load_use_stall)
    );

    core_new_pipe_id_ex u_pipe_id_ex (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_flush         (flush_id_ex),
        .i_stall         (1'b0),
        .i_pc            (pc_d),
        .i_pred_valid    (pred_valid_d),
        .i_pred_is_static(pred_is_static_d),
        .i_pred_taken    (pred_taken_issue_d),
        .i_pred_target   (pred_target_issue_d),
        .i_rs1_data      (rs1_data_d),
        .i_rs2_data      (rs2_data_d),
        .i_rs1_addr      (rs1_addr_d),
        .i_rs2_addr      (rs2_addr_d),
        .i_rd_addr       (rd_addr_d),
        .i_imm           (imm_d),
        .i_mem_read      (mem_read_d),
        .i_mem_write     (mem_write_d),
        .i_reg_write     (reg_write_d),
        .i_wb_sel        (wb_sel_d),
        .i_alu_op        (alu_op_d),
        .i_branch_type   (branch_type_d),
        .i_is_branch     (is_branch_d),
        .i_is_jal        (is_jal_d),
        .i_is_jalr       (is_jalr_d),
        .i_is_lui        (is_lui_d),
        .i_is_auipc      (is_auipc_d),
        .i_src2_is_imm   (src2_is_imm_d),
        .i_mem_size      (mem_size_d),
        .i_load_unsigned (load_unsigned_d),
        .i_valid         (valid_d),
        .o_pc            (pc_e),
        .o_pred_valid    (pred_valid_e),
        .o_pred_is_static(pred_is_static_e),
        .o_pred_taken    (pred_taken_e),
        .o_pred_target   (pred_target_e),
        .o_rs1_data      (rs1_data_e),
        .o_rs2_data      (rs2_data_e),
        .o_rs1_addr      (rs1_addr_e),
        .o_rs2_addr      (rs2_addr_e),
        .o_rd_addr       (rd_addr_e),
        .o_imm           (imm_e),
        .o_mem_read      (mem_read_e),
        .o_mem_write     (mem_write_e),
        .o_reg_write     (reg_write_e),
        .o_wb_sel        (wb_sel_e),
        .o_alu_op        (alu_op_e),
        .o_branch_type   (branch_type_e),
        .o_is_branch     (is_branch_e),
        .o_is_jal        (is_jal_e),
        .o_is_jalr       (is_jalr_e),
        .o_is_lui        (is_lui_e),
        .o_is_auipc      (is_auipc_e),
        .o_src2_is_imm   (src2_is_imm_e),
        .o_mem_size      (mem_size_e),
        .o_load_unsigned (load_unsigned_e),
        .o_valid         (valid_e)
    );

    core_new_forward_ctrl u_forward_ctrl (
        .i_idex_rs1           (rs1_addr_e),
        .i_idex_rs2           (rs2_addr_e),
        .i_exmem_rd           (rd_addr_m1),
        .i_m1m2_rd            (rd_addr_m2),
        .i_m2wb_rd            (rd_addr_w),
        .i_exmem_we           (reg_write_m1 && valid_m1),
        .i_m1m2_we            (reg_write_m2 && valid_m2),
        .i_m2wb_we            (reg_write_w && valid_w),
        .i_src2_is_imm        (src2_is_imm_e),
        .i_is_branch_like     (is_branch_e || is_jal_e || is_jalr_e),
        .i_is_jalr            (is_jalr_e),
        .o_fwd_rs1_sel        (fwd_rs1_sel_e),
        .o_fwd_rs2_sel        (fwd_rs2_sel_e),
        .o_fwd_branch_rs1_sel (fwd_branch_rs1_sel_e),
        .o_fwd_branch_rs2_sel (fwd_branch_rs2_sel_e),
        .o_fwd_target_base_sel(fwd_target_base_sel_e)
    );

    core_new_execute_stage u_execute_stage (
        .i_pc                  (pc_e),
        .i_rs1_data            (rs1_data_e),
        .i_rs2_data            (rs2_data_e),
        .i_imm                 (imm_e),
        .i_rd_addr             (rd_addr_e),
        .i_reg_write           (reg_write_e),
        .i_mem_read            (mem_read_e),
        .i_mem_write           (mem_write_e),
        .i_wb_sel              (wb_sel_e),
        .i_alu_op              (alu_op_e),
        .i_branch_type         (branch_type_e),
        .i_is_branch           (is_branch_e),
        .i_is_jal              (is_jal_e),
        .i_is_jalr             (is_jalr_e),
        .i_is_lui              (is_lui_e),
        .i_is_auipc            (is_auipc_e),
        .i_src2_is_imm         (src2_is_imm_e),
        .i_mem_size            (mem_size_e),
        .i_load_unsigned       (load_unsigned_e),
        .i_pred_taken          (pred_taken_e),
        .i_pred_target         (pred_target_e),
        .i_fwd_exmem_data      (alu_res_m1),
        .i_fwd_m1m2_data       (alu_res_m2),
        .i_fwd_m2wb_data       (wb_data_w),
        .i_fwd_rs1_sel         (fwd_rs1_sel_e),
        .i_fwd_rs2_sel         (fwd_rs2_sel_e),
        .i_fwd_branch_rs1_sel  (fwd_branch_rs1_sel_e),
        .i_fwd_branch_rs2_sel  (fwd_branch_rs2_sel_e),
        .i_fwd_target_base_sel (fwd_target_base_sel_e),
        .o_alu_res             (alu_res_x),
        .o_store_data          (store_data_x),
        .o_rd_addr             (rd_addr_x),
        .o_reg_write           (reg_write_x),
        .o_mem_read            (mem_read_x),
        .o_mem_write           (mem_write_x),
        .o_wb_sel              (wb_sel_x),
        .o_mem_size            (mem_size_x),
        .o_load_unsigned       (load_unsigned_x),
        .o_redirect_valid      (redirect_valid_x),
        .o_redirect_pc         (redirect_pc_x),
        .o_train_valid         (train_valid_x),
        .o_train_taken         (train_taken_x),
        .o_train_pc            (train_pc_x),
        .o_train_target        (train_target_x)
    );

    core_new_pipe_ex_m1 u_pipe_ex_m1 (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_flush         (flush_ex_m1),
        .i_stall         (1'b0),
        .i_alu_res       (alu_res_x),
        .i_store_data    (store_data_x),
        .i_rd_addr       (rd_addr_x),
        .i_reg_write     (reg_write_x),
        .i_mem_read      (mem_read_x),
        .i_mem_write     (mem_write_x),
        .i_wb_sel        (wb_sel_x),
        .i_mem_size      (mem_size_x),
        .i_load_unsigned (load_unsigned_x),
        .i_train_valid   (train_valid_x),
        .i_train_taken   (train_taken_x),
        .i_train_pc      (train_pc_x),
        .i_train_target  (train_target_x),
        .i_valid         (valid_e),
        .o_alu_res       (alu_res_m1),
        .o_store_data    (store_data_m1),
        .o_rd_addr       (rd_addr_m1),
        .o_reg_write     (reg_write_m1),
        .o_mem_read      (mem_read_m1),
        .o_mem_write     (mem_write_m1),
        .o_wb_sel        (wb_sel_m1),
        .o_mem_size      (mem_size_m1),
        .o_load_unsigned (load_unsigned_m1),
        .o_train_valid   (train_valid_m1),
        .o_train_taken   (train_taken_m1),
        .o_train_pc      (train_pc_m1),
        .o_train_target  (train_target_m1),
        .o_valid         (valid_m1)
    );

    core_new_mem1_stage u_mem1_stage (
        .i_alu_res    (alu_res_m1),
        .i_store_data (store_data_m1),
        .i_mem_write  (mem_write_m1 && valid_m1),
        .i_mem_size   (mem_size_m1),
        .o_dram_wen   (dram_wen_m1),
        .o_dram_addr  (dram_addr_m1),
        .o_dram_wdata (dram_wdata_m1),
        .o_dram_mask  (dram_mask_m1)
    );

    core_new_pipe_m1_m2 u_pipe_m1_m2 (
        .i_clk           (clk),
        .i_rst_n         (rst_n),
        .i_flush         (1'b0),
        .i_stall         (1'b0),
        .i_alu_res       (alu_res_m1),
        .i_rd_addr       (rd_addr_m1),
        .i_reg_write     (reg_write_m1),
        .i_wb_sel        (wb_sel_m1),
        .i_mem_size      (mem_size_m1),
        .i_load_unsigned (load_unsigned_m1),
        .i_valid         (valid_m1),
        .o_alu_res       (alu_res_m2),
        .o_rd_addr       (rd_addr_m2),
        .o_reg_write     (reg_write_m2),
        .o_wb_sel        (wb_sel_m2),
        .o_mem_size      (mem_size_m2),
        .o_load_unsigned (load_unsigned_m2),
        .o_valid         (valid_m2)
    );

    core_new_mem2_stage u_mem2_stage (
        .i_dram_rdata    (dram_rdata),
        .i_mem_size      (mem_size_m2),
        .i_load_unsigned (load_unsigned_m2),
        .o_load_data     (load_data_m2)
    );

    core_new_pipe_m2_wb u_pipe_m2_wb (
        .i_clk       (clk),
        .i_rst_n     (rst_n),
        .i_flush     (1'b0),
        .i_stall     (1'b0),
        .i_alu_res   (alu_res_m2),
        .i_load_data (load_data_m2),
        .i_rd_addr   (rd_addr_m2),
        .i_reg_write (reg_write_m2),
        .i_wb_sel    (wb_sel_m2),
        .i_valid     (valid_m2),
        .o_alu_res   (alu_res_w),
        .o_load_data (load_data_w),
        .o_rd_addr   (rd_addr_w),
        .o_reg_write (reg_write_w),
        .o_wb_sel    (wb_sel_w),
        .o_valid     (valid_w)
    );

    core_new_wb_stage u_wb_stage (
        .i_wb_sel    (wb_sel_w),
        .i_alu_res   (alu_res_w),
        .i_load_data (load_data_w),
        .o_wb_data   (wb_data_w)
    );
endmodule
