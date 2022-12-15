# ===== ===== ===== Setups ===== ===== =====
cmake_minimum_required(VERSION 3.11)

# Project name and a few useful settings. Other commands can pick up the results
project(adventofcode
        VERSION 3.0
        DESCRIPTION "Advent of code"
        )

# Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)
# Enable clang-tidy
# TODO: variabile
#    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=include;-checks=*,-llvmlibc*")

# https://interrupt.memfault.com/blog/best-and-worst-gcc-clang-compiler-flags
add_compile_options(-Wall -Wextra -Wno-unused-parameter
        -pedantic
        -Wshadow -Wdouble-promotion
        -Wformat=2 -Wformat-truncation
        -ffunction-sections -fdata-sections
        $<$<CONFIG:RELEASE>:-Werror>
        $<$<NOT:$<CONFIG:DEBUG>>:-O2>
        -g3 -fPIC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ===== ===== ===== Config ===== ===== =====

set(YEAR "" CACHE STRING "AoC year")
set(DAY "" CACHE STRING "Day to compile")

# Adding an option to switch on or off compilation of tests
option (ENABLE_TESTING "Set to ON to perform unit tests" OFF)

# Adding an option to switch on or off the print of the execution time
option (ENABLE_PRINT_TIMING "Set to ON to print the execution time" OFF)

# Adding an option to test common lib
option (ENABLE_COMMON_TESTING "Set to ON to compile common lib testing" OFF)

if (ENABLE_TESTING OR ENABLE_COMMON_TESTING)
    enable_testing()
endif ()

# ===== ===== ===== Library ===== ===== =====

add_subdirectory(common)

# ===== ===== ===== Code ===== ===== =====

if ( DEFINED YEAR AND DEFINED DAY )
    add_subdirectory(${YEAR}/${DAY})
endif ()

