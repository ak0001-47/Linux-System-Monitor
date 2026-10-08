cmake_minimum_required(VERSION 3.16)

project(linux-system-monitor
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Curses REQUIRED)

add_executable(linux-system-monitor
    src/main.cpp
    src/system.cpp
    src/memory.cpp
    src/cpu.cpp
    src/process.cpp
    src/ui.cpp
)

target_include_directories(linux-system-monitor
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(linux-system-monitor
    PRIVATE
        ${CURSES_LIBRARIES}
)