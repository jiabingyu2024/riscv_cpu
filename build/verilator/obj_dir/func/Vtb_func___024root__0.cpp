// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_func.h for the primary calling header

#include "Vtb_func__pch.h"

VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__0(Vtb_func___024root* vlSelf);
VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__1(Vtb_func___024root* vlSelf);
VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__2(Vtb_func___024root* vlSelf);
VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__3(Vtb_func___024root* vlSelf);

void Vtb_func___024root___eval_initial(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_initial\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_READMEM_N(true, 32, 4096, 0, "rtl/ip/irom.mem"s
                 ,  &(vlSelfRef.tb_func__DOT__dut__DOT__Mem_IROM__DOT__mem)
                 , 0, ~0ULL);
    VL_READMEM_N(true, 32, 65536, 0, "rtl/ip/dram.mem"s
                 ,  &(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem)
                 , 0, ~0ULL);
    Vtb_func___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_func___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_func___024root___eval_initial__TOP__Vtiming__2(vlSelf);
    Vtb_func___024root___eval_initial__TOP__Vtiming__3(vlSelf);
}

VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__0(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_func__DOT__w_cpu_clk = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                             nullptr, 
                                             "/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 
                                             66);
        vlSelfRef.tb_func__DOT__w_cpu_clk = (1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_cpu_clk)));
    }
    co_return;
}

VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__1(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_func__DOT__w_clk_50mhz = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000002710ULL, 
                                             nullptr, 
                                             "/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 
                                             71);
        vlSelfRef.tb_func__DOT__w_clk_50mhz = (1U & 
                                               (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_50mhz)));
    }
    co_return;
}

