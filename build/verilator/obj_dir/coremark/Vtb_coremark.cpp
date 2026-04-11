// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_coremark__pch.h"

//============================================================
// Constructors

Vtb_coremark::Vtb_coremark(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_coremark__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_coremark::Vtb_coremark(const char* _vcname__)
    : Vtb_coremark(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_coremark::~Vtb_coremark() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_coremark___024root___eval_debug_assertions(Vtb_coremark___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_coremark___024root___eval_static(Vtb_coremark___024root* vlSelf);
void Vtb_coremark___024root___eval_initial(Vtb_coremark___024root* vlSelf);
void Vtb_coremark___024root___eval_settle(Vtb_coremark___024root* vlSelf);
void Vtb_coremark___024root___eval(Vtb_coremark___024root* vlSelf);

void Vtb_coremark::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_coremark::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_coremark___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_coremark___024root___eval_static(&(vlSymsp->TOP));
        Vtb_coremark___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_coremark___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_coremark___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_coremark::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_coremark::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_coremark::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_coremark___024root___eval_final(Vtb_coremark___024root* vlSelf);

VL_ATTR_COLD void Vtb_coremark::final() {
    Vtb_coremark___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_coremark::hierName() const { return vlSymsp->name(); }
const char* Vtb_coremark::modelName() const { return "Vtb_coremark"; }
unsigned Vtb_coremark::threads() const { return 1; }
void Vtb_coremark::prepareClone() const { contextp()->prepareClone(); }
void Vtb_coremark::atClone() const {
    contextp()->threadPoolpOnClone();
}
