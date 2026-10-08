#pragma once

struct CpuStats {
    unsigned long long total;
    unsigned long long idle;
};

CpuStats get_cpu_stats();

double calculate_cpu_usage(const CpuStats& previous,const CpuStats& current);