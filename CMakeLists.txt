cmake_minimum_required(VERSION 3.16)

project(FPGARetroEmulatorSim
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(POLICY CMP0144)
  cmake_policy(SET CMP0144 NEW)
endif()

find_package(verilator)

add_executable(sim
    sim/main.cpp
)

verilate(sim
    SOURCES rtl/nes_top.sv
    TOP_MODULE nes_top
)
