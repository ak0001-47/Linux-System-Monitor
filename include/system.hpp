#pragma once

#include <string>

struct SystemInfo {
    double uptime_seconds;
    double load_1min;
    double load_5min;
    double load_15min;
};

SystemInfo get_system_info();