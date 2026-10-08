#pragma once

struct MemoryInfo {
    unsigned long long total_kb;
    unsigned long long available_kb;
    unsigned long long used_kb;
};

MemoryInfo get_memory_info();