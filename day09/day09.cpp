/**
 * @file    day09.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    09 Dec 2020
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
#include <vector>

namespace day09 {



const size_t FROMVALUE = 25;

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

uint64_t findWrong(std::vector<uint64_t> &list);
uint64_t findSum(std::vector<uint64_t> &list, uint64_t wrongValue);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto toNumber = [](std::string part) -> uint64_t { 
    uint64_t value = stol(part);
    return value;
};

auto insert = [](uint64_t value, std::vector<uint64_t> * list) {
    list->push_back(value);
};

} // namespace day09


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day09::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day09::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day09::process1(std::string file) {
    std::vector<uint64_t> list;
    day09::read<uint64_t, std::vector<uint64_t>*>(file, '\n', 
                toNumber, 
                insert, &list);

    uint64_t result = day09::findWrong(list);
    return result;
}

uint64_t day09::process2(std::string file) {
    std::vector<uint64_t> list;
    day09::read<uint64_t, std::vector<uint64_t>*>(file, '\n', 
                toNumber, 
                insert, &list);

    uint64_t wrongValue = day09::findWrong(list);
    uint64_t result = day09::findSum(list, wrongValue);
    return result;
}

uint64_t day09::findWrong(std::vector<uint64_t> &list) {
    // Skipp first FROMVALUE values
    for (size_t i = FROMVALUE; i < list.size(); i++) {
        bool checksum = false;
        // Check in [i-FROMVALUE, i]
        for (size_t j = i-FROMVALUE; j < i; j++) {
            for (size_t k = j+1; k < i; k++) {
                // Two differents number j, k where sum is correct
                if (list[i] == list[j] + list[k]) {
                    checksum = true;
                    break;
                }
            }
            if (checksum) {
                break;
            }
        }
        // First value not valid is the solution
        if (!checksum) {
            return list[i];
        }
    }
    return 0;
}

uint64_t day09::findSum(std::vector<uint64_t> &list, uint64_t wrongValue) {
    uint64_t min;
    uint64_t max;
    for (size_t i = 0; i < list.size(); i++) {
        min = list[i];
        max = list[i];
        uint64_t sum = 0;
        // For every list[i] try to calculate sum of consecutive values
        for (size_t j = i; j < list.size(); j++) {
            sum += list[j];
            // Save min and max for the solution
            min = std::min(min, list[j]);
            max = std::max(max, list[j]);
            // Check if sum is found
            if (sum == wrongValue) {
                return min + max;
            } else if (sum > wrongValue) {
                // Useless to continue
                break;
            }
        }
    }
    return 0;
}