void Vtb_func___024root____VbeforeTrig_ha22db48e__0(Vtb_func___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__2(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_func__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_func__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    // Body
    vlSelfRef.tb_func__DOT__virtual_key = 0U;
    vlSelfRef.tb_func__DOT__virtual_sw = 0ULL;
    vlSelfRef.tb_func__DOT__w_clk_rst = 1U;
    vlSelfRef.tb_func__DOT__result = 0U;
    vlSelfRef.tb_func__DOT__cycles = 0ULL;
    vlSelfRef.tb_func__DOT__last_info = 0U;
    vlSelfRef.tb_func__DOT__last_addr = 0U;
    vlSelfRef.tb_func__DOT__last_wdata = 0U;
    if ((! VL_VALUEPLUSARGS_INN(64, "irom=%s"s, vlSelfRef.tb_func__DOT__irom_file))) {
        vlSelfRef.tb_func__DOT__irom_file = "rtl/ip/irom.mem"s;
    }
    if ((! VL_VALUEPLUSARGS_INN(64, "dram=%s"s, vlSelfRef.tb_func__DOT__dram_file))) {
        vlSelfRef.tb_func__DOT__dram_file = "rtl/ip/dram.mem"s;
    }
    if (VL_VALUEPLUSARGS_INN(64, "dump=%s"s, vlSelfRef.tb_func__DOT__dump_file)) {
        vlSymsp->_vm_contextp__->dumpfile(vlSelfRef.tb_func__DOT__dump_file);
        VL_PRINTF_MT("-Info: /home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv:90: $dumpvar ignored, as Verilated without --trace\n");
    }
    VL_WRITEF_NX("[TB-FUNC] load irom=%0@\n[TB-FUNC] load dram=%0@\n",0,
                 -1,&(vlSelfRef.tb_func__DOT__irom_file),
                 -1,&(vlSelfRef.tb_func__DOT__dram_file));
    VL_READMEM_N(true, 32, 4096, 0, vlSelfRef.tb_func__DOT__irom_file
                 ,  &(vlSelfRef.tb_func__DOT__dut__DOT__Mem_IROM__DOT__mem)
                 , 0, ~0ULL);
    VL_READMEM_N(true, 32, 65536, 0, vlSelfRef.tb_func__DOT__dram_file
                 ,  &(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem)
                 , 0, ~0ULL);
    tb_func__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x00000014U;
    while (VL_LTS_III(32, 0U, tb_func__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_func___024root____VbeforeTrig_ha22db48e__0(vlSelf, 
                                                       "@(posedge tb_func.w_cpu_clk)");
        co_await vlSelfRef.__VtrigSched_ha22db48e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_func.w_cpu_clk)", 
                                                             "/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 
                                                             98);
        tb_func__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_func__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_func__DOT__w_clk_rst = 0U;
    co_return;
}

void Vtb_func___024root____VbeforeTrig_h7d3a5011__0(Vtb_func___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_func___024root___eval_initial__TOP__Vtiming__3(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_initial__TOP__Vtiming__3\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vfunc_tb_result_to_string__0__result;
    __Vfunc_tb_result_to_string__0__result = 0;
    std::string __Vtemp_1;
    // Body
    while ((1U & (~ ((0U != (IData)(vlSelfRef.tb_func__DOT__result)) 
                     | (0x000000001dcd6500ULL <= vlSelfRef.tb_func__DOT__cycles))))) {
        Vtb_func___024root____VbeforeTrig_h7d3a5011__0(vlSelf, 
                                                       "@( ((2'h0 != tb_func.result) | (64'h1dcd6500 <= tb_func.cycles)))");
        co_await vlSelfRef.__VtrigSched_h7d3a5011__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( ((2'h0 != tb_func.result) | (64'h1dcd6500 <= tb_func.cycles)))", 
                                                             "/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 
                                                             123);
    }
    if ((0U == (IData)(vlSelfRef.tb_func__DOT__result))) {
        vlSelfRef.tb_func__DOT__result = 3U;
    }
    __Vtemp_1 = ([&]() {
            __Vfunc_tb_result_to_string__0__result 
                = vlSelfRef.tb_func__DOT__result;
            vlSelfRef.__Vfunc_tb_result_to_string__0__Vfuncout 
                = ((1U == (IData)(__Vfunc_tb_result_to_string__0__result))
                    ? "PASS"s : ((2U == (IData)(__Vfunc_tb_result_to_string__0__result))
                                  ? "FAIL"s : ((3U 
                                                == (IData)(__Vfunc_tb_result_to_string__0__result))
                                                ? "TIMEOUT"s
                                                : "NONE"s)));
        }(), vlSelfRef.__Vfunc_tb_result_to_string__0__Vfuncout);
    VL_WRITEF_NX("[TB-FUNC] result=%@ cycles=%0# last_addr=0x%08x last_wdata=0x%08x sim_info=0x%08x\n",0,
                 -1,&(__Vtemp_1),64,vlSelfRef.tb_func__DOT__cycles,
                 32,vlSelfRef.tb_func__DOT__last_addr,
                 32,vlSelfRef.tb_func__DOT__last_wdata,
                 32,vlSelfRef.tb_func__DOT__last_info);
    if (VL_UNLIKELY(((1U == (IData)(vlSelfRef.tb_func__DOT__result))))) {
        VL_FINISH_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 130, "");
    } else if ((2U == (IData)(vlSelfRef.tb_func__DOT__result))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_func.sv:131: Assertion failed in %Ntb_func: [TB-FUNC] testcase reported FAIL\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 131, "", false);
    } else {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_func.sv:132: Assertion failed in %Ntb_func: [TB-FUNC] testcase TIMEOUT\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 132, "", false);
    }
    co_return;
}

