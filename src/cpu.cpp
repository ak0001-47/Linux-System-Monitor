#include "cpu.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

CpuStats get_cpu_stats() {
    std::ifstream file("/proc/stat");

    if (!file) {
        throw std::runtime_error("Could not open /proc/stat");
    }

    std::string line;
    std::getline(file, line);

    std::istringstream stream(line);

    std::string cpu;
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;

    stream >> cpu
           >> user
           >> nice
           >> system
           >> idle
           >> iowait
           >> irq
           >> softirq
           >> steal;

    CpuStats stats;

    stats.idle = idle + iowait;

    stats.total = user + nice + system + idle +
                  iowait + irq + softirq + steal;

    return stats;
}

double calculate_cpu_usage(const CpuStats& previous,
                           const CpuStats& current) {
    unsigned long long total_difference =
        current.total - previous.total;

    unsigned long long idle_difference =
        current.idle - previous.idle;

    if (total_difference == 0) {
        return 0.0;
    }

    return (1.0 -
            static_cast<double>(idle_difference) /
            total_difference) * 100.0;
}
