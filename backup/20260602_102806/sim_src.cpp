#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vtb_src_top.h"
#include "Vtb_src_top___024root.h"
#include "sim_common.hpp"

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace {

struct Options {
    std::string meta_path;
    std::string wave_path;
    uint64_t max_cpu_cycles = 1000000;
    uint64_t stable_cpu_cycles = 64;
    uint32_t cpu_mhz = 200;
    uint32_t cnt_mhz = 50;
    uint32_t run_ms = 0;
    bool wave = false;
    bool fast_counter = false;
    bool strict_sim_limit = false;
};

struct Meta {
    std::string suite;
    std::string test_case;
};

Meta load_meta(const std::string& path) {
    Meta meta;
    if (path.empty()) return meta;
    std::ifstream in(path);
    if (!in) return meta;
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string text = ss.str();
    meta.suite = sim_common::json_string_value(text, "suite");
    meta.test_case = sim_common::json_string_value(text, "case");
    return meta;
}

Options parse_args(int argc, char** argv) {
    Options opt;
    for (int idx = 1; idx < argc; ++idx) {
        std::string arg = argv[idx];
        if (sim_common::starts_with(arg, "+meta=")) {
            opt.meta_path = arg.substr(6);
        } else if (sim_common::starts_with(arg, "+max-cycles=")) {
            opt.max_cpu_cycles = sim_common::parse_u64(arg.substr(12), opt.max_cpu_cycles);
        } else if (sim_common::starts_with(arg, "+stable-cycles=")) {
            opt.stable_cpu_cycles = sim_common::parse_u64(arg.substr(15), opt.stable_cpu_cycles);
        } else if (sim_common::starts_with(arg, "+cpu-mhz=")) {
            opt.cpu_mhz = sim_common::parse_u32(arg.substr(9), opt.cpu_mhz);
        } else if (sim_common::starts_with(arg, "+cnt-mhz=")) {
            opt.cnt_mhz = sim_common::parse_u32(arg.substr(9), opt.cnt_mhz);
        } else if (sim_common::starts_with(arg, "+run-ms=")) {
            opt.run_ms = static_cast<uint32_t>(sim_common::parse_u64(arg.substr(8), opt.run_ms));
        } else if (sim_common::starts_with(arg, "+wave=")) {
            opt.wave = sim_common::parse_u64(arg.substr(6), 0) != 0;
        } else if (sim_common::starts_with(arg, "+wave-file=")) {
            opt.wave_path = arg.substr(11);
        } else if (sim_common::starts_with(arg, "+fast-counter=")) {
            opt.fast_counter = sim_common::parse_u64(arg.substr(14), 0) != 0;
        } else if (sim_common::starts_with(arg, "+strict-sim-limit=")) {
            opt.strict_sim_limit = sim_common::parse_u64(arg.substr(18), 0) != 0;
        }
    }
    if (opt.cpu_mhz == 0 || opt.cnt_mhz == 0) {
        std::cerr << "error: +cpu-mhz and +cnt-mhz must be nonzero\n";
        std::exit(2);
    }
    if (opt.wave && opt.wave_path.empty()) {
        opt.wave_path = "src_wave.vcd";
    }
    return opt;
}

bool core_inst_valid(Vtb_src_top___024root* rootp) {
    return rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e ||
           rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_e ||
           rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e;
}

bool core_branch_update(Vtb_src_top___024root* rootp) {
    return rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e;
}

bool core_branch_miss(Vtb_src_top___024root* rootp) {
    return rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__error_e;
}

uint32_t core_pc_e(Vtb_src_top___024root* rootp) {
    return rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e;
}

bool counter_start(Vtb_src_top___024root* rootp) {
    return rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__cnt_enable_cfg;
}

uint32_t counter_ms(Vtb_src_top___024root* rootp) {
    return rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__cnt_rdata;
}

}  // namespace

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Options opt = parse_args(argc, argv);
    Meta meta = load_meta(opt.meta_path);

    Vtb_src_top* top = new Vtb_src_top;
    VerilatedVcdC* trace = nullptr;
    if (opt.wave) {
        Verilated::traceEverOn(true);
        trace = new VerilatedVcdC;
        top->trace(trace, 99);
        trace->open(opt.wave_path.c_str());
    }

    uint64_t sim_time = 0;
    sim_common::PerfStats total_stats;
    sim_common::PerfStats work_stats;
    uint64_t stable_loops = 0;
    uint64_t counter_stop_cpu_cycle = 0;
    uint32_t last_pc = 0;
    bool last_counter_start = false;
    bool counter_started = false;
    bool counter_stopped = false;
    bool run_ms_reached = false;

    auto eval_dump = [&]() {
        top->eval();
        if (trace) trace->dump(sim_time);
    };

    auto accelerate_counter = [&]() {
        if (!opt.fast_counter) return;
        if (top->i_rst) return;
        if (!counter_start(top->rootp)) return;
        top->rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 49999;
    };

    top->i_clk_50mhz = 0;
    top->i_cpu_clk = 0;
    top->i_rst = 1;
    top->i_virtual_key = 0;
    top->i_virtual_sw = 0;
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

    while (!Verilated::gotFinish() && total_stats.cycles < opt.max_cpu_cycles) {
        sim_time = next_cpu_edge < next_cnt_edge ? next_cpu_edge : next_cnt_edge;
        bool cpu_edge = (sim_time == next_cpu_edge);
        bool cnt_edge = (sim_time == next_cnt_edge);
        bool cpu_rise = cpu_edge && !top->i_cpu_clk;
        bool cnt_rise = cnt_edge && !top->i_clk_50mhz;

        if (cnt_rise) {
            accelerate_counter();
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
            bool counter_active = counter_start(top->rootp);
            uint32_t pc = core_pc_e(top->rootp);
            bool inst_valid = core_inst_valid(top->rootp);

            ++total_stats.cycles;
            if (inst_valid) {
                ++total_stats.instret;
            }
            if (core_branch_update(top->rootp)) {
                ++total_stats.branches;
                if (core_branch_miss(top->rootp)) ++total_stats.branch_miss;
            }

            if (counter_active) {
                ++work_stats.cycles;
                if (inst_valid) {
                    ++work_stats.instret;
                }
                if (core_branch_update(top->rootp)) {
                    ++work_stats.branches;
                    if (core_branch_miss(top->rootp)) ++work_stats.branch_miss;
                }
            }

            if (counter_active) {
                counter_started = true;
            }
            if (last_counter_start && !counter_active) {
                counter_stopped = true;
                counter_stop_cpu_cycle = total_stats.cycles;
            }
            last_counter_start = counter_active;

            uint32_t cnt_ms = counter_ms(top->rootp);
            if (counter_started && opt.run_ms != 0 && cnt_ms >= opt.run_ms) {
                run_ms_reached = true;
            }

            if (pc == last_pc) {
                ++stable_loops;
            } else {
                stable_loops = 0;
                last_pc = pc;
            }

            if (run_ms_reached || (counter_stopped && stable_loops >= opt.stable_cpu_cycles)) {
                break;
            }
        }
    }

    top->final();
    if (trace) {
        trace->close();
        delete trace;
    }

    uint32_t time_ms = counter_ms(top->rootp);

    bool stopped_and_stable = counter_stopped && stable_loops >= opt.stable_cpu_cycles;
    bool protected_limit = total_stats.cycles >= opt.max_cpu_cycles && !run_ms_reached && !stopped_and_stable;
    bool complete = stopped_and_stable;
    bool sampled = (run_ms_reached || protected_limit) && work_stats.instret != 0;

    const char* result = protected_limit ? "SIM_LIMIT" : "DONE";
    const char* reason = run_ms_reached ? "time_reached" : (stopped_and_stable ? "counter_stopped" : "sim_limit");

    std::cout << std::fixed << std::setprecision(2);
    std::cout << result;
    if (!meta.suite.empty()) std::cout << " " << meta.suite;
    if (!meta.test_case.empty()) std::cout << "/" << meta.test_case;
    std::cout << "\n"
              << "  status: reason=" << reason
              << " complete=" << (complete ? "yes" : "no")
              << " sampled=" << (sampled ? "yes" : "no")
              << " counter=" << (counter_started ? (counter_stopped ? "stopped" : "running") : "not_started")
              << "\n"
              << "  time: elapsed_ms=" << time_ms
              << " target_ms=" << opt.run_ms
              << " scale=" << (opt.fast_counter ? "fast" : "real")
              << " strict_limit=" << (opt.strict_sim_limit ? "yes" : "no") << "\n";
    std::cout << "  clocks: cpu=" << opt.cpu_mhz << "MHz cnt=" << opt.cnt_mhz << "MHz\n";
    if (counter_stopped) {
        std::cout << "  stop: cycle=" << counter_stop_cpu_cycle << "\n";
    }
    if (work_stats.instret != 0) {
        sim_common::print_perf_block(std::cout, work_stats, "work");
        sim_common::print_perf_summary(std::cout, total_stats, "total");
    } else {
        sim_common::print_perf_block(std::cout, total_stats, "total");
        std::cout << "  work: no valid sample\n";
    }

    delete top;
    return (protected_limit && opt.strict_sim_limit) ? 124 : 0;
}
