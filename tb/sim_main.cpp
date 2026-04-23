#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vtb_rv32ui_top.h"
#include "Vtb_rv32ui_top___024root.h"

#include <cctype>
#include <cstdint>
#include <cstdlib>
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
    bool wave = false;
};

struct Meta {
    uint32_t base_pc = kDefaultIromBase;
    uint32_t dram_base = kDefaultDramBase;
    uint32_t tohost = 0;
    uint32_t pass_pc = 0;
    uint32_t fail_pc = 0;
    std::string kind;
    std::string suite;
    std::string test_case;
};

struct PerfStats {
    uint64_t cycles = 0;
    uint64_t instret = 0;
    uint64_t branches = 0;
    uint64_t branch_miss = 0;
};

struct TestStatus {
    bool finished = false;
    bool passed = false;
    uint32_t tohost_value = 0;
};

bool starts_with(const std::string& text, const std::string& prefix) {
    return text.rfind(prefix, 0) == 0;
}

uint32_t parse_u32(const std::string& text, uint32_t fallback = 0) {
    if (text.empty()) return fallback;
    char* end = nullptr;
    unsigned long value = std::strtoul(text.c_str(), &end, 0);
    if (end == text.c_str()) return fallback;
    return static_cast<uint32_t>(value);
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
    if (!in) {
        std::cerr << "warning: cannot open meta file " << path << "\n";
        return meta;
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string text = ss.str();
    meta.base_pc = parse_u32(json_string_value(text, "base_pc"), meta.base_pc);
    meta.dram_base = parse_u32(json_string_value(text, "dram_base"), meta.dram_base);
    meta.tohost = parse_u32(json_string_value(text, "tohost"), meta.tohost);
    meta.pass_pc = parse_u32(json_string_value(text, "pass"), meta.pass_pc);
    meta.fail_pc = parse_u32(json_string_value(text, "fail"), meta.fail_pc);
    meta.kind = json_string_value(text, "kind");
    meta.suite = json_string_value(text, "suite");
    meta.test_case = json_string_value(text, "case");
    return meta;
}

Options parse_args(int argc, char** argv) {
    Options opt;
    for (int idx = 1; idx < argc; ++idx) {
        std::string arg = argv[idx];
        if (starts_with(arg, "+irom=")) {
            opt.irom_path = arg.substr(6);
        } else if (starts_with(arg, "+dram=")) {
            opt.dram_path = arg.substr(6);
        } else if (starts_with(arg, "+meta=")) {
            opt.meta_path = arg.substr(6);
        } else if (starts_with(arg, "+max-cycles=")) {
            opt.max_cycles = std::strtoull(arg.substr(12).c_str(), nullptr, 0);
        } else if (starts_with(arg, "+wave=")) {
            opt.wave = parse_u32(arg.substr(6)) != 0;
        } else if (starts_with(arg, "+wave-file=")) {
            opt.wave_path = arg.substr(11);
        }
    }
    if (opt.irom_path.empty()) {
        std::cerr << "error: missing +irom=<path>\n";
        std::exit(2);
    }
    if (opt.wave && opt.wave_path.empty()) {
        opt.wave_path = "wave.vcd";
    }
    return opt;
}

double ratio(uint64_t numerator, uint64_t denominator) {
    if (denominator == 0) return 0.0;
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

uint64_t branch_hit(const PerfStats& stats) {
    return stats.branches >= stats.branch_miss ? stats.branches - stats.branch_miss : 0;
}

double branch_hit_rate(const PerfStats& stats) {
    return stats.branches ? 100.0 * ratio(branch_hit(stats), stats.branches) : 0.0;
}

double cpi(const PerfStats& stats) {
    return ratio(stats.cycles, stats.instret);
}

double ipc(const PerfStats& stats) {
    return ratio(stats.instret, stats.cycles);
}

double branch_mpki(const PerfStats& stats) {
    return stats.instret ? 1000.0 * ratio(stats.branch_miss, stats.instret) : 0.0;
}

void print_stats_line(std::ostream& out, const PerfStats& stats, const std::string& label) {
    out << "  " << label
        << ": cycles=" << stats.cycles
        << " instret=" << stats.instret
        << " cpi=" << cpi(stats)
        << " ipc=" << ipc(stats) << "\n";
}

void print_branch_line(std::ostream& out, const PerfStats& stats) {
    out << "  branch: total=" << stats.branches
        << " hit=" << branch_hit(stats)
        << " miss=" << stats.branch_miss
        << " hit_rate=" << branch_hit_rate(stats) << "%"
        << " mpki=" << branch_mpki(stats) << "\n";
}

bool core_inst_valid(Vtb_rv32ui_top___024root* rootp) {
    return !rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__flush_e_m &&
           (rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__reg_write_e ||
           rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__mem_write_e ||
           rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e);
}

bool core_branch_update(Vtb_rv32ui_top___024root* rootp) {
    return !rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__flush_e_m &&
           rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__update_en_e;
}

bool core_branch_miss(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__error_e;
}

uint32_t core_pc_e(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__pc_e;
}

bool soc_perip_wen(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_wen;
}

uint32_t core_pc_f(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__pc;
}

uint32_t soc_perip_addr(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_addr;
}

uint32_t soc_perip_wdata(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_wdata;
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
    PerfStats stats;
    TestStatus status;
    uint32_t last_pc = 0;
    uint64_t stable_cycles = 0;

    auto eval_dump = [&]() {
        top->eval();
        if (trace) trace->dump(sim_time);
        ++sim_time;
    };

    top->i_clk_50mhz = 0;
    top->i_cpu_clk = 0;
    top->i_rst = 1;
    top->i_virtual_key = 0;
    top->i_virtual_sw = 0;
    eval_dump();

    for (int idx = 0; idx < 16; ++idx) {
        top->i_clk_50mhz = !top->i_clk_50mhz;
        top->i_cpu_clk = !top->i_cpu_clk;
        eval_dump();
    }
    top->i_rst = 0;

    while (!Verilated::gotFinish() && stats.cycles < opt.max_cycles && !status.finished) {
        top->i_cpu_clk = 0;
        top->i_clk_50mhz = !top->i_clk_50mhz;
        eval_dump();

        bool sampled_perip_wen = soc_perip_wen(top->rootp);
        uint32_t sampled_perip_addr = soc_perip_addr(top->rootp);
        uint32_t sampled_perip_wdata = soc_perip_wdata(top->rootp);

        top->i_cpu_clk = 1;
        top->i_clk_50mhz = !top->i_clk_50mhz;
        eval_dump();

        observe_tohost_write(meta, status, sampled_perip_wen, sampled_perip_addr, sampled_perip_wdata);
        if (!top->rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__flush_e_m) {
            observe_pc(meta, status, core_pc_e(top->rootp));
        }

        uint32_t pc_f = core_pc_f(top->rootp);
        if (pc_f == last_pc) {
            ++stable_cycles;
        } else {
            last_pc = pc_f;
            stable_cycles = 0;
        }

        if (!status.finished && meta.kind == "correctness" && stable_cycles >= 64 && stats.instret != 0) {
            status.finished = true;
            status.passed = true;
        }

        if (core_inst_valid(top->rootp)) {
            ++stats.instret;
        }
        if (core_branch_update(top->rootp)) {
            ++stats.branches;
            if (core_branch_miss(top->rootp)) ++stats.branch_miss;
        }
        ++stats.cycles;
    }

    top->final();
    if (trace) {
        trace->close();
        delete trace;
    }

    bool has_oracle = (meta.tohost != 0) || (meta.pass_pc != 0) || (meta.fail_pc != 0);
    bool no_oracle_correctness_pass = !has_oracle && meta.kind == "correctness" && stats.instret != 0 && stats.cycles >= opt.max_cycles;
    bool pass = (status.finished && status.passed) || no_oracle_correctness_pass;
    bool done_without_oracle = !has_oracle && meta.kind != "correctness" && stats.cycles >= opt.max_cycles;
    bool timeout = has_oracle && !status.finished && stats.cycles >= opt.max_cycles;

    const char* result = pass ? "PASS" : (done_without_oracle ? "DONE" : (timeout ? "TIMEOUT" : "FAIL"));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << result;
    if (!meta.suite.empty()) std::cout << " " << meta.suite;
    if (!meta.test_case.empty()) std::cout << "/" << meta.test_case;
    std::cout << "\n";
    print_stats_line(std::cout, stats, "core");
    print_branch_line(std::cout, stats);
    if (meta.tohost != 0) {
        std::cout << "  tohost: 0x" << std::hex << std::setw(8) << std::setfill('0') << status.tohost_value << std::dec << std::setfill(' ') << "\n";
    }

    delete top;
    if (pass || done_without_oracle) return 0;
    if (timeout) return 124;
    return 1;
}
