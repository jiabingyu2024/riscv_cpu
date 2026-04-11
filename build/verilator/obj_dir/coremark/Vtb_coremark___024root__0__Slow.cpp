// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_coremark.h for the primary calling header

#include "Vtb_coremark__pch.h"

void Vtb_coremark___024root___timing_ready(Vtb_coremark___024root* vlSelf);

VL_ATTR_COLD void Vtb_coremark___024root___eval_static(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___eval_static\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000020ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_coremark__DOT__w_cpu_clk__0 
        = vlSelfRef.tb_coremark__DOT__w_cpu_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_coremark__DOT__w_clk_rst__0 
        = vlSelfRef.tb_coremark__DOT__w_clk_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_coremark__DOT__w_clk_50mhz__0 
        = vlSelfRef.tb_coremark__DOT__w_clk_50mhz;
    vlSelfRef.__Vtrigprevexpr_he91805aa__1 = ((0U != (IData)(vlSelfRef.tb_coremark__DOT__result)) 
                                              | (0x00000004a817c800ULL 
                                                 <= vlSelfRef.tb_coremark__DOT__cycles));
    Vtb_coremark___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_coremark___024root___eval_initial__TOP(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___eval_initial__TOP\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_READMEM_N(true, 32, 4096, 0, "rtl/ip/irom.mem"s
                 ,  &(vlSelfRef.tb_coremark__DOT__dut__DOT__Mem_IROM__DOT__mem)
                 , 0, ~0ULL);
    VL_READMEM_N(true, 32, 65536, 0, "rtl/ip/dram.mem"s
                 ,  &(vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void Vtb_coremark___024root___eval_final(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___eval_final\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_coremark___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_coremark___024root___eval_phase__stl(Vtb_coremark___024root* vlSelf);

VL_ATTR_COLD void Vtb_coremark___024root___eval_settle(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___eval_settle\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_coremark___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_coremark.sv", 33, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_coremark___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_coremark___024root___eval_triggers_vec__stl(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___eval_triggers_vec__stl\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_coremark___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_coremark___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_coremark___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_coremark___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

VL_ATTR_COLD void Vtb_coremark___024root___stl_sequent__TOP__0(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___stl_sequent__TOP__0\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 0;
    CData/*1:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 0;
    CData/*1:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0;
    CData/*1:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 0;
    CData/*1:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 0;
    IData/*31:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e = 0;
    CData/*0:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m = 0;
    CData/*0:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w = 0;
    CData/*0:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m = 0;
    CData/*0:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w = 0;
    CData/*0:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0 = 0;
    CData/*0:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1 = 0;
    IData/*31:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data = 0;
    IData/*31:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data = 0;
    IData/*31:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data = 0;
    IData/*31:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data = 0;
    CData/*0:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 0;
    IData/*31:0*/ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target = 0;
    IData/*31:0*/ tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw;
    tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_0;
    __VdfgRegularize_h6e95ff9d_0_0 = 0;
    // Body
    if ((1U & (~ VL_ONEHOT_I((((8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                               << 2U) | (((4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                                          << 1U) | 
                                         (1U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)))))))) {
        if ((0U != (((8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                     << 2U) | (((4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                                << 1U) | (1U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: forward_unit.sv:72: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_forward_unit: unique case, but multiple matches found for '4'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),4,(IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/control/forward_unit.sv", 72, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I(((((8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                                | (4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) 
                               << 1U) | (2U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))))))) {
        if ((0U != ((((8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                      | (4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) 
                     << 1U) | (2U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:120: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '4'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),4,(IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 120, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m)) 
                               << 1U) | (0U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))))))) {
        if ((0U != (((1U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m)) 
                     << 1U) | (0U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_mem.sv:42: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_mem: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/mem/stage_mem.sv", 42, "");
            }
        }
    }
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_d 
        = (((- (IData)(((0x13U == (0x0000007fU & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                        | ((3U == (0x0000007fU & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                           | (0x67U == (0x0000007fU 
                                        & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))))) 
            & (((- (IData)((vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                            >> 0x0000001fU))) << 0x0000000cU) 
               | (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                  >> 0x00000014U))) | (((- (IData)(
                                                   (0x23U 
                                                    == 
                                                    (0x0000007fU 
                                                     & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))) 
                                        & (((- (IData)(
                                                       (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x0000001fU))) 
                                            << 0x0000000cU) 
                                           | ((0x00000fe0U 
                                               & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                  >> 0x00000014U)) 
                                              | (0x0000001fU 
                                                 & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                    >> 7U))))) 
                                       | (((- (IData)(
                                                      (0x63U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))) 
                                           & (((- (IData)(
                                                          (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                           >> 0x0000001fU))) 
                                               << 0x0000000dU) 
                                              | ((((2U 
                                                    & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                       >> 0x0000001eU)) 
                                                   | (1U 
                                                      & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                         >> 7U))) 
                                                  << 0x0000000bU) 
                                                 | ((0x000007e0U 
                                                     & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x00000014U)) 
                                                    | (0x0000001eU 
                                                       & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                          >> 7U)))))) 
                                          | ((0xfffff000U 
                                              & ((- (IData)(
                                                            ((0x37U 
                                                              == 
                                                              (0x0000007fU 
                                                               & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                                                             | (0x17U 
                                                                == 
                                                                (0x0000007fU 
                                                                 & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d))))) 
                                                 & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                                             | ((- (IData)(
                                                           (0x6fU 
                                                            == 
                                                            (0x0000007fU 
                                                             & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))) 
                                                & ((((0x00000ffeU 
                                                      & ((- (IData)(
                                                                    (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                                     >> 0x0000001fU))) 
                                                         << 1U)) 
                                                     | (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x0000001fU)) 
                                                    << 0x00000014U) 
                                                   | ((((0x000001feU 
                                                         & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                            >> 0x0000000bU)) 
                                                        | (1U 
                                                           & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                              >> 0x00000014U))) 
                                                       << 0x0000000bU) 
                                                      | (0x000007feU 
                                                         & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                            >> 0x00000014U)))))))));
    vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m) 
           & (0x80200050U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m));
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f 
        = (((vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem
             [(0x0000000fU & (vlSelfRef.tb_coremark__DOT__dut__DOT__pc 
                              >> 2U))] & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem
                                          [(0x0000000fU 
                                            & (vlSelfRef.tb_coremark__DOT__dut__DOT__pc 
                                               >> 2U))] 
                                          == (vlSelfRef.tb_coremark__DOT__dut__DOT__pc 
                                              >> 6U))) 
            & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem
               [(0x0000000fU & (vlSelfRef.tb_coremark__DOT__dut__DOT__pc 
                                >> 2U))] >> 1U)) ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem
           [(0x0000000fU & (vlSelfRef.tb_coremark__DOT__dut__DOT__pc 
                            >> 2U))] : ((IData)(4U) 
                                        + vlSelfRef.tb_coremark__DOT__dut__DOT__pc));
    vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0 
        = ((0x80100000U <= vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m) 
           & (0x8013ffffU > vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m));
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_e) 
           & ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e) 
              & ((0U != (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e)) 
                 & (((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e) 
                     == (0x0000001fU & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                        >> 0x0000000fU))) 
                    | ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e) 
                       == (0x0000001fU & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                          >> 0x00000014U)))))));
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d = 2U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d = 0U;
    if ((0x00000040U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
        if ((0x00000020U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
            if ((1U & (~ (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                          >> 4U)))) {
                if ((8U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((4U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                            if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                                vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                                vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 4U;
                            }
                        }
                    }
                } else if ((4U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                            vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                            vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                            vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 8U;
                            vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                        }
                    }
                } else if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d = 1U;
                    }
                }
            }
        }
    } else if ((0x00000020U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
        if ((0x00000010U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
            if ((1U & (~ (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                          >> 3U)))) {
                if ((4U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                            vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                            vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                            vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 2U;
                        }
                    }
                } else if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d 
                            = ((0x00004000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                ? ((0x00002000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                    ? ((0x00001000U 
                                        & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                        ? 0U : 1U) : 
                                   ((0x00001000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                     ? ((0x20U == (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                   >> 0x00000019U))
                                         ? 7U : 6U)
                                     : 2U)) : ((0x00002000U 
                                                & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                ? (
                                                   (0x00001000U 
                                                    & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                    ? 9U
                                                    : 8U)
                                                : (
                                                   (0x00001000U 
                                                    & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                    ? 5U
                                                    : 
                                                   ((0x20U 
                                                     == 
                                                     (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                      >> 0x00000019U))
                                                     ? 4U
                                                     : 3U))));
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                          >> 2U)))) {
                if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d = 1U;
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d 
                            = ((0U == (7U & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                             >> 0x0000000cU)))
                                ? 0U : ((1U == (7U 
                                                & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                   >> 0x0000000cU)))
                                         ? 1U : 2U));
                        if ((1U & (~ VL_ONEHOT_I(((
                                                   (1U 
                                                    == 
                                                    (7U 
                                                     & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x0000000cU))) 
                                                   << 1U) 
                                                  | (0U 
                                                     == 
                                                     (7U 
                                                      & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                         >> 0x0000000cU)))))))) {
                            if ((0U != (((1U == (7U 
                                                 & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                    >> 0x0000000cU))) 
                                         << 1U) | (0U 
                                                   == 
                                                   (7U 
                                                    & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                       >> 0x0000000cU)))))) {
                                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                                    VL_WRITEF_NX("[%0t] %%Error: control_unit.sv:106: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_id.u_control_unit: unique case, but multiple matches found for '3'h%x'\n",0,
                                                 64,
                                                 VL_TIME_UNITED_Q(1000),
                                                 -9,
                                                 vlSymsp->name(),
                                                 3,
                                                 (7U 
                                                  & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                     >> 0x0000000cU)));
                                    VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/id/control_unit.sv", 106, "");
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if ((0x00000010U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
        if ((1U & (~ (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                      >> 3U)))) {
            if ((4U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 1U;
                        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                    }
                }
            } else if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d 
                        = ((0x00004000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                            ? ((0x00002000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                ? ((0x00001000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                    ? 0U : 1U) : ((0x00001000U 
                                                   & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                   ? 
                                                  ((0x40000000U 
                                                    & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                    ? 7U
                                                    : 6U)
                                                   : 2U))
                            : ((0x00002000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                ? ((0x00001000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                    ? 9U : 8U) : ((0x00001000U 
                                                   & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                   ? 5U
                                                   : 3U)));
                }
            }
        }
    } else if ((1U & (~ (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                         >> 3U)))) {
        if ((1U & (~ (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                      >> 2U)))) {
            if ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                if ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d = 1U;
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d = 1U;
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d 
                        = (1U & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                 >> 0x0000000eU));
                    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d 
                        = ((0x00002000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                            ? 2U : ((0x00001000U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                     ? 1U : 0U));
                }
            }
        }
    }
    tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
        = vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem
        [(0x0000ffffU & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m 
                         >> 2U))];
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_w)
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w
            : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w);
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m) 
           & (0U != (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m)));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w) 
           & (0U != (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w)));
    vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_data 
        = ((2U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m
            : ((1U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                ? ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? ((vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                        << 0x00000010U) | (0x0000ffffU 
                                           & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))
                    : ((0xffff0000U & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                       | (0x0000ffffU & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)))
                : ((0U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                    ? ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                        ? ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                            ? ((vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                << 0x00000018U) | (0x00ffffffU 
                                                   & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))
                            : ((0xff000000U & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                               | ((0x00ff0000U & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                                  << 0x00000010U)) 
                                  | (0x0000ffffU & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))))
                        : ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                            ? ((0xffff0000U & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                               | ((0x0000ff00U & (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                                  << 8U)) 
                                  | (0x000000ffU & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))
                            : ((0xffffff00U & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                               | (0x000000ffU & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m))))
                    : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)));
    vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout = 0U;
    vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout 
        = ((0U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
            ? ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                ? ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? (tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                       >> 0x18U) : (0x000000ffU & (tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                                   >> 0x10U)))
                : ((1U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? (0x000000ffU & (tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                      >> 8U)) : (0x000000ffU 
                                                 & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))
            : ((1U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                ? ((2U & vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? (IData)((QData)((IData)((tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                               >> 0x10U))))
                    : (IData)((QData)((IData)((0x0000ffffU 
                                               & tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))))
                : ((2U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                    ? tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw
                    : 0U)));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m 
        = ((IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0) 
           & ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m) 
              == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e)));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m 
        = ((IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0) 
           & ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m) 
              == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e)));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w 
        = ((IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1) 
           & ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w) 
              == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e)));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w 
        = ((IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1) 
           & ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w) 
              == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e)));
    vlSelfRef.tb_coremark__DOT__dut__DOT__perip_rdata 
        = ((((- (IData)((0x80200000U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
             | ((- (IData)((0x80200004U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                | ((- (IData)((0x80200010U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                   | ((- (IData)((0x80200020U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                      | ((- (IData)((0x80200064U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                         | ((- (IData)((0x80200070U 
                                        == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                            | (- (IData)((0x80200074U 
                                          == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))))))))) 
            & ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m)
                ? 0U : ((0x80200000U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                         ? (IData)(vlSelfRef.tb_coremark__DOT__virtual_sw)
                         : ((0x80200004U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                             ? (IData)((vlSelfRef.tb_coremark__DOT__virtual_sw 
                                        >> 0x00000020U))
                             : ((0x80200010U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                 ? (IData)(vlSelfRef.tb_coremark__DOT__virtual_key)
                                 : ((0x80200020U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                     ? vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__seg_wdata
                                     : ((0x80200064U 
                                         == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                         ? 1U : ((0x80200070U 
                                                  == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                                  ? vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__sim_done_code
                                                  : 
                                                 ((0x80200074U 
                                                   == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                                   ? vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__sim_info_code
                                                   : 0xdeadbeefU))))))))) 
           | (((- (IData)((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0))) 
               & vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout) 
              | ((- (IData)((0x80200050U == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                 & vlSelfRef.tb_coremark__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms)));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e)
            ? 3U : 0U);
    if (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m) {
        if ((1U & (~ (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e)))) {
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 1U;
        }
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 0U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 1U;
    } else {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 0U;
        if (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w) {
            if ((1U & (~ (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e)))) {
                tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 2U;
            }
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 2U;
        }
    }
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 0U;
    if (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m) {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 1U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 0U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 1U;
    } else {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 0U;
        if (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w) {
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 2U;
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 2U;
        }
    }
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0U;
    if ((1U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 3U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 3U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0U;
    } else if ((4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 3U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 3U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0U;
    } else if ((8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 3U;
        if (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m) {
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 1U;
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 2U;
        } else if (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w) {
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 2U;
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 3U;
        } else {
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 0U;
            tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 1U;
        }
    }
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data 
        = ((1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e))
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e))
                ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : ((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e))
                    ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e
                    : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e)));
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data 
        = ((1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))
                ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
        = ((1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e))
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e))
                ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : ((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e))
                    ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e
                    : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e)));
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
        = ((1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))
                ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e));
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e)) 
                               << 1U) | (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))))))) {
        if ((0U != (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e)) 
                     << 1U) | (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:58: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 58, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e)) 
                               << 1U) | (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))))))) {
        if ((0U != (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e)) 
                     << 1U) | (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:64: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 64, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                               << 2U) | (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                                          << 1U) | 
                                         (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)))))))) {
        if ((0U != (((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                     << 2U) | (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                                << 1U) | (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:70: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 70, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                               << 2U) | (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                                          << 1U) | 
                                         (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)))))))) {
        if ((0U != (((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                     << 2U) | (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                                << 1U) | (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:77: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 77, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                               << 2U) | (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                                          << 1U) | 
                                         (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)))))))) {
        if ((0U != (((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                     << 2U) | (((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                                << 1U) | (1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:84: Assertion failed in %Ntb_coremark.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 84, "");
            }
        }
    }
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data 
        = ((1U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e))
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e
            : ((2U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e))
                ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
                : ((3U == (IData)(tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e))
                    ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                    : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e)));
    __VdfgRegularize_h6e95ff9d_0_0 = (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                      == tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data);
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 0U;
    tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target 
        = (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data 
           + vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e);
    if (vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e) {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken 
            = ((4U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                ? ((2U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                    ? ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                        ? (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                           >= vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)
                        : (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                           < vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data))
                    : ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                        ? VL_GTES_III(32, tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data, vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)
                        : VL_LTS_III(32, tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data, vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)))
                : ((1U & (~ ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e) 
                             >> 1U))) && ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                                           ? (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                                              != vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)
                                           : (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                                              == vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data))));
    } else if ((4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 1U;
    } else if ((8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 1U;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target 
            = (0xfffffffeU & (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data 
                              + vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e));
    }
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e 
        = (((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e) 
            | (4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) 
           | (8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)));
    if (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken) {
        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e = 1U;
        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e 
            = tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target;
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e 
            = tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target;
    } else {
        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e = 0U;
        vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e 
            = ((IData)(4U) + vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e);
        tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e 
            = ((IData)(4U) + vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e);
    }
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e) 
           & (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e 
              != vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e));
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_e 
        = ((2U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))
            ? vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e
            : (((4U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                | (8U == (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)))
                ? ((IData)(4U) + vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e)
                : ((8U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                    ? ((4U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                        ? ((2U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? 0U : ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                     ? ((tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                         >= tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                         ? 1U : 0U)
                                     : (VL_GTES_III(32, tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data, tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                         ? 1U : 0U)))
                        : ((2U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? ((IData)(__VdfgRegularize_h6e95ff9d_0_0)
                                    ? 0U : 1U) : ((IData)(__VdfgRegularize_h6e95ff9d_0_0)
                                                   ? 1U
                                                   : 0U))
                            : ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? ((tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                    < tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                    ? 1U : 0U) : (VL_LTS_III(32, tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data, tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                                   ? 1U
                                                   : 0U))))
                    : ((4U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                        ? ((2U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? VL_SHIFTRS_III(32,32,5, tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data, 
                                                 (0x0000001fU 
                                                  & tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data))
                                : (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   >> (0x0000001fU 
                                       & tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)))
                            : ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   << (0x0000001fU 
                                       & tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data))
                                : (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   - tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)))
                        : ((2U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   + tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                : (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   ^ tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data))
                            : ((1U & (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   | tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                : (tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   & tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)))))));
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e) 
           | (IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d));
    vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_next_hz 
        = ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e)
            ? tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e
            : ((IData)(vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d)
                ? vlSelfRef.tb_coremark__DOT__dut__DOT__pc
                : vlSelfRef.tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f));
}

VL_ATTR_COLD void Vtb_coremark___024root___eval_stl(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___eval_stl\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_coremark___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_coremark___024root___eval_phase__stl(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___eval_phase__stl\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_coremark___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_coremark___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_coremark___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_coremark___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_coremark___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_coremark___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_coremark___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_coremark.w_cpu_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge tb_coremark.w_clk_rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(negedge tb_coremark.w_cpu_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @(posedge tb_coremark.w_clk_50mhz)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @( ((2'h0 != tb_coremark.result) | (64'h4a817c800 <= tb_coremark.cycles)))\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_coremark___024root___ctor_var_reset(Vtb_coremark___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_coremark___024root___ctor_var_reset\n"); );
    Vtb_coremark__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_coremark__DOT__w_cpu_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5878929024602402312ull);
    vlSelf->tb_coremark__DOT__w_clk_50mhz = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17359728234717020605ull);
    vlSelf->tb_coremark__DOT__w_clk_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1525570897213680721ull);
    vlSelf->tb_coremark__DOT__virtual_key = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7640838953993157311ull);
    vlSelf->tb_coremark__DOT__virtual_sw = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9288249623779680826ull);
    vlSelf->tb_coremark__DOT__result = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11093237688321843730ull);
    vlSelf->tb_coremark__DOT__cycles = 0;
    vlSelf->tb_coremark__DOT__last_info = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9794060971666205484ull);
    vlSelf->tb_coremark__DOT__heartbeat_period = 0;
    vlSelf->tb_coremark__DOT__dut__DOT__pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14786822322906732693ull);
    vlSelf->tb_coremark__DOT__dut__DOT__perip_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15316995388938052750ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_next_hz = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11418734282763565409ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4990200970108216774ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7698465224513515601ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8938446902552953420ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5474987815278546036ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10012357806384183749ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13817234864824059345ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 956466945611760664ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5384807710727212574ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11188969603090281566ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3251453819155518084ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2662165492150946305ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2194654474759209794ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4076299865096461113ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1639687274187381725ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11670076632375305228ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2412896054450643980ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1037568621619215987ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16964180553128453841ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9791187158970109374ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8741476611769721643ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17450850952027549748ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4123635121086145856ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7189855044538554559ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18354325004915564034ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12408094079020548006ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11566237345935986543ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10500028891092670958ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2027174048737414961ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11259761292749296838ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_e = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14752675863170855876ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7879024037055721991ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13391626978976967913ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5800077738806075730ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6052665188139235044ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 828156171125257681ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13148528375286382418ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11847574806255421186ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3423564403602362677ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4772854411578275042ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12842865672525195136ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12812235701528533051ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8429853488692495102ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7017767295075697652ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2515907766633356957ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1661996506695962754ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2036541275723414783ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5557957992239220827ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16701056178677840878ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4680408381273333132ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 622665026968121191ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3157038871002917049ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4078210872860683256ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2002733762920655805ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11217362034101203974ull);
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5143111068606544843ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(26, __VscopeHash, 1932222605304965935ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12878860552450761512ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11927318747870586008ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2342083291570634226ull);
    }
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13361455877150825831ull);
    }
    vlSelf->tb_coremark__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4182275302884753369ull);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->tb_coremark__DOT__dut__DOT__Mem_IROM__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3780529117830065109ull);
    }
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__seg_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16822949672932709985ull);
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__sim_done_code = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7372852197175816108ull);
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__sim_info_code = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1150081428971132311ull);
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen = 0;
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0 = 0;
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10509923688759146193ull);
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9469536209843833972ull);
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16617093794947198937ull);
    }
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5173817398279323269ull);
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17585772252311187886ull);
    vlSelf->tb_coremark__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5926092453213418164ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_coremark__DOT__w_cpu_clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_coremark__DOT__w_clk_rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_coremark__DOT__w_clk_50mhz__0 = 0;
    vlSelf->__Vtrigprevexpr_he91805aa__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
