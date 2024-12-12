/**
 * @file    main.cpp
 * @project advent of code
 * 
 * @author  Niccolò Pieretti
 * @date    12 Dec 2024
 *
 ****************************************************************************
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include "day12.h"
#include <iostream>

using namespace day12;

#ifdef PRINT_TIMING
#    include <chrono>
#endif

// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
    std::string inputFilename(argv[1]);
    std::cout << "OPENING: " << inputFilename << std::endl;

    // Part 1
    std::cout << "Part1" << std::endl;
#ifdef PRINT_TIMING
    auto begin1 = std::chrono::steady_clock::now();
#endif
    std::cout << process1(inputFilename) << std::endl;
#ifdef PRINT_TIMING
    auto end1 = std::chrono::steady_clock::now();
    std::cout.imbue(std::locale(""));
    std::cout << "Part1 execution = " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count()
              << "[µs]" << std::endl;
#endif

    // Part 2
    std::cout << "Part2" << std::endl;
#ifdef PRINT_TIMING
    auto begin2 = std::chrono::steady_clock::now();
#endif
    std::cout << process2(inputFilename) << std::endl;
#ifdef PRINT_TIMING
    auto end2 = std::chrono::steady_clock::now();
    std::cout << "Part2 execution = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count()
              << "[µs]" << std::endl;
#endif

    return 0;
}