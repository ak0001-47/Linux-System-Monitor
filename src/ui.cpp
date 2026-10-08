#include "ui.hpp"

#include "cpu.hpp"
#include "memory.hpp"
#include "system.hpp"
#include "process.hpp"

#include <algorithm>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ncurses.h>
#include <thread>

struct ProcessUsage {
    ProcessInfo process;
    double cpu_usage;
};

void start_ui() {
    initscr();
    noecho();
    curs_set(0);

    CpuStats first_cpu = get_cpu_stats();
    std::vector<ProcessInfo> first_processes = get_processes();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    CpuStats second_cpu = get_cpu_stats();
    std::vector<ProcessInfo> second_processes = get_processes();

    double cpu_usage = calculate_cpu_usage(first_cpu, second_cpu);

    unsigned long long total_cpu_difference =
        second_cpu.total - first_cpu.total;

    std::vector<ProcessUsage> process_usage;

    for (const ProcessInfo& current : second_processes) {
        for (const ProcessInfo& previous : first_processes) {
            if (current.pid == previous.pid) {
                double usage = calculate_process_cpu_usage(
                    previous,
                    current,
                    total_cpu_difference
                );

                process_usage.push_back({
                    current,
                    usage
                });

                break;
            }
        }
    }

    std::sort(
        process_usage.begin(),
        process_usage.end(),
        [](const ProcessUsage& first, const ProcessUsage& second) {
            return first.cpu_usage > second.cpu_usage;
        }
    );

    MemoryInfo memory = get_memory_info();
    SystemInfo system = get_system_info();

    double memory_usage =
        (static_cast<double>(memory.used_kb) /
         memory.total_kb) * 100.0;

    clear();

    printw("===============================================\n");
    printw("             LINUX SYSTEM MONITOR              \n");
    printw("===============================================\n\n");

    printw("CPU Usage:    %.2f%%\n", cpu_usage);
    printw("Memory:       %.2f%%\n", memory_usage);

    printw("Uptime:       %.0f seconds\n",
           system.uptime_seconds);

    printw("Load Average: %.2f %.2f %.2f\n\n",
           system.load_1min,
           system.load_5min,
           system.load_15min);

    printw("-----------------------------------------------\n");
printw("PID\tPROCESS\t\tCPU %%\n");
printw("-----------------------------------------------\n");

int count = 0;

for (const ProcessUsage& process : process_usage) {
    printw("%d\t%-16s %.2f\n",
           process.process.pid,
           process.process.name.c_str(),
           process.cpu_usage);

    count++;

    if (count == 10) {
        break;
    }
}

printw("\nPress any key to exit.");

    refresh();
    getch();

    endwin();
}