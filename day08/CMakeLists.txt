# ===== ===== ===== Setups ===== ===== ===== 
cmake_minimum_required(VERSION 3.11)

# Project name and a few useful settings. Other commands can pick up the results
project(aoc2020_day08
    VERSION 1.0
    DESCRIPTION "Advent of code: day08"
    )

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)
    # Enable clang-tidy
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

    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
    
    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# ===== ===== ===== Code ===== ===== ===== 

# ServiceCam_test
add_executable (day08 day08.cpp )
#target_include_directories(ServiceCam_test PRIVATE ../facilities/include/)
target_compile_features(day08 PRIVATE cxx_std_11)
#target_link_libraries (day08 PRIVATE ${} )