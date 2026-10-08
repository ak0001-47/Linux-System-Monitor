#include "system.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

SystemInfo get_system_info() {
    SystemInfo info{};

    std::ifstream uptime_file("/proc/uptime");
    if (!uptime_file) {
        throw std::runtime_error("Failed to open /proc/uptime");
    }

    uptime_file >> info.uptime_seconds;

    std::ifstream loadavg_file("/proc/loadavg");
    if (!loadavg_file) {
        throw std::runtime_error("Failed to open /proc/loadavg");
    }

    loadavg_file >> info.load_1min
                 >> info.load_5min
                 >> info.load_15min;

    return info;
}