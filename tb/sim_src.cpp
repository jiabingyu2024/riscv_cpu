#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vtb_src_top.h"
#include "Vtb_src_top___024root.h"

#include <cctype>
#include <cstdint>
#include <cstdlib>
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
    uint32_t run_ms = 0;
    bool wave = false;
    bool fast_counter = false;
    bool strict_sim_limit = false;
};

struct Meta {
    std::string suite;
    std::string test_case;
};

bool starts_with(const std::string& text, const std::string& prefix) {
    return text.rfind(prefix, 0) == 0;
}

uint64_t parse_u64(const std::string& text, uint64_t fallback = 0) {
    if (text.empty()) return fallback;
    char* end = nullptr;
    unsigned long long value = std::strtoull(text.c_str(), &end, 0);
    if (end == text.c_str()) return fallback;
    return static_cast<uint64_t>(value);
}

std::string json_string_value(const std::string& text, const std::string& key) {
    const std::string needle = "\"" + key + "\"";
    size_t pos = text.find(needle);
    if (pos == std::string::npos) return "";
    pos = text.find(':', pos + needle.size());
    if (pos == std::string::npos) return "";
    pos = text.find('"', pos + 1);
    if (pos == std::string::npos) return "";
    size_t end = text.find('"', pos + 1);
    if (end == std::string::npos) return "";
    return text.substr(pos + 1, end - pos - 1);
}

Meta load_meta(const std::string& path) {
    Meta meta;
    if (path.empty()) return meta;
    std::ifstream in(path);
    if (!in) return meta;
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string text = ss.str();
    meta.suite = json_string_value(text, "suite");
    meta.test_case = json_string_value(text, "case");
    return meta;
}

