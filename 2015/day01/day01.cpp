/**
 * @file    day01.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    07 Dec 2020
 * @bug     
 * @todo    
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <functional>
#include <set>

namespace day01 {

template<class T>
T parseLine(std::string inputFilename, char delimiter, 
        std::function <T(std::string)> convert) {
    
    std::ifstream source;
    source.open(inputFilename);

    std::string part;
    std::getline(source, part, delimiter);
    return convert(part);
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto map = [](std::string part) -> uint64_t { 
    uint64_t count = 0;
    for (long unsigned int i = 0; i < part.length(); ++i) {
        switch (part[i]) {
        case '(':
            count++;
            break;
        case ')':
            count--;
            break;
        
        default:
            break;
        }
    }
    return count;
};

auto map2 = [](std::string part) -> uint64_t { 
    int64_t count = 0;
    for (long unsigned int i = 0; i < part.length(); ++i) {
        switch (part[i]) {
        case '(':
            count++;
            break;
        case ')':
            count--;
            break;
        
        default:
            break;
        }
        if (count < 0) {
            return i+1;
        }
    }
    return 0;
};


} // namespace day01


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day01::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day01::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day01::process1(std::string file) {
    uint64_t result = parseLine<uint64_t>(file, '\n', map);
    return result;
}

uint64_t day01::process2(std::string file) {
    uint64_t result = parseLine<uint64_t>(file, '\n', map2);
    return result;
}