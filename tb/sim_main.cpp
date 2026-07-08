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
    uint32_t cpu_mhz = 200;
    uint32_t cnt_mhz = 50;
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
    meta.led_addr = parse_u32(json_string_value(text, "led_addr"), meta.led_addr);
    meta.pass_led = parse_u32(json_string_value(text, "pass_led"), meta.pass_led);
    meta.fail_led = parse_u32(json_string_value(text, "fail_led"), meta.fail_led);
    meta.seg_addr = parse_u32(json_string_value(text, "seg_addr"), meta.seg_addr);
    meta.cnt_addr = parse_u32(json_string_value(text, "cnt_addr"), meta.cnt_addr);
    meta.pass_tests = parse_u32(json_string_value(text, "pass_tests"), meta.pass_tests);
    meta.virtual_sw_lo = parse_u32(json_string_value(text, "virtual_sw_lo"), meta.virtual_sw_lo);
    meta.virtual_sw_hi = parse_u32(json_string_value(text, "virtual_sw_hi"), meta.virtual_sw_hi);
    meta.virtual_key = parse_u32(json_string_value(text, "virtual_key"), meta.virtual_key);
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
        } else if (starts_with(arg, "+cpu-mhz=")) {
            opt.cpu_mhz = parse_u32(arg.substr(9), opt.cpu_mhz);
        } else if (starts_with(arg, "+cnt-mhz=")) {
            opt.cnt_mhz = parse_u32(arg.substr(9), opt.cnt_mhz);
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
    if (opt.cpu_mhz == 0 || opt.cnt_mhz == 0) {
        std::cerr << "error: +cpu-mhz and +cnt-mhz must be nonzero\n";
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
           !rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__ex_stall_e &&
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

uint32_t soc_perip_addr(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_addr;
}

uint32_t soc_perip_wdata(Vtb_rv32ui_top___024root* rootp) {
    return rootp->tb_rv32ui_top__DOT__u_dut__DOT__perip_wdata;
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
    PerfStats stats;
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
            if (!top->rootp->tb_rv32ui_top__DOT__u_dut__DOT__Core_cpu__DOT__u_core__DOT__flush_e_m) {
                uint32_t pc_e = core_pc_e(top->rootp);
                status.last_pc = pc_e;
                observe_pc(meta, status, pc_e);
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
    print_stats_line(std::cout, stats, "core");
    std::cout << "  clocks: cpu=" << opt.cpu_mhz << "MHz cnt=" << opt.cnt_mhz << "MHz\n";
    print_branch_line(std::cout, stats);
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
