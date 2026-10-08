#include "process.hpp"

#include <dirent.h>
#include <fstream>
#include <string>
#include <sstream>

std::vector<ProcessInfo> get_processes() {
    std::vector<ProcessInfo> processes;

    DIR* directory = opendir("/proc");

    if (!directory) {
        return processes;
    }

    dirent* entry;

    while ((entry = readdir(directory)) != nullptr) {
        std::string pid_string = entry->d_name;

        if (pid_string.empty() ||
            pid_string.find_first_not_of("0123456789") != std::string::npos) {
            continue;
        }

        int pid = std::stoi(pid_string);

        std::ifstream stat_file("/proc/" + pid_string + "/stat");

        if (!stat_file) {
            continue;
        }

        std::string line;
        std::getline(stat_file, line);

        std::size_t name_start = line.find('(');
        std::size_t name_end = line.rfind(')');

        if (name_start == std::string::npos ||
            name_end == std::string::npos ||
            name_end <= name_start) {
            continue;
        }

        std::string process_name =
            line.substr(name_start + 1, name_end - name_start - 1);

        std::string remaining =
            line.substr(name_end + 2);

        std::istringstream stream(remaining);

        char state;
        stream >> state;

        unsigned long long value;
        unsigned long long utime = 0;
        unsigned long long stime = 0;

        for (int field = 4; field <= 15; field++) {
            stream >> value;

            if (field == 14) {
                utime = value;
            } else if (field == 15) {
                stime = value;
            }
        }

        if (stream.fail()) {
            continue;
        }

        processes.push_back({
            pid,
            process_name,
            utime + stime
        });
    }

    closedir(directory);

    return processes;
}

double calculate_process_cpu_usage(
    const ProcessInfo& previous,
    const ProcessInfo& current,
    unsigned long long total_cpu_difference) {

    if (total_cpu_difference == 0) {
        return 0.0;
    }

    if (current.cpu_time < previous.cpu_time) {
        return 0.0;
    }

    unsigned long long process_difference =
        current.cpu_time - previous.cpu_time;

    return (static_cast<double>(process_difference) /
            total_cpu_difference) * 100.0;
}