void Vtb_func___024root___eval_triggers_vec__act(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_triggers_vec__act\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vtrigprevexpr_h298d6784__0;
    __Vtrigprevexpr_h298d6784__0 = 0;
    // Body
    __Vtrigprevexpr_h298d6784__0 = ((0U != (IData)(vlSelfRef.tb_func__DOT__result)) 
                                    | (0x000000001dcd6500ULL 
                                       <= vlSelfRef.tb_func__DOT__cycles));
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(__Vtrigprevexpr_h298d6784__0) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr_h298d6784__1)) 
                                                       << 5U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 4U)) 
                                                     | (((((IData)(vlSelfRef.tb_func__DOT__w_clk_50mhz) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_50mhz__0))) 
                                                          << 3U) 
                                                         | (((~ (IData)(vlSelfRef.tb_func__DOT__w_cpu_clk)) 
                                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0)) 
                                                            << 2U)) 
                                                        | ((((IData)(vlSelfRef.tb_func__DOT__w_clk_rst) 
                                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_rst__0))) 
                                                            << 1U) 
                                                           | ((IData)(vlSelfRef.tb_func__DOT__w_cpu_clk) 
                                                              & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0))))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0 
        = vlSelfRef.tb_func__DOT__w_cpu_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_rst__0 
        = vlSelfRef.tb_func__DOT__w_clk_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_clk_50mhz__0 
        = vlSelfRef.tb_func__DOT__w_clk_50mhz;
    vlSelfRef.__Vtrigprevexpr_h298d6784__1 = __Vtrigprevexpr_h298d6784__0;
}

bool Vtb_func___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___trigger_anySet__act\n"); );
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

void Vtb_func___024root___act_sequent__TOP__0(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___act_sequent__TOP__0\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw;
    tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw = 0;
    // Body
    tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
        = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem
        [(0x0000ffffU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m 
                         >> 2U))];
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
}

void Vtb_func___024root___eval_act(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_act\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_func___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtb_func___024root___nba_sequent__TOP__0(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___nba_sequent__TOP__0\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0;
    IData/*31:0*/ __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0;
    // Body
    __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
        = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
        = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0U;
        __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = 0U;
    } else {
        __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
            = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start)
                ? ((0xc34fU == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))
                    ? 0U : (0x0000ffffU & ((IData)(1U) 
                                           + (IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))))
                : 0U);
        if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start) 
             & (0xc34fU == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms)))) {
            __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
                = ((IData)(1U) + vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms);
        }
        if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen) 
             & (0x80000000U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m))) {
            vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = 1U;
        } else if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen) 
                    & (0xffffffffU == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m))) {
            vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = 0U;
        }
    }
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
        = __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
        = __Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
}

