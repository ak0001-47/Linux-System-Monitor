#pragma once

#include <string>
#include <vector>

struct ProcessInfo {
    int pid;
    std::string name;
    unsigned long long cpu_time;
};

std::vector<ProcessInfo> get_processes();

double calculate_process_cpu_usage(
    const ProcessInfo& previous,
    const ProcessInfo& current,
    unsigned long long total_cpu_difference
);