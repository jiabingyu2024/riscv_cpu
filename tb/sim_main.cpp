#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vtb_rv32ui_top.h"
#include "Vtb_rv32ui_top___024root.h"
#include "Vtb_rv32ui_top_BypassIF.h"
#include "Vtb_rv32ui_top_CommitStageIF.h"
#include "Vtb_rv32ui_top_CtrlIF.h"
#include "Vtb_rv32ui_top_PerfIF.h"
#include "sim_common.hpp"

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace {

constexpr uint32_t kDefaultIromBase = 0x80000000u;
constexpr uint32_t kDefaultDramBase = 0x80100000u;

struct Options {
    std::string irom_path;
    std::string dram_path;
    std::string meta_path;
    std::string wave_path;
    uint64_t max_cycles = 100000;
    uint32_t cpu_mhz = 200;
    uint32_t cnt_mhz = 50;
    uint32_t debug_commit = 0;
    bool wave = false;
};

struct Meta {
    uint32_t base_pc = kDefaultIromBase;
    uint32_t dram_base = kDefaultDramBase;
    uint32_t tohost = 0;
    uint32_t pass_pc = 0;
    uint32_t fail_pc = 0;
    uint32_t led_addr = 0;
    uint32_t pass_led = 0;
    uint32_t fail_led = 0;
    uint32_t seg_addr = 0;
    uint32_t cnt_addr = 0;
    uint32_t pass_tests = 0;
    uint32_t virtual_sw_lo = 0;
    uint32_t virtual_sw_hi = 0;
    uint32_t virtual_key = 0;
    std::string kind;
    std::string suite;
    std::string test_case;
};

struct TestStatus {
    bool finished = false;
    bool passed = false;
    uint32_t tohost_value = 0;
    uint32_t led_value = 0;
    uint32_t seg_value = 0;
    uint32_t counter_ms = 0;
    uint32_t counter_raw_ms = 0;
    uint32_t counter_sub_ms = 0;
    uint64_t virtual_seg = 0;
    bool saw_led = false;
    bool saw_seg = false;
    bool saw_led_pass = false;
    bool seg_passed = false;
    bool virtual_seg_passed = false;
    uint64_t post_led_pass_cycles = 0;
    bool saw_write = false;
    uint32_t last_write_addr = 0;
    uint32_t last_write_data = 0;
    uint32_t last_pc = 0;
};

Meta load_meta(const std::string& path) {
    Meta meta;
    if (path.empty()) return meta;
    std::ifstream in(path);
    if (!in) {
        std::cerr << "warning: cannot open meta file " << path << "\n";
        return meta;
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string text = ss.str();
    meta.base_pc = sim_common::parse_u32(sim_common::json_string_value(text, "base_pc"), meta.base_pc);
    meta.dram_base = sim_common::parse_u32(sim_common::json_string_value(text, "dram_base"), meta.dram_base);
    meta.tohost = sim_common::parse_u32(sim_common::json_string_value(text, "tohost"), meta.tohost);
    meta.pass_pc = sim_common::parse_u32(sim_common::json_string_value(text, "pass"), meta.pass_pc);
    meta.fail_pc = sim_common::parse_u32(sim_common::json_string_value(text, "fail"), meta.fail_pc);
    meta.led_addr = sim_common::parse_u32(sim_common::json_string_value(text, "led_addr"), meta.led_addr);
    meta.pass_led = sim_common::parse_u32(sim_common::json_string_value(text, "pass_led"), meta.pass_led);
    meta.fail_led = sim_common::parse_u32(sim_common::json_string_value(text, "fail_led"), meta.fail_led);
    meta.seg_addr = sim_common::parse_u32(sim_common::json_string_value(text, "seg_addr"), meta.seg_addr);
    meta.cnt_addr = sim_common::parse_u32(sim_common::json_string_value(text, "cnt_addr"), meta.cnt_addr);
    meta.pass_tests = sim_common::parse_u32(sim_common::json_string_value(text, "pass_tests"), meta.pass_tests);
    meta.virtual_sw_lo = sim_common::parse_u32(sim_common::json_string_value(text, "virtual_sw_lo"), meta.virtual_sw_lo);
    meta.virtual_sw_hi = sim_common::parse_u32(sim_common::json_string_value(text, "virtual_sw_hi"), meta.virtual_sw_hi);
    meta.virtual_key = sim_common::parse_u32(sim_common::json_string_value(text, "virtual_key"), meta.virtual_key);
    meta.kind = sim_common::json_string_value(text, "kind");
    meta.suite = sim_common::json_string_value(text, "suite");
    meta.test_case = sim_common::json_string_value(text, "case");
    return meta;
}

Options parse_args(int argc, char** argv) {
    Options opt;
    for (int idx = 1; idx < argc; ++idx) {
        std::string arg = argv[idx];
        if (sim_common::starts_with(arg, "+irom=")) {
            opt.irom_path = arg.substr(6);
        } else if (sim_common::starts_with(arg, "+dram=")) {
            opt.dram_path = arg.substr(6);
        } else if (sim_common::starts_with(arg, "+meta=")) {
            opt.meta_path = arg.substr(6);
        } else if (sim_common::starts_with(arg, "+max-cycles=")) {
            opt.max_cycles = sim_common::parse_u64(arg.substr(12), opt.max_cycles);
        } else if (sim_common::starts_with(arg, "+cpu-mhz=")) {
            opt.cpu_mhz = sim_common::parse_u32(arg.substr(9), opt.cpu_mhz);
        } else if (sim_common::starts_with(arg, "+cnt-mhz=")) {
            opt.cnt_mhz = sim_common::parse_u32(arg.substr(9), opt.cnt_mhz);
        } else if (sim_common::starts_with(arg, "+debug-commit=")) {
            opt.debug_commit = sim_common::parse_u32(arg.substr(14), opt.debug_commit);
        } else if (sim_common::starts_with(arg, "+wave=")) {
            opt.wave = sim_common::parse_u32(arg.substr(6)) != 0;
        } else if (sim_common::starts_with(arg, "+wave-file=")) {
            opt.wave_path = arg.substr(11);
        }
    }
    if (opt.irom_path.empty()) {
        std::cerr << "error: missing +irom=<path>\n";
        std::exit(2);
    }
    if (opt.cpu_mhz == 0 || opt.cnt_mhz == 0) {
        std::cerr << "error: +cpu-mhz and +cnt-mhz must be nonzero\n";
        std::exit(2);
    }
    if (opt.wave && opt.wave_path.empty()) {
        opt.wave_path = "wave.vcd";
    }
    return opt;
}

sim_common::PerfStats core_perf(Vtb_rv32ui_top___024root* rootp) {
    sim_common::PerfStats stats;
    auto* perf = rootp->__PVT__tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__perfIF;
    stats.cycles = perf->cycle;
    stats.instret = perf->commitCnt;
    stats.branches = perf->branchCnt;
    stats.branch_miss = perf->branchMissCnt;
    return stats;
}

bool soc_perip_wen(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_wen;
}

uint32_t soc_perip_addr(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_addr;
}

uint32_t soc_perip_wdata(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_wdata;
}

void observe_pc(const Meta& meta, TestStatus& status, uint32_t pc);

void observe_commit_pc(const Meta& meta, TestStatus& status, Vtb_rv32ui_top___024root* rootp) {
    auto* commit = rootp->__PVT__tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__cmStageIF;
    auto* ctrl = rootp->__PVT__tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__ctrlIF;
    for (int lane = 0; lane < 2; ++lane) {
        if (commit->commitValid[lane]) {
            uint32_t pc = commit->commitPc[lane];
            status.last_pc = pc;
            observe_pc(meta, status, pc);
        }
    }
}

void print_commit_debug(const Options& opt, uint64_t cycle, Vtb_rv32ui_top___024root* rootp) {
    if (opt.debug_commit == 0 || cycle > opt.debug_commit) return;

    auto* commit = rootp->__PVT__tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__cmStageIF;
    auto* ctrl = rootp->__PVT__tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__ctrlIF;
    auto* bypass = rootp->__PVT__tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__bypassIF;
    bool any_commit = false;
    for (int lane = 0; lane < 2; ++lane) {
        any_commit |= commit->commitValid[lane];
    }
    bool late_loop_window = false;
    bool branch_debug_window = (cycle >= 130 && cycle <= 160) ||
                               (cycle >= 270 && cycle <= 300) ||
                               late_loop_window;
    if (!any_commit && cycle != opt.debug_commit && !branch_debug_window) return;

    std::cerr << "DBG cycle=" << cycle
              << " pcReg=0x" << std::hex << std::setw(8) << std::setfill('0')
              << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__pc__DOT__pcReg
              << " mtvec=0x" << std::setw(8)
              << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__executeSysStage__DOT__mtvec
              << " mepc=0x" << std::setw(8)
              << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__executeSysStage__DOT__mepc
              << " mcause=0x" << std::setw(8)
              << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__executeSysStage__DOT__mcause
              << std::dec << std::setfill(' ');
    std::cerr << " robCount=" << static_cast<unsigned>(
                     rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__rob__DOT__count)
              << " rnStall=" << static_cast<unsigned>(ctrl->rnStallReq)
              << " rnEmpty=" << static_cast<unsigned>(ctrl->rnStageEmpty)
              << " serial=" << static_cast<unsigned>(ctrl->serialBlock)
              << " empty(ds/is/rr/ex/wb)="
              << static_cast<unsigned>(ctrl->dsStageEmpty)
              << static_cast<unsigned>(ctrl->isStageEmpty)
              << static_cast<unsigned>(ctrl->rrStageEmpty)
              << static_cast<unsigned>(ctrl->exStageEmpty)
              << static_cast<unsigned>(ctrl->wbStageEmpty);
    if (ctrl->rnStallReq || cycle == opt.debug_commit) {
        auto free_mask = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__freeList__DOT__freeMask;
        std::cerr << " rn[local=" << static_cast<unsigned>(
                         rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__renameStage__DOT__unnamedblk3__DOT__localStall)
                  << " res=" << static_cast<unsigned>(
                         rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__renameStage__DOT__unnamedblk3__DOT__resourceStall)
                  << " chk=" << static_cast<unsigned>(
                         rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__renameStage__DOT__unnamedblk3__DOT__chkptStall)
                  << " br=" << static_cast<unsigned>(
                         rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__renameStage__DOT__unnamedblk3__DOT__branchPresent)
                  << "/" << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__renameStage__DOT__unnamedblk3__DOT__branchCount
                  << " can=" << static_cast<unsigned>(
                         rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__renameStage__DOT__unnamedblk3__DOT__canRename)
                  << " free=" << __builtin_popcountll(free_mask)
                  << " chkpt=";
        for (int c = 0; c < 8; ++c) {
            std::cerr << static_cast<unsigned>(
                rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__freeList__DOT__chkptValid[c]);
        }
        std::cerr << "]";
    }
    if (late_loop_window || cycle == opt.debug_commit) {
        auto dump_lgc = [&](int lgc, const char* name) {
            uint32_t spr = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__specRAT__DOT__rat[lgc];
            uint32_t apr = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__archRAT__DOT__rat[lgc];
            std::cerr << " " << name << "[s" << spr
                      << "=0x" << std::hex << std::setw(8) << std::setfill('0')
                      << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__regFile__DOT__regs[spr]
                      << " a" << std::dec << apr
                      << "=0x" << std::hex << std::setw(8) << std::setfill('0')
                      << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__regFile__DOT__regs[apr]
                      << std::dec << std::setfill(' ') << "]";
        };
        dump_lgc(1, "ra");
        dump_lgc(4, "tp");
        dump_lgc(5, "t0");
        dump_lgc(6, "t1");
        dump_lgc(14, "a4");
    }
    if (cycle == opt.debug_commit) {
        auto rob_head = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__rob__DOT__head;
        auto rob_tail = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__rob__DOT__tail;
        std::cerr << " rob[head=" << static_cast<unsigned>(rob_head)
                  << " tail=" << static_cast<unsigned>(rob_tail) << "]";
        for (int r = 0; r < 16; ++r) {
            auto& entry = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__rob__DOT__entries[r];
            uint32_t pc = (entry[3] >> 2) | (entry[4] << 30);
            uint32_t valid = (entry[4] >> 3) & 1;
            uint32_t done = (entry[4] >> 2) & 1;
            if (valid) {
                std::cerr << " e" << r << "[pc=0x" << std::hex << std::setw(8)
                          << std::setfill('0') << pc << std::dec << std::setfill(' ')
                          << " d=" << done << "]";
            }
        }
        std::cerr << " iq";
        for (int q = 0; q < 16; ++q) {
            if (rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__issueQueue__DOT__valid[q]) {
                auto& payload = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__payload__DOT__entries[q];
                uint32_t payload_pc = (payload[2] >> 26) | ((payload[3] & 0x03ff'ffffU) << 6);
                auto& iqe = rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__issueQueue__DOT__entries[q];
                std::cerr << " q" << q << "[pc=0x" << std::hex << std::setw(8)
                          << std::setfill('0') << payload_pc
                          << " raw4=0x" << std::setw(8) << iqe[4]
                          << " raw3=0x" << std::setw(8) << iqe[3]
                          << " raw2=0x" << std::setw(8) << iqe[2]
                          << " raw1=0x" << std::setw(8) << iqe[1]
                          << " raw0=0x" << std::setw(8) << iqe[0]
                          << std::dec << std::setfill(' ') << "]";
            }
        }
    }
    if (branch_debug_window) {
        std::cerr << " brcA=0x" << std::hex << std::setw(8) << std::setfill('0')
                  << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__executeBrcStage__DOT__unnamedblk3__DOT__unnamedblk4__DOT__a
                  << " brcB=0x" << std::setw(8)
                  << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__executeBrcStage__DOT__unnamedblk3__DOT__unnamedblk4__DOT__b
                  << " rf19=0x" << std::setw(8)
                  << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__regFile__DOT__regs[19]
                  << std::dec << std::setfill(' ');
        for (int p = 0; p < 4; ++p) {
            uint32_t req = bypass->brcReadReq[p];
            uint64_t res = bypass->brcReadRes[p];
            std::cerr << " br" << p
                      << "[v=" << ((req >> 6) & 1)
                      << " pr=" << (req & 0x3f)
                      << " rf=0x" << std::hex << std::setw(8) << std::setfill('0')
                      << rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__regFile__DOT__regs[req & 0x3f]
                      << std::dec << std::setfill(' ')
                      << " hit=" << ((res >> 32) & 1)
                      << " data=0x" << std::hex << std::setw(8) << std::setfill('0')
                      << static_cast<uint32_t>(res)
                      << std::dec << std::setfill(' ') << "]";
        }
        for (int p = 0; p < 10; ++p) {
            uint64_t fwd = bypass->wbForward[p];
            if ((fwd >> 43) & 1) {
                std::cerr << " fwd" << p
                          << "[wr=" << ((fwd >> 42) & 1)
                          << " rd=" << ((fwd >> 36) & 0x3f)
                          << " data=0x" << std::hex << std::setw(8) << std::setfill('0')
                          << static_cast<uint32_t>((fwd >> 4) & 0xffff'ffffULL)
                          << std::dec << std::setfill(' ') << "]";
            }
        }
    }
    for (int lane = 0; lane < 2; ++lane) {
        if (commit->commitValid[lane]) {
            std::cerr << " c" << lane << "=0x" << std::hex << std::setw(8) << std::setfill('0')
                      << commit->commitPc[lane] << std::dec << std::setfill(' ');
        }
    }
    if (commit->commitException) {
        std::cerr << " commitException";
    }
    std::cerr << "\n";
}

uint32_t soc_seg_wdata(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__bridge_inst__DOT__seg_wdata;
}

uint32_t soc_counter_ms(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__bridge_inst__DOT__cnt_rdata;
}

uint32_t soc_counter_raw_ms(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms_bin;
}

uint32_t soc_counter_sub_ms(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
}

uint8_t seg7_encode(uint32_t digit) {
    switch (digit & 0xfu) {
        case 0x0: return 0x3f;
        case 0x1: return 0x06;
        case 0x2: return 0x5b;
        case 0x3: return 0x4f;
        case 0x4: return 0x66;
        case 0x5: return 0x6d;
        case 0x6: return 0x7d;
        case 0x7: return 0x07;
        case 0x8: return 0x7f;
        case 0x9: return 0x6f;
        case 0xa: return 0x77;
        case 0xb: return 0x7c;
        case 0xc: return 0x39;
        case 0xd: return 0x5e;
        case 0xe: return 0x79;
        case 0xf: return 0x71;
        default:  return 0x00;
    }
}

uint64_t pack_virtual_seg(uint32_t seg_wdata, bool high_phase) {
    uint8_t ans = high_phase ? 0xaa : 0x55;
    uint32_t d1 = high_phase ? ((seg_wdata >> 4) & 0xfu) : (seg_wdata & 0xfu);
    uint32_t d2 = high_phase ? ((seg_wdata >> 12) & 0xfu) : ((seg_wdata >> 8) & 0xfu);
    uint32_t d3 = high_phase ? ((seg_wdata >> 20) & 0xfu) : ((seg_wdata >> 16) & 0xfu);
    uint32_t d4 = high_phase ? ((seg_wdata >> 28) & 0xfu) : ((seg_wdata >> 24) & 0xfu);
    uint64_t out = 0;
    out |= static_cast<uint64_t>(seg7_encode(d1));
    out |= static_cast<uint64_t>(ans & 0x03u) << 8;
    out |= static_cast<uint64_t>(seg7_encode(d2)) << 10;
    out |= static_cast<uint64_t>((ans >> 2) & 0x03u) << 18;
    out |= static_cast<uint64_t>(seg7_encode(d3)) << 20;
    out |= static_cast<uint64_t>((ans >> 4) & 0x03u) << 28;
    out |= static_cast<uint64_t>(seg7_encode(d4)) << 30;
    out |= static_cast<uint64_t>((ans >> 6) & 0x03u) << 38;
    return out;
}

uint32_t bcd6(uint32_t value) {
    value %= 1000000u;
    uint32_t out = 0;
    for (int idx = 0; idx < 6; ++idx) {
        out |= (value % 10u) << (idx * 4);
        value /= 10u;
    }
    return out;
}

bool virtual_seg_matches(uint32_t seg_wdata, uint64_t virtual_seg) {
    uint64_t masked = virtual_seg & ((1ull << 40) - 1ull);
    return masked == pack_virtual_seg(seg_wdata, true) ||
           masked == pack_virtual_seg(seg_wdata, false);
}

bool src_test_seg_matches(const Meta& meta, uint32_t seg_wdata, uint32_t counter_ms) {
    if (meta.pass_tests == 0) return true;
    uint32_t expected_prefix = ((meta.pass_tests / 10u) << 28) | ((meta.pass_tests % 10u) << 24);
    uint32_t prefix_mask = 0xff000000u;
    uint32_t runtime_bcd = bcd6(counter_ms);
    return (seg_wdata & prefix_mask) == expected_prefix &&
           ((seg_wdata & 0x00ffffffu) == runtime_bcd);
}

bool has_src_test_seg_oracle(const Meta& meta) {
    return meta.suite == "src_test" && meta.seg_addr != 0 && meta.pass_tests != 0;
}

void observe_pc(const Meta& meta, TestStatus& status, uint32_t pc) {
    if (status.finished) return;
    if (meta.fail_pc != 0 && pc == meta.fail_pc) {
        status.finished = true;
        status.passed = false;
        return;
    }
    if (meta.pass_pc != 0 && pc == meta.pass_pc) {
        status.finished = true;
        status.passed = true;
        if (status.tohost_value == 0) status.tohost_value = 1;
    }
}

void observe_tohost_write(const Meta& meta, TestStatus& status, bool wen, uint32_t addr, uint32_t wdata) {
    if (status.finished || meta.tohost == 0 || !wen || addr != meta.tohost) return;
    status.tohost_value = wdata;
    if (wdata != 0) {
        status.finished = true;
        status.passed = (wdata == 1);
    }
}

void observe_led_write(const Meta& meta, TestStatus& status, bool wen, uint32_t addr, uint32_t wdata) {
    if (status.finished || meta.led_addr == 0 || !wen || addr != meta.led_addr) return;
    status.led_value = wdata;
    status.saw_led = true;
    if (meta.fail_led != 0 && wdata == meta.fail_led) {
        status.finished = true;
        status.passed = false;
        return;
    }
    if (meta.pass_led != 0 && wdata == meta.pass_led) {
        status.saw_led_pass = true;
        if (!has_src_test_seg_oracle(meta)) {
            status.finished = true;
            status.passed = true;
        }
    }
}

void observe_seg_write(const Meta& meta, TestStatus& status, bool wen, uint32_t addr, uint32_t wdata) {
    if (meta.seg_addr == 0 || !wen || addr != meta.seg_addr) return;
    status.seg_value = wdata;
    status.saw_seg = true;
}

void observe_perip_write(TestStatus& status, bool wen, uint32_t addr, uint32_t wdata) {
    if (!wen) return;
    status.saw_write = true;
    status.last_write_addr = addr;
    status.last_write_data = wdata;
}

void update_src_test_status(const Meta& meta, TestStatus& status, Vtb_rv32ui_top* top) {
    if (status.finished || !has_src_test_seg_oracle(meta)) return;
    status.seg_value = soc_seg_wdata(top->rootp);
    status.counter_ms = soc_counter_ms(top->rootp);
    status.counter_raw_ms = soc_counter_raw_ms(top->rootp);
    status.counter_sub_ms = soc_counter_sub_ms(top->rootp);
    status.virtual_seg = top->o_virtual_seg;
    status.seg_passed = src_test_seg_matches(meta, status.seg_value, status.counter_ms);
    status.virtual_seg_passed = virtual_seg_matches(status.seg_value, status.virtual_seg);
    if (!status.saw_led_pass) return;
    ++status.post_led_pass_cycles;
    if (status.seg_passed && status.virtual_seg_passed) {
        status.finished = true;
        status.passed = true;
    } else if (status.post_led_pass_cycles > 512) {
        status.finished = true;
        status.passed = false;
    }
}

}  // namespace

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Options opt = parse_args(argc, argv);
    Meta meta = load_meta(opt.meta_path);

    Vtb_rv32ui_top* top = new Vtb_rv32ui_top;
    VerilatedVcdC* trace = nullptr;
    if (opt.wave) {
        Verilated::traceEverOn(true);
        trace = new VerilatedVcdC;
        top->trace(trace, 99);
        trace->open(opt.wave_path.c_str());
    }

    uint64_t sim_time = 0;
    sim_common::PerfStats stats;
    TestStatus status;
    auto eval_dump = [&]() {
        top->eval();
        if (trace) trace->dump(sim_time);
        ++sim_time;
    };

    top->i_clk_50mhz = 0;
    top->i_cpu_clk = 0;
    top->i_rst = 1;
    top->i_virtual_key = meta.virtual_key;
    top->i_virtual_sw = (static_cast<uint64_t>(meta.virtual_sw_hi) << 32) | meta.virtual_sw_lo;
    eval_dump();

    uint64_t cpu_half_ps = 1000000ull / (2ull * opt.cpu_mhz);
    uint64_t cnt_half_ps = 1000000ull / (2ull * opt.cnt_mhz);
    if (cpu_half_ps == 0) cpu_half_ps = 1;
    if (cnt_half_ps == 0) cnt_half_ps = 1;
    uint64_t next_cpu_edge = cpu_half_ps;
    uint64_t next_cnt_edge = cnt_half_ps;

    for (int idx = 0; idx < 16; ++idx) {
        sim_time = next_cpu_edge < next_cnt_edge ? next_cpu_edge : next_cnt_edge;
        if (sim_time == next_cpu_edge) {
            top->i_cpu_clk = !top->i_cpu_clk;
            next_cpu_edge += cpu_half_ps;
        }
        if (sim_time == next_cnt_edge) {
            top->i_clk_50mhz = !top->i_clk_50mhz;
            next_cnt_edge += cnt_half_ps;
        }
        eval_dump();
    }
    top->i_rst = 0;

    while (!Verilated::gotFinish() && stats.cycles < opt.max_cycles && !status.finished) {
        sim_time = next_cpu_edge < next_cnt_edge ? next_cpu_edge : next_cnt_edge;
        bool cpu_edge = (sim_time == next_cpu_edge);
        bool cnt_edge = (sim_time == next_cnt_edge);
        bool cpu_rise = cpu_edge && !top->i_cpu_clk;
        bool sampled_perip_wen = false;
        uint32_t sampled_perip_addr = 0;
        uint32_t sampled_perip_wdata = 0;

        if (cpu_rise) {
            sampled_perip_wen = soc_perip_wen(top->rootp);
            sampled_perip_addr = soc_perip_addr(top->rootp);
            sampled_perip_wdata = soc_perip_wdata(top->rootp);
        }
        if (cpu_edge) {
            top->i_cpu_clk = !top->i_cpu_clk;
            next_cpu_edge += cpu_half_ps;
        }
        if (cnt_edge) {
            top->i_clk_50mhz = !top->i_clk_50mhz;
            next_cnt_edge += cnt_half_ps;
        }
        eval_dump();

        if (cpu_rise) {
            observe_perip_write(status, sampled_perip_wen, sampled_perip_addr, sampled_perip_wdata);
            observe_tohost_write(meta, status, sampled_perip_wen, sampled_perip_addr, sampled_perip_wdata);
            observe_seg_write(meta, status, sampled_perip_wen, sampled_perip_addr, sampled_perip_wdata);
            observe_led_write(meta, status, sampled_perip_wen, sampled_perip_addr, sampled_perip_wdata);
            update_src_test_status(meta, status, top);
            observe_commit_pc(meta, status, top->rootp);
            stats = core_perf(top->rootp);
            print_commit_debug(opt, stats.cycles, top->rootp);
        }
    }

    top->final();
    if (trace) {
        trace->close();
        delete trace;
    }

    bool has_oracle = (meta.tohost != 0) || (meta.pass_pc != 0) || (meta.fail_pc != 0) || (meta.led_addr != 0);
    bool pass = status.finished && status.passed;
    bool done_without_oracle = !has_oracle && meta.kind != "correctness" && stats.cycles >= opt.max_cycles;
    bool timeout = stats.cycles >= opt.max_cycles && !status.finished && (has_oracle || meta.kind == "correctness");

    const char* result = pass ? "PASS" : (done_without_oracle ? "DONE" : (timeout ? "TIMEOUT" : "FAIL"));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << result;
    if (!meta.suite.empty()) std::cout << " " << meta.suite;
    if (!meta.test_case.empty()) std::cout << "/" << meta.test_case;
    std::cout << "\n";
    sim_common::print_stats_line(std::cout, stats, "core");
    std::cout << "  clocks: cpu=" << opt.cpu_mhz << "MHz cnt=" << opt.cnt_mhz << "MHz\n";
    sim_common::print_branch_line(std::cout, stats);
    if (meta.tohost != 0) {
        std::cout << "  tohost: 0x" << std::hex << std::setw(8) << std::setfill('0') << status.tohost_value << std::dec << std::setfill(' ') << "\n";
    }
    if (meta.led_addr != 0) {
        std::cout << "  oracle: led addr=0x" << std::hex << std::setw(8) << std::setfill('0') << meta.led_addr
                  << " pass=0x" << std::setw(8) << meta.pass_led
                  << " fail=0x" << std::setw(8) << meta.fail_led << std::dec << std::setfill(' ') << "\n";
        if (status.saw_led) {
            std::cout << "  led: 0x" << std::hex << std::setw(8) << std::setfill('0') << status.led_value << std::dec << std::setfill(' ') << "\n";
        } else {
            std::cout << "  led: no write observed\n";
        }
    }
    if (has_src_test_seg_oracle(meta)) {
        std::cout << "  oracle: seg addr=0x" << std::hex << std::setw(8) << std::setfill('0') << meta.seg_addr
                  << " tests=" << std::dec << meta.pass_tests
                  << " counter_addr=0x" << std::hex << std::setw(8) << meta.cnt_addr << std::dec << std::setfill(' ') << "\n";
        std::cout << "  seg: wdata=0x" << std::hex << std::setw(8) << std::setfill('0') << status.seg_value
                  << " virtual=0x" << std::setw(10) << status.virtual_seg
                  << std::dec << std::setfill(' ')
                  << " counter_ms=" << status.counter_ms
                  << " raw_ms=" << status.counter_raw_ms
                  << " sub_ms_ticks=" << status.counter_sub_ms
                  << " core_ms_floor=" << ((stats.cycles * 1000ull) / (opt.cpu_mhz * 1000000ull))
                  << " instret_ideal_ms_floor=" << ((stats.instret * 1000ull) / (opt.cpu_mhz * 1000000ull))
                  << " seg_ok=" << (status.seg_passed ? "yes" : "no")
                  << " virtual_ok=" << (status.virtual_seg_passed ? "yes" : "no") << "\n";
    }
    if (!pass && !done_without_oracle) {
        std::cout << "  debug: last_pc=0x" << std::hex << std::setw(8) << std::setfill('0') << status.last_pc;
        if (status.saw_write) {
            std::cout << " last_write_addr=0x" << std::setw(8) << status.last_write_addr
                      << " last_write_data=0x" << std::setw(8) << status.last_write_data;
        } else {
            std::cout << " no_perip_write";
        }
        std::cout << std::dec << std::setfill(' ') << "\n";
    }

    delete top;
    if (pass || done_without_oracle) return 0;
    if (timeout) return 124;
    return 1;
}
