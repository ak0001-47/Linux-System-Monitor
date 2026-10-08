# Linux System Monitor

A lightweight Linux system monitor built with **C++17** and **ncurses**, using the Linux **`/proc` filesystem** to collect and display system and process-level statistics through a terminal-based dashboard.

> **Project Status:** In Development  
> **Current Version:** v0.1

---

## Table of Contents

- [Overview](#overview)
- [Why This Project](#why-this-project)
- [Objectives](#objectives)
- [Technologies and Tools](#technologies-and-tools)
- [How the Project Works](#how-the-project-works)
- [Project Development Approach](#project-development-approach)
- [Initial Project Setup](#initial-project-setup)
- [Project Structure](#project-structure)
- [CMake Configuration](#cmake-configuration)
- [System Information](#system-information)
- [Memory Monitoring](#memory-monitoring)
- [CPU Monitoring](#cpu-monitoring)
- [Process Monitoring](#process-monitoring)
- [Process CPU Usage](#process-cpu-usage)
- [Top Process Selection](#top-process-selection)
- [ncurses Terminal Interface](#ncurses-terminal-interface)
- [Current Architecture](#current-architecture)
- [Current Dashboard](#current-dashboard)
- [Current Features](#current-features)
- [Development Roadmap](#development-roadmap)
- [Building and Running](#building-and-running)
- [Current Limitations](#current-limitations)
- [Learning Goals](#learning-goals)
- [Future Documentation](#future-documentation)
- [License](#license)

---

# Overview

Linux exposes a large amount of information about the running system through the virtual **`/proc` filesystem**.

System-monitoring utilities such as `top` and `htop` use system information to display CPU usage, memory usage, running processes, load averages, and other statistics.

The goal of this project is to build a simplified Linux system monitor from scratch using **C++17**, without depending on a high-level monitoring library.

The project directly reads Linux system information from `/proc`, processes that information in C++, calculates resource utilization, and displays the results through an **ncurses terminal interface**.

The monitor is being developed incrementally, beginning with basic system statistics and gradually moving toward a continuously updating terminal monitoring application.

---

# Why This Project

The project is being developed to gain practical experience with Linux systems programming and understand how operating-system information can be accessed and processed by user-space programs.

Instead of simply using existing monitoring commands, the project explores how a monitoring utility can be implemented internally.

The project provides practical experience with:

- Linux `/proc` filesystem
- CPU accounting
- CPU utilization calculation
- Memory statistics
- Process information
- Process CPU usage
- Sampling-based monitoring
- Linux/POSIX interfaces
- Terminal user interfaces
- C++17
- CMake
- Modular systems programming
- Git and incremental development

The project also provides a practical way to understand the type of system information used by real Linux monitoring utilities.

---

# Objectives

The main objectives of the project are:

1. Understand how Linux exposes system information through `/proc`.
2. Collect CPU statistics directly from `/proc/stat`.
3. Calculate overall CPU utilization from successive samples.
4. Collect memory statistics from `/proc/meminfo`.
5. Calculate memory utilization.
6. Retrieve system uptime and load averages.
7. Enumerate running Linux processes.
8. Read process-level CPU information.
9. Calculate process CPU utilization.
10. Identify CPU-intensive processes.
11. Display system statistics through a terminal dashboard.
12. Use ncurses for terminal-based visualization.
13. Organize the project into modular C++ components.
14. Build the project using CMake.
15. Gradually convert the monitor into a continuously updating application.

---

# Technologies and Tools

## Programming Language

- C++17

## Operating System

- Linux
- Ubuntu on WSL2 during development

## Linux Interfaces

The project directly uses information exposed through:

- `/proc/stat`
- `/proc/meminfo`
- `/proc/uptime`
- `/proc/loadavg`
- `/proc/<PID>/stat`
- `/proc/<PID>/status`

## Terminal Interface

- ncurses

## Build System

- CMake

## Development Tools

- Visual Studio Code
- WSL2
- Git
- GitHub
- GNU/Linux command-line tools

---

# How the Project Works

The overall data flow is:

```text
                 Linux Kernel
                      │
                      ▼
              /proc Filesystem
                      │
       ┌──────────────┼──────────────┐
       │              │              │
       ▼              ▼              ▼
   CPU Data       Memory Data    Process Data
   /proc/stat     /proc/meminfo  /proc/<PID>/stat
       │              │              │
       └──────────────┼──────────────┘
                      ▼
                C++ Processing
                      │
                      ▼
             Resource Calculations
                      │
                      ▼
              ncurses Dashboard


# Project Structure:

linux-system-monitor/
│
├── CMakeLists.txt
├── README.md
│
├── include/
│   ├── cpu.hpp
│   ├── memory.hpp
│   ├── process.hpp
│   ├── system.hpp
│   └── ui.hpp
│
├── src/
│   ├── main.cpp
│   ├── cpu.cpp
│   ├── memory.cpp
│   ├── process.cpp
│   ├── system.cpp
│   └── ui.cpp
│
├── tests/
│
└── build/


The project separates data collection from presentation.
For example:

cpu.cpp
    ↓
CPU statistics

memory.cpp
    ↓
Memory statistics

system.cpp
    ↓
Uptime + load average

process.cpp
    ↓
Process information + CPU usage

ui.cpp
    ↓
Terminal dashboard

# Project Development Approach

The project is being developed incrementally.

Instead of attempting to implement the complete monitor in one step, each major component is implemented and tested independently before integrating it with the rest of the application.

The development process is:

Project Structure
       ↓
CMake Configuration
       ↓
System Information
       ↓
Memory Monitoring
       ↓
CPU Monitoring
       ↓
Process Enumeration
       ↓
Process CPU Monitoring
       ↓
Top Process Selection
       ↓
ncurses Dashboard
       ↓
Live Refresh
       ↓
Testing and Refinement

This approach makes each component easier to understand, test, debug, and explain.



===============================================
             LINUX SYSTEM MONITOR
===============================================

CPU Usage:    3.76%
Memory:       67.29%
Uptime:       138396 seconds
Load Average: 0.29 0.27 0.33

-----------------------------------------------
PID     PROCESS          CPU %
-----------------------------------------------
199094  MainThread       1.25
83803   MainThread       0.75
183582  MainThread       0.50
...