#include <verilated.h>
#include <verilated_vcd_c.h>

#include "VmyCPU.h"
#include "VmyCPU___024root.h"

#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace {

constexpr uint32_t kDefaultIromBase = 0x80000000u;
constexpr uint32_t kDefaultDramBase = 0x80100000u;
constexpr uint8_t kMaskByte = 0;
constexpr uint8_t kMaskHalf = 1;
constexpr uint8_t kMaskWord = 2;

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
    std::string suite;
    std::string test_case;
};

std::string trim(const std::string& input) {
    size_t first = 0;
    while (first < input.size() && std::isspace(static_cast<unsigned char>(input[first]))) ++first;
    size_t last = input.size();
    while (last > first && std::isspace(static_cast<unsigned char>(input[last - 1]))) --last;
    return input.substr(first, last - first);
}

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
    meta.suite = json_string_value(text, "suite");
    meta.test_case = json_string_value(text, "case");
    return meta;
}

std::vector<uint32_t> load_hex_words(const std::string& path) {
    std::vector<uint32_t> words;
    if (path.empty()) return words;
    std::ifstream in(path);
    if (!in) {
        std::cerr << "error: cannot open hex file " << path << "\n";
        std::exit(2);
    }
    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        words.push_back(parse_u32("0x" + line));
    }
    return words;
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

class MemoryModel {
public:
    explicit MemoryModel(const Meta& meta) : meta_(meta) {}

    void load_irom(const std::vector<uint32_t>& words) {
        irom_ = words;
        uint32_t addr = meta_.base_pc;
        for (uint32_t word : words) {
            data_words_[addr] = word;
            addr += 4;
        }
    }

    void load_dram(const std::vector<uint32_t>& words) {
        uint32_t addr = meta_.dram_base;
        for (uint32_t word : words) {
            data_words_[addr] = word;
            addr += 4;
        }
    }

    uint32_t read_irom(uint32_t addr) const {
        if (addr < meta_.base_pc) return 0x00000013u;
        uint64_t index = (static_cast<uint64_t>(addr) - meta_.base_pc) >> 2;
        if (index >= irom_.size()) return 0x00000013u;
        return irom_[static_cast<size_t>(index)];
    }

    uint32_t read_data(uint32_t addr, uint8_t mask) const {
        auto mmio = mmio_words_.find(addr);
        if (mmio != mmio_words_.end()) return mmio->second;

        uint32_t word_addr = addr & ~3u;
        uint32_t word = 0;
        auto it = data_words_.find(word_addr);
        if (it != data_words_.end()) word = it->second;

        uint32_t offset = addr & 3u;
        if (mask == kMaskByte) {
            return (word >> (offset * 8)) & 0xffu;
        }
        if (mask == kMaskHalf) {
            uint32_t shift = (offset & 2u) * 8;
            return (word >> shift) & 0xffffu;
        }
        return word;
    }

    void write_data(uint32_t addr, uint8_t mask, uint32_t value) {
        if (meta_.tohost != 0 && addr == meta_.tohost) {
            tohost_value_ = value;
            if (value != 0) {
                finished_ = true;
                passed_ = (value == 1);
            }
        }

        uint32_t word_addr = addr & ~3u;
        uint32_t& word = data_words_[word_addr];
        uint32_t offset = addr & 3u;
        if (mask == kMaskWord) {
            word = value;
        } else if (mask == kMaskHalf) {
            uint32_t shift = (offset & 2u) * 8;
            word = (word & ~(0xffffu << shift)) | ((value & 0xffffu) << shift);
        } else {
            uint32_t shift = offset * 8;
            word = (word & ~(0xffu << shift)) | ((value & 0xffu) << shift);
        }
    }

    bool finished() const { return finished_; }
    bool passed() const { return passed_; }
    uint32_t tohost_value() const { return tohost_value_; }