void Vtb_func___024root___nba_sequent__TOP__1(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___nba_sequent__TOP__1\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v0;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16;
    __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v0;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v0 = 0;
    IData/*25:0*/ __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16;
    __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16;
    __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v0;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16;
    __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16;
    __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v0;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v0 = 0;
    CData/*1:0*/ __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16;
    __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16;
    __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16 = 0;
    CData/*1:0*/ __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17;
    __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17 = 0;
    CData/*3:0*/ __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17;
    __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17 = 0;
    // Body
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v0 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v0 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v0 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v0 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17 = 0U;
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_e 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e))) 
               && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_read_d)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_e 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e))) 
               && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_rs2_imm_d)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_e 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e))) 
               && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__is_branch_d)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_w 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_m));
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v0 = 1U;
    } else if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e) {
        __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16 
            = (0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                              >> 2U));
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16 = 1U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v0) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[0U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[1U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[2U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[3U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[4U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[5U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[6U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[7U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[8U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[9U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[10U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[11U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[12U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[13U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[14U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[15U] = 0U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem[__VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__valid_mem__v16] = 1U;
    }
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v0 = 1U;
    } else if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e) {
        __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16 
            = (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
               >> 6U);
        __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16 
            = (0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                              >> 2U));
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16 = 1U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v0) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[0U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[1U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[2U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[3U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[4U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[5U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[6U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[7U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[8U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[9U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[10U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[11U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[12U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[13U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[14U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[15U] = 0U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem[__VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16] 
            = __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__tag_mem__v16;
    }
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v0 = 1U;
    } else if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e) {
        __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16 
            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_target_e;
        __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16 
            = (0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                              >> 2U));
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16 = 1U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v0) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[0U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[1U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[2U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[3U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[4U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[5U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[6U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[7U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[8U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[9U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[10U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[11U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[12U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[13U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[14U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[15U] = 0U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem[__VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16] 
            = __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__target_mem__v16;
    }
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v0 = 1U;
    } else if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e) {
        if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__update_taken_e) {
            if ((3U != vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem
                 [(0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                                  >> 2U))])) {
                __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16 
                    = (3U & ((IData)(1U) + vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem
                             [(0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                                              >> 2U))]));
                __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16 
                    = (0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                                      >> 2U));
                __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16 = 1U;
            }
        } else if ((0U != vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem
                    [(0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                                     >> 2U))])) {
            __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17 
                = (3U & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem
                         [(0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                                          >> 2U))] 
                         - (IData)(1U)));
            __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17 
                = (0x0000000fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                                  >> 2U));
            __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17 = 1U;
        }
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v0) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[0U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[1U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[2U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[3U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[4U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[5U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[6U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[7U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[8U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[9U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[10U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[11U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[12U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[13U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[14U] = 1U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[15U] = 1U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[__VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16] 
            = __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v16;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem[__VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17] 
            = __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_bpu_top__DOT__counter_mem__v17;
    }
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e = 3U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_d = 0U;
    } else {
        if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e = 3U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e = 0U;
        } else {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_e 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_ctrl_d;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_e 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__imm_d;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_e 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_d;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_e 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_spec_d;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__func3_e 
                = (7U & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                         >> 0x0000000cU));
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_data_e 
                = ((0U == (0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                          >> 0x00000014U)))
                    ? 0U : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem
                   [(0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                    >> 0x00000014U))]);
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_data_e 
                = ((0U == (0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                          >> 0x0000000fU)))
                    ? 0U : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem
                   [(0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                    >> 0x0000000fU))]);
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e 
                = (0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                  >> 0x00000014U));
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e 
                = (0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                  >> 0x0000000fU));
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_d;
        }
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w 
            = ((0U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                ? ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_m)
                    ? (0x000000ffU & vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata)
                    : (((- (IData)((1U & (vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata 
                                          >> 7U)))) 
                        << 8U) | (0x000000ffU & vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata)))
                : ((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                    ? ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_m)
                        ? (0x0000ffffU & vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata)
                        : (((- (IData)((1U & (vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata 
                                              >> 0x0000000fU)))) 
                            << 0x00000010U) | (0x0000ffffU 
                                               & vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata)))
                    : vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata));
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w 
            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m;
        if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_d = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d)))) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_d 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f;
        }
    }
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
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_m 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_e));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_m 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_e));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_e 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e))) 
               && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_d)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_e 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e))) 
               && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__load_unsigned_d)));
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m = 2U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_d = 0U;
    } else {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m 
            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_e;
        if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_d = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d)))) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_d 
                = vlSelfRef.tb_func__DOT__dut__DOT__pc;
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
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_e 
        = ((IData)(vlSelfRef.tb_func__DOT__w_clk_rst)
            ? 2U : ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e)
                     ? 2U : (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_d)));
}

void Vtb_func___024root___nba_sequent__TOP__2(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___nba_sequent__TOP__2\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*63:0*/ __Vdly__tb_func__DOT__cycles;
    __Vdly__tb_func__DOT__cycles = 0;
    QData/*63:0*/ __VdlyMask__tb_func__DOT__cycles;
    __VdlyMask__tb_func__DOT__cycles = 0;
    IData/*31:0*/ __Vdly__tb_func__DOT__last_addr;
    __Vdly__tb_func__DOT__last_addr = 0;
    IData/*31:0*/ __VdlyMask__tb_func__DOT__last_addr;
    __VdlyMask__tb_func__DOT__last_addr = 0;
    IData/*31:0*/ __Vdly__tb_func__DOT__last_wdata;
    __Vdly__tb_func__DOT__last_wdata = 0;
    IData/*31:0*/ __VdlyMask__tb_func__DOT__last_wdata;
    __VdlyMask__tb_func__DOT__last_wdata = 0;
    IData/*31:0*/ __Vdly__tb_func__DOT__last_info;
    __Vdly__tb_func__DOT__last_info = 0;
    IData/*31:0*/ __VdlyMask__tb_func__DOT__last_info;
    __VdlyMask__tb_func__DOT__last_info = 0;
    CData/*1:0*/ __Vdly__tb_func__DOT__result;
    __Vdly__tb_func__DOT__result = 0;
    CData/*1:0*/ __VdlyMask__tb_func__DOT__result;
    __VdlyMask__tb_func__DOT__result = 0;
    IData/*31:0*/ __VdlyVal__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0;
    __VdlyVal__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0;
    SData/*15:0*/ __VdlyDim0__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0;
    __VdlyDim0__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0;
    __VdlySet__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0;
    // Body
    __VdlySet__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0U;
    if (((~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst)) 
         & (0U == (IData)(vlSelfRef.tb_func__DOT__result)))) {
        __Vdly__tb_func__DOT__cycles = (1ULL + vlSelfRef.tb_func__DOT__cycles);
        __VdlyMask__tb_func__DOT__cycles = 0xffffffffffffffffULL;
    }
    if (((~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst)) 
         & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m))) {
        __Vdly__tb_func__DOT__last_wdata = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m;
        __VdlyMask__tb_func__DOT__last_wdata = 0xffffffffU;
        __Vdly__tb_func__DOT__last_addr = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m;
        __VdlyMask__tb_func__DOT__last_addr = 0xffffffffU;
        if ((0x80200074U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
            __Vdly__tb_func__DOT__last_info = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m;
            __VdlyMask__tb_func__DOT__last_info = 0xffffffffU;
        }
        if ((0x80200070U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
            if ((1U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)) {
                __Vdly__tb_func__DOT__result = 1U;
                __VdlyMask__tb_func__DOT__result = 3U;
            } else if ((0xdead0001U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)) {
                __Vdly__tb_func__DOT__result = 2U;
                __VdlyMask__tb_func__DOT__result = 3U;
            }
        }
    }
    if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m) 
         & (IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0))) {
        __VdlyVal__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0 
            = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_data;
        __VdlyDim0__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0 
            = (0x0000ffffU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m 
                              >> 2U));
        __VdlySet__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0 = 1U;
    }
    vlSelfRef.tb_func__DOT__cycles = ((__Vdly__tb_func__DOT__cycles 
                                       & __VdlyMask__tb_func__DOT__cycles) 
                                      | (vlSelfRef.tb_func__DOT__cycles 
                                         & (~ __VdlyMask__tb_func__DOT__cycles)));
    __VdlyMask__tb_func__DOT__cycles = 0ULL;
    vlSelfRef.tb_func__DOT__last_wdata = ((__Vdly__tb_func__DOT__last_wdata 
                                           & __VdlyMask__tb_func__DOT__last_wdata) 
                                          | (vlSelfRef.tb_func__DOT__last_wdata 
                                             & (~ __VdlyMask__tb_func__DOT__last_wdata)));
    __VdlyMask__tb_func__DOT__last_wdata = 0U;
    vlSelfRef.tb_func__DOT__last_addr = ((__Vdly__tb_func__DOT__last_addr 
                                          & __VdlyMask__tb_func__DOT__last_addr) 
                                         | (vlSelfRef.tb_func__DOT__last_addr 
                                            & (~ __VdlyMask__tb_func__DOT__last_addr)));
    __VdlyMask__tb_func__DOT__last_addr = 0U;
    vlSelfRef.tb_func__DOT__last_info = ((__Vdly__tb_func__DOT__last_info 
                                          & __VdlyMask__tb_func__DOT__last_info) 
                                         | (vlSelfRef.tb_func__DOT__last_info 
                                            & (~ __VdlyMask__tb_func__DOT__last_info)));
    __VdlyMask__tb_func__DOT__last_info = 0U;
    vlSelfRef.tb_func__DOT__result = (((IData)(__Vdly__tb_func__DOT__result) 
                                       & (IData)(__VdlyMask__tb_func__DOT__result)) 
                                      | ((IData)(vlSelfRef.tb_func__DOT__result) 
                                         & (~ (IData)(__VdlyMask__tb_func__DOT__result))));
    __VdlyMask__tb_func__DOT__result = 0U;
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__seg_wdata = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_done_code = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_info_code = 0U;
    } else if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m) {
        if ((0x80200040U != vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
            if ((0x80200020U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
                vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__seg_wdata 
                    = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m;
            }
            if ((0x80200020U != vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
                if ((0x80200070U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
                    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_done_code 
                        = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m;
                }
                if ((0x80200070U != vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
                    if ((0x80200074U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)) {
                        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_info_code 
                            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m;
                    }
                }
            }
        }
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0) {
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0] 
            = __VdlyVal__tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem__v0;
    }
}

void Vtb_func___024root___nba_sequent__TOP__3(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___nba_sequent__TOP__3\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
    __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0;
    CData/*4:0*/ __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
    __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0;
    CData/*0:0*/ __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0;
    // Body
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0 = 0U;
    __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0U;
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0 = 1U;
    } else if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w) 
                & (0U != (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w)))) {
        __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 
            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w;
        __VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 
            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w;
        __VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 1U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[0U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[1U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[2U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[3U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[4U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[5U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[6U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[7U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[8U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[9U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[10U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[11U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[12U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[13U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[14U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[15U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[16U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[17U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[18U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[19U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[20U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[21U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[22U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[23U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[24U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[25U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[26U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[27U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[28U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[29U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[30U] = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[31U] = 0U;
    }
    if (__VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[__VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32] 
            = __VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
    }
}

void Vtb_func___024root___nba_sequent__TOP__4(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___nba_sequent__TOP__4\n"); );
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
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_0;
    __VdfgRegularize_h6e95ff9d_0_0 = 0;
    // Body
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_src_w)
            ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_data_w
            : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_w);
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_e));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_e 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e))) 
               && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_d)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m 
        = ((IData)(vlSelfRef.tb_func__DOT__w_clk_rst)
            ? 0U : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_e);
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_m) 
           & (0x80200050U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m));
    vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0 
        = ((0x80100000U <= vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m) 
           & (0x8013ffffU > vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e));
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w = 0U;
    } else {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_ex__DOT__b2_data;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w 
            = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m;
    }
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w) 
           & (0U != (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_m_w 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_m_w 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_1) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e 
        = ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__w_clk_rst))) 
           && ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e))) 
               && (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_d)));
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m 
        = ((IData)(vlSelfRef.tb_func__DOT__w_clk_rst)
            ? 0U : (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_m) 
           & (0U != (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs2_e_m 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs2_addr_e)));
    tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT__hit_rs1_e_m 
        = ((IData)(tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_forward_unit__DOT____VdfgRegularize_hcada4e97_0_0) 
           & ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_m) 
              == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rs1_addr_e)));
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
    if (vlSelfRef.tb_func__DOT__w_clk_rst) {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d = 0U;
    } else {
        vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_e 
            = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__flush_d_e)
                ? 0U : (0x0000001fU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                                       >> 7U)));
        if (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d)))) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__inst_d 
                = vlSelfRef.tb_func__DOT__dut__DOT__Mem_IROM__DOT__mem
                [(0x00000fffU & (vlSelfRef.tb_func__DOT__dut__DOT__pc 
                                 >> 2U))];
        }
    }
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
    vlSelfRef.tb_func__DOT__dut__DOT__pc = ((IData)(vlSelfRef.tb_func__DOT__w_clk_rst)
                                             ? 0x80000000U
                                             : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_next_hz);
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
    vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_next_hz 
        = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__error_e)
            ? tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__right_pc_e
            : ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__stall_f_d)
                ? vlSelfRef.tb_func__DOT__dut__DOT__pc
                : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__pc_predict_f));
}

