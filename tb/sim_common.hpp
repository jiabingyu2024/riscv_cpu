#pragma once

#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <ostream>
#include <string>

namespace sim_common {

struct PerfStats {
    uint64_t cycles = 0;
    uint64_t instret = 0;
    uint64_t branches = 0;
    uint64_t branch_miss = 0;
};

inline bool starts_with(const std::string& text, const std::string& prefix) {
    return text.rfind(prefix, 0) == 0;
}

inline uint32_t parse_u32(const std::string& text, uint32_t fallback = 0) {
    if (text.empty()) return fallback;
    char* end = nullptr;
    unsigned long value = std::strtoul(text.c_str(), &end, 0);
    if (end == text.c_str()) return fallback;
    return static_cast<uint32_t>(value);
}

inline uint64_t parse_u64(const std::string& text, uint64_t fallback = 0) {
    if (text.empty()) return fallback;
    char* end = nullptr;
    unsigned long long value = std::strtoull(text.c_str(), &end, 0);
    if (end == text.c_str()) return fallback;
    return static_cast<uint64_t>(value);
}

inline std::string json_string_value(const std::string& text, const std::string& key) {
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

inline double ratio(uint64_t numerator, uint64_t denominator) {
    if (denominator == 0) return 0.0;
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

inline uint64_t branch_hit(const PerfStats& stats) {
    return stats.branches >= stats.branch_miss ? stats.branches - stats.branch_miss : 0;
}

inline double branch_hit_rate(const PerfStats& stats) {
    return stats.branches ? 100.0 * ratio(branch_hit(stats), stats.branches) : 0.0;
}

inline double cpi(const PerfStats& stats) {
    return ratio(stats.cycles, stats.instret);
}

inline double ipc(const PerfStats& stats) {
    return ratio(stats.instret, stats.cycles);
}

inline double branch_mpki(const PerfStats& stats) {
    return stats.instret ? 1000.0 * ratio(stats.branch_miss, stats.instret) : 0.0;
}

inline void print_stats_line(std::ostream& out, const PerfStats& stats, const std::string& label) {
    out << "  " << label
        << ": cycles=" << stats.cycles
        << " instret=" << stats.instret
        << " cpi=" << cpi(stats)
        << " ipc=" << ipc(stats) << "\n";
}

inline void print_branch_line(std::ostream& out, const PerfStats& stats) {
    out << "  branch: total=" << stats.branches
        << " hit=" << branch_hit(stats)
        << " miss=" << stats.branch_miss
        << " hit_rate=" << branch_hit_rate(stats) << "%"
        << " mpki=" << branch_mpki(stats) << "\n";
}

inline void print_perf_block(std::ostream& out, const PerfStats& stats, const std::string& label) {
    print_stats_line(out, stats, label);
    out << "    branch: total=" << stats.branches
        << " hit=" << branch_hit(stats)
        << " miss=" << stats.branch_miss
        << " hit_rate=" << branch_hit_rate(stats) << "%"
        << " mpki=" << branch_mpki(stats) << "\n";
}

inline void print_perf_summary(std::ostream& out, const PerfStats& stats, const std::string& label) {
    out << "  " << label
        << ": cycles=" << stats.cycles
        << " instret=" << stats.instret
        << " cpi=" << cpi(stats)
        << " ipc=" << ipc(stats)
        << " branch_hit=" << branch_hit_rate(stats) << "%\n";
}

}  // namespace sim_common
