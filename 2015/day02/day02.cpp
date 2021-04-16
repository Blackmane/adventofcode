/**
 * @file    day02.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    07 Dec 2020
 * @bug     
 * @todo    
 * 
 ****************************************************************************
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

namespace day02 {

template<class T, class R>
R parse(std::string inputFilename, char delimiter, 
        std::function <T(std::string)> convert, 
        std::function <R(T, R)> foldl, R accumulatorValue) {
    
    std::ifstream source;
    source.open(inputFilename);
    R accumulator = accumulatorValue;
    std::string part;
    while (std::getline(source, part, delimiter)) {
        accumulator = foldl(convert(part), accumulator);
    }
    return accumulator ;
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

uint64_t findSolution(std::list<uint64_t> &list);


// ===== ===== ===== Lambdas ===== ===== ===== 

auto toArea = [](std::string part) -> uint64_t { 
    auto last = 0;
    auto pos = part.find('x', last);
    uint64_t l1 = std::stoi(part.substr(last, pos));
    last = pos+1;
    pos = part.find('x', last);
    uint64_t l2 = std::stoi(part.substr(last, pos));
    last = pos+1;
    uint64_t l3 = std::stoi(part.substr(last, part.length()-last+1));

    uint64_t area = l1*l2 + l1*l3 + l2*l3;
    return 2*area + std::min(std::min(l1*l2, l1*l3), l2*l3);
};

auto toLength = [](std::string part) -> uint64_t { 
    auto last = 0;
    auto pos = part.find('x', last);
    uint64_t l1 = std::stoi(part.substr(last, pos));
    last = pos+1;
    pos = part.find('x', last);
    uint64_t l2 = std::stoi(part.substr(last, pos));
    last = pos+1;
    uint64_t l3 = std::stoi(part.substr(last, part.length()-last+1));

    uint64_t length = l1 + l2 + l3 - std::max(std::max(l1, l2), l3);
    std::cout<< length << std::endl;
    return l1 * l2 * l3 + length * 2;
};


auto sum = [](uint64_t area, uint64_t total) -> uint64_t { 
std::cout<< area << std::endl;
    return area + total; 
};

} // namespace day02


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day02::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day02::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day02::process1(std::string file) {
    uint64_t result = day02::parse<uint64_t, uint64_t>(file, '\n', toArea, sum, 0);
    return result;
}

uint64_t day02::process2(std::string file) {
    uint64_t result = day02::parse<uint64_t, uint64_t>(file, '\n', toLength, sum, 0);
    return result;
}

// 3812909