    void observe_pc(uint32_t pc) {
        if (meta_.fail_pc != 0 && pc == meta_.fail_pc) {
            finished_ = true;
            passed_ = false;
            return;
        }
        if (meta_.pass_pc != 0 && pc == meta_.pass_pc) {
            finished_ = true;
            passed_ = true;
            if (tohost_value_ == 0) tohost_value_ = 1;
        }
    }

private:
    Meta meta_;
    std::vector<uint32_t> irom_;
    std::unordered_map<uint32_t, uint32_t> data_words_;
    std::unordered_map<uint32_t, uint32_t> mmio_words_;
    bool finished_ = false;
    bool passed_ = false;
    uint32_t tohost_value_ = 0;
};

void drive_comb(VmyCPU* top, MemoryModel& mem) {
    top->irom_data = mem.read_irom(top->irom_addr);
    top->perip_rdata = mem.read_data(top->perip_addr, top->perip_mask);
}

}  // namespace

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Options opt = parse_args(argc, argv);
    Meta meta = load_meta(opt.meta_path);

    MemoryModel mem(meta);
    mem.load_irom(load_hex_words(opt.irom_path));
    mem.load_dram(load_hex_words(opt.dram_path));

    VmyCPU* top = new VmyCPU;
    VerilatedVcdC* trace = nullptr;
    if (opt.wave) {
        Verilated::traceEverOn(true);
        trace = new VerilatedVcdC;
        top->trace(trace, 99);
        trace->open(opt.wave_path.c_str());
    }

    uint64_t sim_time = 0;
    uint64_t cycles = 0;
    uint64_t branch_total = 0;
    uint64_t branch_miss = 0;

    auto tick_half = [&]() {
        drive_comb(top, mem);
        top->eval();
        if (trace) trace->dump(sim_time);
        ++sim_time;
    };

    top->cpu_rst = 1;
    top->cpu_clk = 0;
    tick_half();
    for (int idx = 0; idx < 8; ++idx) {
        top->cpu_clk = !top->cpu_clk;
        tick_half();
    }
    top->cpu_rst = 0;

    while (!Verilated::gotFinish() && cycles < opt.max_cycles && !mem.finished()) {
        top->cpu_clk = 0;
        tick_half();

        top->cpu_clk = 1;
        drive_comb(top, mem);
        top->eval();
        if (top->perip_wen) {
            mem.write_data(top->perip_addr, top->perip_mask, top->perip_wdata);
        }
        mem.observe_pc(top->rootp->myCPU__DOT__u_core__DOT__pc_e);
        if (top->rootp->myCPU__DOT__u_core__DOT__update_en_e) {
            ++branch_total;
            if (top->rootp->myCPU__DOT__u_core__DOT__error_e) {
                ++branch_miss;
            }
        }
        if (trace) trace->dump(sim_time);
        ++sim_time;
        ++cycles;
    }

    top->final();
    if (trace) {
        trace->close();
        delete trace;
    }

    uint64_t branch_hit = branch_total >= branch_miss ? branch_total - branch_miss : 0;
    double hit_rate = branch_total ? (100.0 * static_cast<double>(branch_hit) / static_cast<double>(branch_total)) : 0.0;

    bool has_oracle = (meta.tohost != 0) || (meta.pass_pc != 0) || (meta.fail_pc != 0);
    bool pass = mem.finished() && mem.passed();
    bool done_without_oracle = !has_oracle && cycles >= opt.max_cycles;
    bool timeout = has_oracle && !mem.finished() && cycles >= opt.max_cycles;

    std::cout << (pass ? "PASS" : (done_without_oracle ? "DONE" : (timeout ? "TIMEOUT" : "FAIL")));
    if (!meta.suite.empty()) std::cout << " suite=" << meta.suite;
    if (!meta.test_case.empty()) std::cout << " case=" << meta.test_case;
    std::cout << " cycles=" << cycles
              << " branches=" << branch_total
              << " hit=" << branch_hit
              << " miss=" << branch_miss
              << " hit_rate=" << std::fixed << std::setprecision(2) << hit_rate << "%";
    if (meta.tohost != 0) {
        std::cout << " tohost=0x" << std::hex << std::setw(8) << std::setfill('0') << mem.tohost_value() << std::dec;
    }
    std::cout << "\n";

    delete top;
    if (pass || done_without_oracle) return 0;
    if (timeout) return 124;
    return 1;
}
