#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string_view>
#include <string>

#include "tb_config.h"
#include "Vcore_top.h"
#include "verilated.h"
#include "verilated_fst_c.h"

namespace {

uint64_t g_main_time = 0;

double sc_time_stamp() {
    return static_cast<double>(g_main_time);
}

std::string get_string_plusarg(int argc, char** argv, const std::string& key) {
    const std::string prefix = "+" + key + "=";
    const std::string flag = "+" + key;

    for (int i = 1; i < argc; ++i) {
        const std::string_view arg(argv[i]);
        if (arg == flag) {
            return "1";
        }
        if (arg.rfind(prefix, 0) == 0) {
            return std::string(arg.substr(prefix.size()));
        }
    }
    return "";
}

uint64_t parse_u64(const std::string& text, uint64_t default_value) {
    if (text.empty()) {
        return default_value;
    }
    return std::stoull(text, nullptr, 0);
}

void tick(Vcore_top* top, VerilatedFstC* trace) {
    top->clk = 0;
    top->eval();
    if (trace != nullptr) {
        trace->dump(g_main_time);
    }
    ++g_main_time;

    top->clk = 1;
    top->eval();
    if (trace != nullptr) {
        trace->dump(g_main_time);
    }
    ++g_main_time;
}

}  // namespace

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    std::unique_ptr<Vcore_top> top = std::make_unique<Vcore_top>();

    const std::string wave_path = get_string_plusarg(argc, argv, "WAVE");
    const uint64_t max_cycles = parse_u64(get_string_plusarg(argc, argv, "MAX_CYCLES"), kDefaultMaxCycles);
    const uint64_t pass_pc = parse_u64(get_string_plusarg(argc, argv, "PASS_PC"), UINT64_MAX);
    const uint64_t fail_pc = parse_u64(get_string_plusarg(argc, argv, "FAIL_PC"), UINT64_MAX);
    const std::string trace_arg = get_string_plusarg(argc, argv, "TRACE");
    const bool enable_trace = !wave_path.empty() && !trace_arg.empty() && trace_arg != "0";

    std::unique_ptr<VerilatedFstC> trace;

    if (enable_trace) {
        std::filesystem::create_directories(std::filesystem::path(wave_path).parent_path());
        trace = std::make_unique<VerilatedFstC>();
        top->trace(trace.get(), 99);
        trace->open(wave_path.c_str());
    }

    top->rst_n = 0;
    top->clk = 0;

    for (int i = 0; i < kResetCycles; ++i) {
        tick(top.get(), trace.get());
    }

    top->rst_n = 1;

    for (uint64_t cycle = 0; cycle < max_cycles; ++cycle) {
        tick(top.get(), trace.get());

        const uint64_t pc = static_cast<uint64_t>(top->o_dbg_pc);

        if (fail_pc != UINT64_MAX && pc == fail_pc) {
            std::cerr << "FAIL_PC reached at cycle " << cycle
                      << ", pc=0x" << std::hex << pc << std::dec << std::endl;
            if (trace != nullptr) {
                trace->close();
            }
            top->final();
            return 1;
        }

        if (pass_pc != UINT64_MAX && pc == pass_pc) {
            std::cout << "PASS_PC reached at cycle " << cycle
                      << ", pc=0x" << std::hex << pc << std::dec << std::endl;
            if (trace != nullptr) {
                trace->close();
            }
            top->final();
            return 0;
        }
    }

    std::cerr << "TIMEOUT after " << max_cycles << " cycles"
              << ", last pc=0x" << std::hex << static_cast<uint64_t>(top->o_dbg_pc)
              << std::dec << std::endl;

    if (trace != nullptr) {
        trace->close();
    }
    top->final();
    return 2;
}