Options parse_args(int argc, char** argv) {
    Options opt;
    for (int idx = 1; idx < argc; ++idx) {
        std::string arg = argv[idx];
        if (starts_with(arg, "+meta=")) {
            opt.meta_path = arg.substr(6);
        } else if (starts_with(arg, "+max-cycles=")) {
            opt.max_cpu_cycles = parse_u64(arg.substr(12), opt.max_cpu_cycles);
        } else if (starts_with(arg, "+stable-cycles=")) {
            opt.stable_cpu_cycles = parse_u64(arg.substr(15), opt.stable_cpu_cycles);
        } else if (starts_with(arg, "+run-ms=")) {
            opt.run_ms = static_cast<uint32_t>(parse_u64(arg.substr(8), opt.run_ms));
        } else if (starts_with(arg, "+wave=")) {
            opt.wave = parse_u64(arg.substr(6), 0) != 0;
        } else if (starts_with(arg, "+wave-file=")) {
            opt.wave_path = arg.substr(11);
        } else if (starts_with(arg, "+fast-counter=")) {
            opt.fast_counter = parse_u64(arg.substr(14), 0) != 0;
        } else if (starts_with(arg, "+strict-sim-limit=")) {
            opt.strict_sim_limit = parse_u64(arg.substr(18), 0) != 0;
        }
    }
    if (opt.wave && opt.wave_path.empty()) {
        opt.wave_path = "src_wave.vcd";
    }
    return opt;
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

    uint64_t sim_ticks = 0;
    uint64_t cpu_cycles = 0;
    uint64_t branch_total = 0;
    uint64_t branch_miss = 0;
    uint64_t stable_loops = 0;
    uint64_t counter_stop_cpu_cycle = 0;
    uint32_t last_pc = 0;
    bool last_counter_start = false;
    bool counter_started = false;
    bool counter_stopped = false;
    bool run_ms_reached = false;

    auto eval_dump = [&]() {
        top->eval();
        if (trace) trace->dump(sim_ticks);
        ++sim_ticks;
    };

    auto accelerate_counter = [&]() {
        if (!opt.fast_counter) return;
        if (top->i_rst) return;
        if (!top->rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__start) return;
        top->rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 49999;
    };

    top->i_clk_50mhz = 0;
    top->i_cpu_clk = 0;
    top->i_rst = 1;
    top->i_virtual_key = 0;
    top->i_virtual_sw = 0;
    eval_dump();

    for (int idx = 0; idx < 32; ++idx) {
        if ((idx % 2) == 0) {
            top->i_clk_50mhz = !top->i_clk_50mhz;
        }
        top->i_cpu_clk = !top->i_cpu_clk;
        eval_dump();
    }
    top->i_rst = 0;

    while (!Verilated::gotFinish() && cpu_cycles < opt.max_cpu_cycles) {
        for (int substep = 0; substep < 4; ++substep) {
            if ((substep == 0 || substep == 2) && top->i_clk_50mhz == 0) {
                accelerate_counter();
            }
            if (substep == 0 || substep == 2) {
                top->i_clk_50mhz = !top->i_clk_50mhz;
            }
            top->i_cpu_clk = !top->i_cpu_clk;
            eval_dump();

            if (substep == 0 || substep == 2) {
                bool counter_start = top->rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__start;
                uint32_t pc = top->rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e;

                if (top->rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e) {
                    ++branch_total;
                    if (top->rootp->tb_src_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__error_e) {
                        ++branch_miss;
                    }
                }

                if (counter_start) {
                    counter_started = true;
                }
                if (last_counter_start && !counter_start) {
                    counter_stopped = true;
                    counter_stop_cpu_cycle = cpu_cycles;
                }
                last_counter_start = counter_start;

                uint32_t cnt_ms = top->rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
                if (counter_started && opt.run_ms != 0 && cnt_ms >= opt.run_ms) {
                    run_ms_reached = true;
                }

                if (pc == last_pc) {
                    ++stable_loops;
                } else {
                    stable_loops = 0;
                    last_pc = pc;
                }

                ++cpu_cycles;
            }
        }

        if (run_ms_reached || (counter_stopped && stable_loops >= opt.stable_cpu_cycles)) {
            break;
        }
    }

    top->final();
    if (trace) {
        trace->close();
        delete trace;
    }

    uint32_t time_ms = top->rootp->tb_src_top__DOT__u_dut__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    uint64_t branch_hit = branch_total >= branch_miss ? branch_total - branch_miss : 0;
    double hit_rate = branch_total ? (100.0 * static_cast<double>(branch_hit) / static_cast<double>(branch_total)) : 0.0;

    bool stopped_and_stable = counter_stopped && stable_loops >= opt.stable_cpu_cycles;
    bool protected_limit = cpu_cycles >= opt.max_cpu_cycles && !run_ms_reached && !stopped_and_stable;
    std::cout << (protected_limit ? "SIM_LIMIT" : "DONE");
    if (!meta.suite.empty()) std::cout << " suite=" << meta.suite;
    if (!meta.test_case.empty()) std::cout << " case=" << meta.test_case;
    std::cout << " time_ms=" << time_ms
              << " run_ms=" << opt.run_ms
              << " cycles=" << cpu_cycles
              << " reason=" << (run_ms_reached ? "time_reached" : (stopped_and_stable ? "counter_stopped" : "sim_limit"))
              << " counter_scale=" << (opt.fast_counter ? "fast" : "real")
              << " strict_sim_limit=" << (opt.strict_sim_limit ? 1 : 0)
              << " counter_started=" << (counter_started ? 1 : 0)
              << " counter_stopped=" << (counter_stopped ? 1 : 0);
    if (counter_stopped) {
        std::cout << " counter_stop_cycle=" << counter_stop_cpu_cycle;
    }
    std::cout << " branches=" << branch_total
              << " hit=" << branch_hit
              << " miss=" << branch_miss
              << " hit_rate=" << std::fixed << std::setprecision(2) << hit_rate << "%\n";

    delete top;
    return (protected_limit && opt.strict_sim_limit) ? 124 : 0;
}