void Vtb_func___024root___nba_comb__TOP__0(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___nba_comb__TOP__0\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw;
    tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw = 0;
    // Body
    tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
        = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem
        [(0x0000ffffU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m 
                         >> 2U))];
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
}

void Vtb_func___024root___nba_comb__TOP__1(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___nba_comb__TOP__1\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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
}

void Vtb_func___024root___eval_nba(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_nba\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0;
    __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0 = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__3___VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
    __Vinline__nba_sequent__TOP__3___VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0;
    CData/*4:0*/ __Vinline__nba_sequent__TOP__3___VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
    __Vinline__nba_sequent__TOP__3___VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
    __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0;
    IData/*31:0*/ __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw;
    __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw = 0;
    // Body
    if ((8ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
            = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
        __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
            = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
        if (vlSelfRef.tb_func__DOT__w_clk_rst) {
            __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = 0U;
        } else {
            __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
                = ((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start)
                    ? ((0xc34fU == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))
                        ? 0U : (0x0000ffffU & ((IData)(1U) 
                                               + (IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))))
                    : 0U);
            if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start) 
                 & (0xc34fU == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms)))) {
                __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
                    = ((IData)(1U) + vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms);
            }
            if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen) 
                 & (0x80000000U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m))) {
                vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = 1U;
            } else if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____Vcellinp__counter_inst__cnt_wen) 
                        & (0xffffffffU == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m))) {
                vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__start = 0U;
            }
        }
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_func___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_func___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0 = 0U;
        __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 0U;
        if (vlSelfRef.tb_func__DOT__w_clk_rst) {
            __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0 = 1U;
        } else if (((IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_w) 
                    & (0U != (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w)))) {
            __Vinline__nba_sequent__TOP__3___VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__wb_data_w;
            __Vinline__nba_sequent__TOP__3___VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 
                = vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__rd_addr_w;
            __Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32 = 1U;
        }
        if (__Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v0) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[0U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[1U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[2U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[3U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[4U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[5U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[6U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[7U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[8U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[9U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[10U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[11U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[12U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[13U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[14U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[15U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[16U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[17U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[18U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[19U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[20U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[21U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[22U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[23U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[24U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[25U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[26U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[27U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[28U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[29U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[30U] = 0U;
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[31U] = 0U;
        }
        if (__Vinline__nba_sequent__TOP__3___VdlySet__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32) {
            vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem[__Vinline__nba_sequent__TOP__3___VdlyDim0__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32] 
                = __Vinline__nba_sequent__TOP__3___VdlyVal__tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__u_stage_id__DOT__u_regfile__DOT__rf_mem__v32;
        }
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_func___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
            = vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__Mem_DRAM__DOT__mem
            [(0x0000ffffU & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m 
                             >> 2U))];
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout = 0U;
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout 
            = ((0U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                    ? ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                        ? (__Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                           >> 0x18U) : (0x000000ffU 
                                        & (__Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                           >> 0x10U)))
                    : ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                        ? (0x000000ffU & (__Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                          >> 8U)) : 
                       (0x000000ffU & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))
                : ((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                    ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                        ? (IData)((QData)((IData)((__Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw 
                                                   >> 0x10U))))
                        : (IData)((QData)((IData)((0x0000ffffU 
                                                   & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))))
                    : ((2U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                        ? __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw
                        : 0U)));
        vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_data 
            = ((2U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                ? vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m
                : ((1U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                    ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                        ? ((vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                            << 0x00000010U) | (0x0000ffffU 
                                               & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))
                        : ((0xffff0000U & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                           | (0x0000ffffU & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)))
                    : ((0U == (IData)(vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__mem_mask_m))
                        ? ((2U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                            ? ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                ? ((vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                    << 0x00000018U) 
                                   | (0x00ffffffU & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))
                                : ((0xff000000U & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                                   | ((0x00ff0000U 
                                       & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                          << 0x00000010U)) 
                                      | (0x0000ffffU 
                                         & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw))))
                            : ((1U & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                ? ((0xffff0000U & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                                   | ((0x0000ff00U 
                                       & (vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m 
                                          << 8U)) | 
                                      (0x000000ffU 
                                       & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw)))
                                : ((0xffffff00U & __Vinline__nba_comb__TOP__0_tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dram_rdata_raw) 
                                   | (0x000000ffU & vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m))))
                        : vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__a2_data_m)));
    }
    if ((0x000000000000000bULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.tb_func__DOT__dut__DOT__perip_rdata 
            = ((((- (IData)((0x80200000U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                 | ((- (IData)((0x80200004U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                    | ((- (IData)((0x80200010U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                       | ((- (IData)((0x80200020U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                          | ((- (IData)((0x80200064U 
                                         == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                             | ((- (IData)((0x80200070U 
                                            == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
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
                                     : ((0x80200020U 
                                         == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                         ? vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__seg_wdata
                                         : ((0x80200064U 
                                             == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                             ? 1U : 
                                            ((0x80200070U 
                                              == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                              ? vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_done_code
                                              : ((0x80200074U 
                                                  == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m)
                                                  ? vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__sim_info_code
                                                  : 0xdeadbeefU))))))))) 
               | (((- (IData)((IData)(vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT____VdfgRegularize_h25f421aa_0_0))) 
                   & vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__dram_driver_inst__DOT__dout) 
                  | ((- (IData)((0x80200050U == vlSelfRef.tb_func__DOT__dut__DOT__Core_cpu__DOT__u_core__DOT__alu_res_m))) 
                     & vlSelfRef.tb_func__DOT__dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms)));
    }
}

void Vtb_func___024root___timing_ready(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___timing_ready\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_ha22db48e__0.ready("@(posedge tb_func.w_cpu_clk)");
    }
    if ((0x0000000000000020ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h7d3a5011__0.ready("@( ((2'h0 != tb_func.result) | (64'h1dcd6500 <= tb_func.cycles)))");
    }
}

void Vtb_func___024root___timing_resume(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___timing_resume\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_ha22db48e__0.moveToResumeQueue(
                                                          "@(posedge tb_func.w_cpu_clk)");
    vlSelfRef.__VtrigSched_h7d3a5011__0.moveToResumeQueue(
                                                          "@( ((2'h0 != tb_func.result) | (64'h1dcd6500 <= tb_func.cycles)))");
    vlSelfRef.__VtrigSched_ha22db48e__0.resume("@(posedge tb_func.w_cpu_clk)");
    vlSelfRef.__VtrigSched_h7d3a5011__0.resume("@( ((2'h0 != tb_func.result) | (64'h1dcd6500 <= tb_func.cycles)))");
    if ((0x0000000000000010ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_func___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_func___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_func___024root___eval_phase__act(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_phase__act\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_func___024root___eval_triggers_vec__act(vlSelf);
    Vtb_func___024root___timing_ready(vlSelf);
    Vtb_func___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_func___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_func___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_func___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_func___024root___timing_resume(vlSelf);
        Vtb_func___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_func___024root___eval_phase__inact(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_phase__inact\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 33, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_func___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_func___024root___eval_phase__nba(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_phase__nba\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_func___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_func___024root___eval_nba(vlSelf);
        Vtb_func___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_func___024root___eval(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_func___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 33, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 33, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_func___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("/home/jiabingyu/prj/riscv_cpu/tb/tb_func.sv", 33, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_func___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_func___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_func___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_func___024root____VbeforeTrig_ha22db48e__0(Vtb_func___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root____VbeforeTrig_ha22db48e__0\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_func__DOT__w_cpu_clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_func__DOT__w_cpu_clk__0 
        = vlSelfRef.tb_func__DOT__w_cpu_clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_ha22db48e__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_func___024root____VbeforeTrig_h7d3a5011__0(Vtb_func___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root____VbeforeTrig_h7d3a5011__0\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    CData/*0:0*/ __Vtrigprevexpr_h298d6784__0;
    __Vtrigprevexpr_h298d6784__0 = 0;
    // Body
    __Vtrigprevexpr_h298d6784__0 = ((0U != (IData)(vlSelfRef.tb_func__DOT__result)) 
                                    | (0x000000001dcd6500ULL 
                                       <= vlSelfRef.tb_func__DOT__cycles));
    __VTmp[0U] = (QData)((IData)((((IData)(__Vtrigprevexpr_h298d6784__0) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr_h298d6784__1)) 
                                  << 5U)));
    vlSelfRef.__Vtrigprevexpr_h298d6784__1 = __Vtrigprevexpr_h298d6784__0;
    if ((0x0000000000000020ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h7d3a5011__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_func___024root___eval_debug_assertions(Vtb_func___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_func___024root___eval_debug_assertions\n"); );
    Vtb_func__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
