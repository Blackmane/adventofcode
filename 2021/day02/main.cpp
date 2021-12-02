/**
 * @file    main.cpp
 * @project advent of code
 * 
 * @author  Niccolò Pieretti
 * @date    02 Dec 2021
 *
 ****************************************************************************
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include "day02.h"
#include <iostream>

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
    std::cout << process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << process2(inputFilename) << std::endl;

    return 0;
}

