// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_func.h for the primary calling header

#ifndef VERILATED_VTB_FUNC___024ROOT_H_
#define VERILATED_VTB_FUNC___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_func__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_func___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ tb_func__DOT__w_cpu_clk;
        CData/*0:0*/ tb_func__DOT__w_clk_50mhz;
        CData/*0:0*/ tb_func__DOT__w_clk_rst;
        CData/*7:0*/ tb_func__DOT__virtual_key;
        CData/*1:0*/ tb_func__DOT__result;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d;
        CData/*3:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d;
        CData/*3:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d;
        CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d;
        CData/*4:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e;
        CData/*4:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e;
        CData/*4:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e;
        CData/*3:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e;
        CData/*3:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e;
        CData/*2:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e;
        CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e;
        CData/*4:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_m;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m;
        CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_m;
        CData/*4:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_w;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d;
        CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e;
        CData/*0:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen;
        CData/*0:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0;
        CData/*0:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_func__DOT__w_clk_rst__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_func__DOT__w_clk_50mhz__0;
        CData/*0:0*/ __Vtrigprevexpr_h298d6784__1;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VinactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        SData/*15:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
        IData/*31:0*/ tb_func__DOT__last_info;
        IData/*31:0*/ tb_func__DOT__last_addr;
        IData/*31:0*/ tb_func__DOT__last_wdata;
        IData/*31:0*/ tb_func__DOT__dut__DOT__pc;
        IData/*31:0*/ tb_func__DOT__dut__DOT__perip_rdata;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_next_hz;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_d;
    };
    struct {
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_d;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_d;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_e;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w;
        IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data;
        IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__seg_wdata;
        IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_done_code;
        IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_info_code;
        IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_data;
        IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout;
        IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
        IData/*31:0*/ __VactIterCount;
        IData/*31:0*/ __VinactIterCount;
        IData/*31:0*/ __Vi;
        QData/*63:0*/ tb_func__DOT__virtual_sw;
        QData/*63:0*/ tb_func__DOT__cycles;
        VlUnpacked<IData/*25:0*/, 16> tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem;
        VlUnpacked<IData/*31:0*/, 16> tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem;
        VlUnpacked<CData/*1:0*/, 16> tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem;
        VlUnpacked<CData/*0:0*/, 16> tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem;
        VlUnpacked<IData/*31:0*/, 32> tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem;
        VlUnpacked<IData/*31:0*/, 4096> tb_func__DOT__dut__DOT__Mem_IROM__DOT__mem;
        VlUnpacked<IData/*31:0*/, 65536> tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    std::string tb_func__DOT__irom_file;
    std::string tb_func__DOT__dram_file;
    std::string tb_func__DOT__dump_file;
    std::string __Vfunc_tb_result_to_string__0__Vfuncout;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_ha22db48e__0;
    VlTriggerScheduler __VtrigSched_h7d3a5011__0;

    // INTERNAL VARIABLES
    Vtb_func__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_func___024root(Vtb_func__Syms* symsp, const char* namep);
    ~Vtb_func___024root();
    VL_UNCOPYABLE(Vtb_func___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
