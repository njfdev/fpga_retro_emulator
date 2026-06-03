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

# find the source directories
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "sim/*.cpp"
    "software/*.cpp"
)

# remove rtl_out files already included by verilate
file(GLOB_RECURSE EXCLUDED_SRC_FILES CONFIGURE_DEPENDS
    "sim/rtl_out/*"
)
list(REMOVE_ITEM SRC_FILES ${EXCLUDED_SRC_FILES})

add_executable(sim
    ${SRC_FILES}
)

target_include_directories(sim PRIVATE sim software)

verilate(sim
    SOURCES rtl/nes_top.sv
    TOP_MODULE nes_top
)
