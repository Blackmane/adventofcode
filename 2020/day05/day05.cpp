/**
 * @file    day05.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    05 Dec 2020
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

namespace day05 {
/*
The problem:
The format of the rows and columns is the same as the binary code.
So it was easy do convert them to a integer and find the max value.
Second part: I didn't understand the text initially.
Anyway, just sort the seat ids and find the missing one.

The approach:
Here I have change how to approach to problems.
I have tried a more functional way to resolve the problem.
Interesting, but not yet productive.
I can do better.
*/

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


template<class T, class R>
void read(std::string inputFilename, char delimiter, 
        std::function <T(std::string)> convert, 
        std::function <void(T, R)> insert, R structure) {
    
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    while (std::getline(source, part, delimiter)) {
        insert(convert(part), structure);
    }
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

uint64_t findSolution(std::list<uint64_t> &list);


// ===== ===== ===== Lambdas ===== ===== ===== 

auto map = [](std::string part) -> uint64_t { 
    uint64_t row = 0;
    uint64_t column = 0;
    for (int i = 0; i < 7; ++i) {
        row = row << 1;
        row += part[i] == 'B';
    }
    for (int i = 7; i < 10; ++i) {
        column = column << 1;
        column += part[i] == 'R';
    }
    uint64_t seatId = row * 8 + column;
    return seatId;
};


auto foldl = [](uint64_t seatId, uint64_t maxId) -> uint64_t { 
    return maxId >= seatId ? maxId : seatId; 
};


auto order_insert = [](uint64_t value, std::list<uint64_t> * list) {
    auto it = std::lower_bound(list->begin(), list->end(), value);
    list->insert(it, value);
};


} // namespace day05


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day05::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day05::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day05::process1(std::string file) {
    uint64_t result = day05::parse<uint64_t, uint64_t>(file, '\n', 
                            day05::map, 
                            day05::foldl, 0);
    return result;
}

uint64_t day05::process2(std::string file) {
    std::list<uint64_t> list;
    day05::read<uint64_t, std::list<uint64_t>*>(file, '\n', 
                day05::map, 
                day05::order_insert, &list);

    uint64_t result = day05::findSolution(list);
    return result;
}

uint64_t day05::findSolution(std::list<uint64_t> &list) {
    uint64_t prec = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        // Find the "hole"
        if (prec+2 == *it) {
            return prec+1;
        }
        prec = *it;
    }
    return prec;
}