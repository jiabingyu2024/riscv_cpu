// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_func.h for the primary calling header

#include "Vtb_func__pch.h"

void Vtb_func___024root___timing_ready(Vtb_func___024root* vlSelf);

VL_ATTR_COLD void Vtb_func___024root___eval_static(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_static\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000020ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0 
        = vlSelfRef.tb_func__DOT__w_cpu_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_rst__0 
        = vlSelfRef.tb_func__DOT__w_clk_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_50mhz__0 
        = vlSelfRef.tb_func__DOT__w_clk_50mhz;
    vlSelfRef.__Vtrigprevexpr_h298d6784__1 = ((0U != (IData)(vlSelfRef.tb_func__DOT__result)) 
                                              | (0x000000001dcd6500ULL 
                                                 <= vlSelfRef.tb_func__DOT__cycles));
    Vtb_func___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_func___024root___eval_initial__TOP(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_initial__TOP\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_READMEM_N(true, 32, 4096, 0, "rtl/ip/irom.mem"s
                 ,  &(vlSelfRef.tb_func__DOT__dut__DOT__Mem_IROM__DOT__mem)
                 , 0, ~0ULL);
    VL_READMEM_N(true, 32, 65536, 0, "rtl/ip/dram.mem"s
                 ,  &(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void Vtb_func___024root___eval_final(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_final\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_func___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_func___024root___eval_phase__stl(Vtb_func___024root* vlSelf);

VL_ATTR_COLD void Vtb_func___024root___eval_settle(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_settle\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_func___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 33, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_func___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_func___024root___eval_triggers_vec__stl(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_triggers_vec__stl\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_func___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_func___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_func___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_func___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_func___024root___stl_sequent__TOP__0(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___stl_sequent__TOP__0\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 0;
    CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 0;
    CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0;
    CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 0;
    CData/*1:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 0;
    IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e = 0;
    CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m = 0;
    CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w = 0;
    CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m = 0;
    CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w = 0;
    CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0 = 0;
    CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1 = 0;
    IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data = 0;
    IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data = 0;
    IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data = 0;
    IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data = 0;
    CData/*0:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 0;
    IData/*31:0*/ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target = 0;
    IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw;
    tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_0;
    __VdfgRegularize_h6e95ff9d_0_0 = 0;
    // Body
    if ((1U & (~ VL_ONEHOT_I((((8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                               << 2U) | (((4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                                          << 1U) | 
                                         (1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)))))))) {
        if ((0U != (((8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                     << 2U) | (((4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                                << 1U) | (1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: forward_unit.sv:72: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_forward_unit: unique case, but multiple matches found for '4'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),4,(IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/control/forward_unit.sv", 72, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I(((((8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                                | (4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) 
                               << 1U) | (2U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))))))) {
        if ((0U != ((((8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                      | (4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) 
                     << 1U) | (2U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:120: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '4'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),4,(IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 120, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m)) 
                               << 1U) | (0U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))))))) {
        if ((0U != (((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m)) 
                     << 1U) | (0U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_mem.sv:42: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_mem: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/mem/stage_mem.sv", 42, "");
            }
        }
    }
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_d 
        = (((- (IData)(((0x13U == (0x0000007fU & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                        | ((3U == (0x0000007fU & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                           | (0x67U == (0x0000007fU 
                                        & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))))) 
            & (((- (IData)((vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                            >> 0x0000001fU))) << 0x0000000cU) 
               | (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                  >> 0x00000014U))) | (((- (IData)(
                                                   (0x23U 
                                                    == 
                                                    (0x0000007fU 
                                                     & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))) 
                                        & (((- (IData)(
                                                       (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x0000001fU))) 
                                            << 0x0000000cU) 
                                           | ((0x00000fe0U 
                                               & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                  >> 0x00000014U)) 
                                              | (0x0000001fU 
                                                 & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                    >> 7U))))) 
                                       | (((- (IData)(
                                                      (0x63U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))) 
                                           & (((- (IData)(
                                                          (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                           >> 0x0000001fU))) 
                                               << 0x0000000dU) 
                                              | ((((2U 
                                                    & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                       >> 0x0000001eU)) 
                                                   | (1U 
                                                      & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                         >> 7U))) 
                                                  << 0x0000000bU) 
                                                 | ((0x000007e0U 
                                                     & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x00000014U)) 
                                                    | (0x0000001eU 
                                                       & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                          >> 7U)))))) 
                                          | ((0xfffff000U 
                                              & ((- (IData)(
                                                            ((0x37U 
                                                              == 
                                                              (0x0000007fU 
                                                               & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                                                             | (0x17U 
                                                                == 
                                                                (0x0000007fU 
                                                                 & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d))))) 
                                                 & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) 
                                             | ((- (IData)(
                                                           (0x6fU 
                                                            == 
                                                            (0x0000007fU 
                                                             & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)))) 
                                                & ((((0x00000ffeU 
                                                      & ((- (IData)(
                                                                    (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                                     >> 0x0000001fU))) 
                                                         << 1U)) 
                                                     | (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x0000001fU)) 
                                                    << 0x00000014U) 
                                                   | ((((0x000001feU 
                                                         & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                            >> 0x0000000bU)) 
                                                        | (1U 
                                                           & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                              >> 0x00000014U))) 
                                                       << 0x0000000bU) 
                                                      | (0x000007feU 
                                                         & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                            >> 0x00000014U)))))))));
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m) 
           & (0x80200050U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f 
        = (((vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem
             [(0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__pc 
                              >> 2U))] & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem
                                          [(0x0000000fU 
                                            & (vlSelfRef.tb_func__DOT__dut__DOT__pc 
                                               >> 2U))] 
                                          == (vlSelfRef.tb_func__DOT__dut__DOT__pc 
                                              >> 6U))) 
            & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem
               [(0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__pc 
                                >> 2U))] >> 1U)) ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem
           [(0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__pc 
                            >> 2U))] : ((IData)(4U) 
                                        + vlSelfRef.tb_func__DOT__dut__DOT__pc));
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0 
        = ((0x80100000U <= vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m) 
           & (0x8013ffffU > vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_e) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e) 
              & ((0U != (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e)) 
                 & (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e) 
                     == (0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                        >> 0x0000000fU))) 
                    | ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e) 
                       == (0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                          >> 0x00000014U)))))));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d = 2U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d = 0U;
    if ((0x00000040U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
        if ((0x00000020U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
            if ((1U & (~ (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                          >> 4U)))) {
                if ((8U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((4U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                            if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                                vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                                vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 4U;
                            }
                        }
                    }
                } else if ((4U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 8U;
                            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                        }
                    }
                } else if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d = 1U;
                    }
                }
            }
        }
    } else if ((0x00000020U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
        if ((0x00000010U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
            if ((1U & (~ (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                          >> 3U)))) {
                if ((4U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 2U;
                        }
                    }
                } else if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d 
                            = ((0x00004000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                ? ((0x00002000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                    ? ((0x00001000U 
                                        & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                        ? 0U : 1U) : 
                                   ((0x00001000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                     ? ((0x20U == (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                   >> 0x00000019U))
                                         ? 7U : 6U)
                                     : 2U)) : ((0x00002000U 
                                                & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                ? (
                                                   (0x00001000U 
                                                    & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                    ? 9U
                                                    : 8U)
                                                : (
                                                   (0x00001000U 
                                                    & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                    ? 5U
                                                    : 
                                                   ((0x20U 
                                                     == 
                                                     (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                      >> 0x00000019U))
                                                     ? 4U
                                                     : 3U))));
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                          >> 2U)))) {
                if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d = 1U;
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d 
                            = ((0U == (7U & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                             >> 0x0000000cU)))
                                ? 0U : ((1U == (7U 
                                                & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                   >> 0x0000000cU)))
                                         ? 1U : 2U));
                        if ((1U & (~ VL_ONEHOT_I(((
                                                   (1U 
                                                    == 
                                                    (7U 
                                                     & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                        >> 0x0000000cU))) 
                                                   << 1U) 
                                                  | (0U 
                                                     == 
                                                     (7U 
                                                      & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                         >> 0x0000000cU)))))))) {
                            if ((0U != (((1U == (7U 
                                                 & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                    >> 0x0000000cU))) 
                                         << 1U) | (0U 
                                                   == 
                                                   (7U 
                                                    & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                       >> 0x0000000cU)))))) {
                                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                                    VL_WRITEF_NX("[%0t] %%Error: control_unit.sv:106: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_id.u_control_unit: unique case, but multiple matches found for '3'h%x'\n",0,
                                                 64,
                                                 VL_TIME_UNITED_Q(1000),
                                                 -9,
                                                 vlSymsp->name(),
                                                 3,
                                                 (7U 
                                                  & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                                     >> 0x0000000cU)));
                                    VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/id/control_unit.sv", 106, "");
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if ((0x00000010U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
        if ((1U & (~ (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                      >> 3U)))) {
            if ((4U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = 1U;
                        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                    }
                }
            } else if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d 
                        = ((0x00004000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                            ? ((0x00002000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                ? ((0x00001000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                    ? 0U : 1U) : ((0x00001000U 
                                                   & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                   ? 
                                                  ((0x40000000U 
                                                    & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                    ? 7U
                                                    : 6U)
                                                   : 2U))
                            : ((0x00002000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                ? ((0x00001000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                    ? 9U : 8U) : ((0x00001000U 
                                                   & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                                   ? 5U
                                                   : 3U)));
                }
            }
        }
    } else if ((1U & (~ (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                         >> 3U)))) {
        if ((1U & (~ (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                      >> 2U)))) {
            if ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                if ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)) {
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d = 1U;
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = 1U;
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d = 1U;
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = 1U;
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = 3U;
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d 
                        = (1U & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                 >> 0x0000000eU));
                    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d 
                        = ((0x00002000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                            ? 2U : ((0x00001000U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d)
                                     ? 1U : 0U));
                }
            }
        }
    }
    tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
        = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem
        [(0x0000ffffU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m 
                         >> 2U))];
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_w)
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w
            : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w);
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m) 
           & (0U != (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w) 
           & (0U != (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w)));
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_data 
        = ((2U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m
            : ((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? ((vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                        << 0x00000010U) | (0x0000ffffU 
                                           & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))
                    : ((0xffff0000U & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                       | (0x0000ffffU & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)))
                : ((0U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                    ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                        ? ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                            ? ((vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                << 0x00000018U) | (0x00ffffffU 
                                                   & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))
                            : ((0xff000000U & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                               | ((0x00ff0000U & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                                  << 0x00000010U)) 
                                  | (0x0000ffffU & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))))
                        : ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                            ? ((0xffff0000U & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                               | ((0x0000ff00U & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                                  << 8U)) 
                                  | (0x000000ffU & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))
                            : ((0xffffff00U & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                               | (0x000000ffU & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m))))
                    : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)));
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout 
        = ((0U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
            ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                ? ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? (tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                       >> 0x18U) : (0x000000ffU & (tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                                   >> 0x10U)))
                : ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? (0x000000ffU & (tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                      >> 8U)) : (0x000000ffU 
                                                 & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))
            : ((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? (IData)((QData)((IData)((tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                               >> 0x10U))))
                    : (IData)((QData)((IData)((0x0000ffffU 
                                               & tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))))
                : ((2U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                    ? tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw
                    : 0U)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e)));
    vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata = 
        ((((- (IData)((0x80200000U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
           | ((- (IData)((0x80200004U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
              | ((- (IData)((0x80200010U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                 | ((- (IData)((0x80200020U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                    | ((- (IData)((0x80200064U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                       | ((- (IData)((0x80200070U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                          | (- (IData)((0x80200074U 
                                        == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))))))))) 
          & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m)
              ? 0U : ((0x80200000U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                       ? (IData)(vlSelfRef.tb_func__DOT__virtual_sw)
                       : ((0x80200004U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                           ? (IData)((vlSelfRef.tb_func__DOT__virtual_sw 
                                      >> 0x00000020U))
                           : ((0x80200010U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                               ? (IData)(vlSelfRef.tb_func__DOT__virtual_key)
                               : ((0x80200020U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                   ? vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__seg_wdata
                                   : ((0x80200064U 
                                       == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                       ? 1U : ((0x80200070U 
                                                == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                                ? vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_done_code
                                                : (
                                                   (0x80200074U 
                                                    == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                                    ? vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_info_code
                                                    : 0xdeadbeefU))))))))) 
         | (((- (IData)((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0))) 
             & vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout) 
            | ((- (IData)((0x80200050U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
               & vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e)
            ? 3U : 0U);
    if (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m) {
        if ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e)))) {
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 1U;
        }
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 0U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 1U;
    } else {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 0U;
        if (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w) {
            if ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e)))) {
                tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 2U;
            }
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e = 2U;
        }
    }
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 0U;
    if (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m) {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 1U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 0U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 1U;
    } else {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 0U;
        if (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w) {
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 2U;
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e = 2U;
        }
    }
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0U;
    if ((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 3U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 3U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0U;
    } else if ((4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 3U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 3U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 0U;
    } else if ((8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e = 3U;
        if (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m) {
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 1U;
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 2U;
        } else if (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w) {
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 2U;
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 3U;
        } else {
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e = 0U;
            tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e = 1U;
        }
    }
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data 
        = ((1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e))
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e))
                ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : ((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e))
                    ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e
                    : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data 
        = ((1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))
                ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
        = ((1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e))
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e))
                ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : ((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e))
                    ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e
                    : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
        = ((1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
            : ((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))
                ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e));
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e)) 
                               << 1U) | (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))))))) {
        if ((0U != (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e)) 
                     << 1U) | (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:58: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b1_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 58, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e)) 
                               << 1U) | (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))))))) {
        if ((0U != (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e)) 
                     << 1U) | (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:64: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__b2_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 64, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                               << 2U) | (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                                          << 1U) | 
                                         (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)))))))) {
        if ((0U != (((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                     << 2U) | (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)) 
                                << 1U) | (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:70: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 70, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                               << 2U) | (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                                          << 1U) | 
                                         (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)))))))) {
        if ((0U != (((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                     << 2U) | (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)) 
                                << 1U) | (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:77: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a1_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 77, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                               << 2U) | (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                                          << 1U) | 
                                         (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)))))))) {
        if ((0U != (((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                     << 2U) | (((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)) 
                                << 1U) | (1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: stage_ex.sv:84: Assertion failed in %Ntb_func.dut.Core_cpu.u_core.u_stage_ex: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_sel_e));
                VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/rtl/core/ex/stage_ex.sv", 84, "");
            }
        }
    }
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data 
        = ((1U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e))
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e
            : ((2U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e))
                ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m
                : ((3U == (IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__t1_sel_e))
                    ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w
                    : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e)));
    __VdfgRegularize_h6e95ff9d_0_0 = (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                      == tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data);
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 0U;
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target 
        = (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data 
           + vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e);
    if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e) {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken 
            = ((4U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                ? ((2U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                    ? ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                        ? (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                           >= vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)
                        : (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                           < vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data))
                    : ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                        ? VL_GTES_III(32, tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data, vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)
                        : VL_LTS_III(32, tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data, vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)))
                : ((1U & (~ ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e) 
                             >> 1U))) && ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e))
                                           ? (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                                              != vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data)
                                           : (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b1_data 
                                              == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data))));
    } else if ((4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 1U;
    } else if ((8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) {
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken = 1U;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target 
            = (0xfffffffeU & (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__t1_data 
                              + vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e));
    }
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e 
        = (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e) 
            | (4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))) 
           | (8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)));
    if (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_taken) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e 
            = tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target;
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e 
            = tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__u_branch_cmp__DOT__branch_target;
    } else {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e 
            = ((IData)(4U) + vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e);
        tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e 
            = ((IData)(4U) + vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e);
    }
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e) 
           & (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e 
              != vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_e 
        = ((2U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e))
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e
            : (((4U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)) 
                | (8U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e)))
                ? ((IData)(4U) + vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e)
                : ((8U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                    ? ((4U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                        ? ((2U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? 0U : ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                     ? ((tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                         >= tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                         ? 1U : 0U)
                                     : (VL_GTES_III(32, tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data, tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                         ? 1U : 0U)))
                        : ((2U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? ((IData)(__VdfgRegularize_h6e95ff9d_0_0)
                                    ? 0U : 1U) : ((IData)(__VdfgRegularize_h6e95ff9d_0_0)
                                                   ? 1U
                                                   : 0U))
                            : ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? ((tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                    < tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                    ? 1U : 0U) : (VL_LTS_III(32, tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data, tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                                   ? 1U
                                                   : 0U))))
                    : ((4U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                        ? ((2U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? VL_SHIFTRS_III(32,32,5, tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data, 
                                                 (0x0000001fU 
                                                  & tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data))
                                : (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   >> (0x0000001fU 
                                       & tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)))
                            : ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   << (0x0000001fU 
                                       & tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data))
                                : (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   - tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)))
                        : ((2U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                            ? ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   + tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                : (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   ^ tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data))
                            : ((1U & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e))
                                ? (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   | tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)
                                : (tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a1_data 
                                   & tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__a2_data)))))));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e) 
           | (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_next_hz 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e)
            ? tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e
            : ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d)
                ? vlSelfRef.tb_func__DOT__dut__DOT__pc
                : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f));
}

