// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_COREMARK__SYMS_H_
#define VERILATED_VTB_COREMARK__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_coremark.h"

// INCLUDE MODULE CLASSES
#include "Vtb_coremark___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_coremark__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_coremark* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_coremark___024root         TOP;

    // CONSTRUCTORS
    Vtb_coremark__Syms(VerilatedContext* contextp, const char* namep, Vtb_coremark* modelp);
    ~Vtb_coremark__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
