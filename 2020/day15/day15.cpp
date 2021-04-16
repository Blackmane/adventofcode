/**
 * @file    day15.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    15 Dec 2020
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
#include <functional>
#include <unordered_map>
#include <vector>


namespace day15 {

template<class T, class S>
void read(std::string inputFilename, char delimiter, 
        std::function <T(std::string)> convert, 
        std::function <void(T, S)> insert, S structure) {
    
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    while (std::getline(source, part, delimiter)) {
        insert(convert(part), structure);
    }
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

uint64_t findSolution(std::vector<uint64_t> & numbers, uint64_t last);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto toNumber = [](std::string part) -> uint64_t {
    uint64_t number = stol(part);
    return number;
};

auto insert = [](uint64_t num, std::vector<uint64_t>* numbers) -> void {
    numbers->push_back(num);
};

} // namespace day15


// ===== ===== ===== Implementations ===== ===== ===== 
uint64_t day15::findSolution(std::vector<uint64_t> & numbers, uint64_t last) {
    //std::unordered_map<uint64_t, uint64_t> sayed; // 10x Slow solution!
    std::vector<uint64_t> sayed(last);
    uint64_t say = 0;
    uint64_t i = 0;
    // Load first numbers
    while (i < numbers.size()) {
        say = numbers[i];
        i++;
        sayed[say] = i;
    }
    uint64_t nextSay;
    for (;i < last; ++i) {
        // Get current number last turn
        uint64_t lastTurn = sayed[say];
        // If exist entry, calculate difference (next number to say)
        if (lastTurn > 0) {
            nextSay = i - lastTurn;
        } else {
            nextSay = 0;
        }
        // Set turn
        sayed[say] = i;
        // Next
        say = nextSay;
    }

    return say;
}


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day15::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day15::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Solutions ===== ===== ===== 
uint64_t day15::process1(std::string file) {
    std::vector<uint64_t> numbers;
    read<uint64_t, std::vector<uint64_t>*>(file, ',', 
                toNumber, insert, &numbers);

    uint64_t result = findSolution(numbers, 2020);
    return result;
}

uint64_t day15::process2(std::string file) {
    std::vector<uint64_t> numbers;
    read<uint64_t, std::vector<uint64_t>*>(file, ',', 
                toNumber, insert, &numbers);

    uint64_t result = findSolution(numbers, 30000000);
    return result;
}