VL_ATTR_COLD void Vtb_func___024root___eval_stl(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_stl\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_func___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_func___024root___eval_phase__stl(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_phase__stl\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_func___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_func___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_func___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_func___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_func___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_func___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_func___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_func.w_cpu_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge tb_func.w_clk_rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(negedge tb_func.w_cpu_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @(posedge tb_func.w_clk_50mhz)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @( ((2'h0 != tb_func.result) | (64'h1dcd6500 <= tb_func.cycles)))\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_func___024root___ctor_var_reset(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___ctor_var_reset\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_func__DOT__w_cpu_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7633711593987789938ull);
    vlSelf->tb_func__DOT__w_clk_50mhz = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8479021155929925910ull);
    vlSelf->tb_func__DOT__w_clk_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1789594069395624676ull);
    vlSelf->tb_func__DOT__virtual_key = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6928899123343177960ull);
    vlSelf->tb_func__DOT__virtual_sw = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 18144974213664535979ull);
    vlSelf->tb_func__DOT__result = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7531888056479966324ull);
    vlSelf->tb_func__DOT__cycles = 0;
    vlSelf->tb_func__DOT__last_info = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5069883000146920399ull);
    vlSelf->tb_func__DOT__last_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9594007129974999038ull);
    vlSelf->tb_func__DOT__last_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15281443633494483891ull);
    vlSelf->tb_func__DOT__dut__DOT__pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5148907503633775060ull);
    vlSelf->tb_func__DOT__dut__DOT__perip_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17215450013488752801ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_next_hz = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3049088713740891537ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15285189675135944909ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5641175628080125817ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 73174598161717570ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3980541754202476432ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13477484878504575262ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 423792337400124089ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11324774328530335514ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1011367556993374581ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6903486367208564702ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2048694118784163685ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3196823904224350846ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13682276563780743141ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3055035288945984981ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12046077425175580399ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_d = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2989102935621453916ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8288811199866394965ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17167362376881794905ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17130992414682621272ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8590975594146598746ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1255581998503280432ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8623711833247495190ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3394885945386523787ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11674163021418799038ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5712261361259454996ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7587613451822964339ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5495568774971144560ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8461994247684576161ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9475934436457191383ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10670475362241299813ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_e = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2229952462434882204ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6302656580837009410ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3184357078482272947ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6562400064100441861ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11430772141447177044ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12780199105095955923ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9031712951008517417ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2871245609437091587ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10802192801451837454ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11333335954952744018ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4354856603795661894ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9478734751939782899ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4191788864936274872ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8332016206182117226ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9578038744227942995ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1889315977514273627ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13162776011709327780ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_m = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1629378665724853050ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10190434787178641728ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4832999768277070545ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7890590914922333564ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10022797931184056541ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 325693254007190197ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11480405988084169850ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2118199612491881901ull);
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6271219392724115135ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(26, __VscopeHash, 3330560289166215604ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 262780524350511324ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2301247037270297600ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5688235291257433295ull);
    }
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16925896354397052054ull);
    }
    vlSelf->tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15182789810239601505ull);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->tb_func__DOT__dut__DOT__Mem_IROM__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 250155007587352832ull);
    }
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__seg_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7067817471870412714ull);
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_done_code = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12301391349131207175ull);
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_info_code = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13918443986163540867ull);
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen = 0;
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0 = 0;
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1566536907907658187ull);
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 896944849476816530ull);
    for (int __Vi0 = 0; __Vi0 < 65536; ++__Vi0) {
        vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2340782411881802764ull);
    }
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14802813728841643801ull);
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4719878541108880713ull);
    vlSelf->tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12204842391813170178ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_50mhz__0 = 0;
    vlSelf->__Vtrigprevexpr_h298d6784__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
