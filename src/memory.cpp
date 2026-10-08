#include "memory.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

MemoryInfo get_memory_info() {
    std::ifstream file("/proc/meminfo");

    if (!file) {
        throw std::runtime_error("Could not open /proc/meminfo");
    }

    MemoryInfo info{};

    std::string key;
    unsigned long long value;
    std::string unit;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") {
            info.total_kb = value;
        } else if (key == "MemAvailable:") {
            info.available_kb = value;
        }

        if (info.total_kb && info.available_kb) {
            break;
        }
    }

    if (!info.total_kb || !info.available_kb) {
        throw std::runtime_error("Could not read memory information");
    }

    info.used_kb = info.total_kb - info.available_kb;

    return info;
}