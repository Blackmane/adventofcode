/**
 * @file    day10.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    10 Dec 2020
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

namespace day10 {

/*
Part2: looks like there are no step by 2, but only by 3 and 1.
So the problem is easy with the following considerations.
In a list like [.., b, c, ..] where c-b==3, b and c must be present, otherwise there are no valid solutions.
So we can calculate solution as combinations([.., b]) * combinations([c, ..]).
Instead, if c-b==1, we must count how many consecutive step by one are present.
Let's consider a list of step by 1: [a0, ..., an] where an-a0 = n.
If steps are 1 or 0, the combinations are 1.
Adding a new step n implies that the possible combinations are those given by:
do 1 step from n-1
do 2 steps from n-2
do 3 steps from n-3
*/

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
uint64_t findSolution2(std::list<uint64_t> &list);
uint64_t countComb(int64_t i);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto toNumber = [](std::string part) -> uint64_t { 
    uint64_t value = stol(part);
    return value;
};

auto insert = [](uint64_t value, std::list<uint64_t> * list) {
    auto it = std::lower_bound(list->begin(), list->end(), value);
    list->insert(it, value);
};

} // namespace day10


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day10::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day10::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day10::process1(std::string file) {
    std::list<uint64_t> list;
    day10::read<uint64_t, std::list<uint64_t>*>(file, '\n', 
                toNumber, 
                insert, &list);

    uint64_t result = day10::findSolution(list);
    return result;
}

uint64_t day10::process2(std::string file) {
    std::list<uint64_t> list;
    day10::read<uint64_t, std::list<uint64_t>*>(file, '\n', 
                toNumber, 
                insert, &list);

    uint64_t result = day10::findSolution2(list);
    return result;
}

uint64_t day10::findSolution(std::list<uint64_t> &list) {
    uint64_t onediff = 0;
    uint64_t threediff = 1;
    uint64_t voltage = 0;

    for (auto it = list.begin(); it != list.end(); ++it) {
        int64_t diff = *it - voltage;
        // Count diff by one and diff by three
        if (diff == 1) {
            onediff++;
        } else if (diff == 3) {
            threediff++;
        }
        // Save new voltage
        voltage = *it;
    }
    return onediff * threediff;
}

uint64_t day10::findSolution2(std::list<uint64_t> &list) {
    uint64_t combinations = 1;
    uint64_t prec = 0;
    uint64_t precdif = 0;
    uint64_t i = 0;

    for (auto yt = list.begin(); yt != list.end(); ++yt) {
        precdif = *yt - prec;
        switch (precdif) {
            case 3:
                // Multiply combinations
                combinations *= countComb(i);
                i = 0;
                break;
            case 2:
                // Looks like there is no diff by 2
                std::cout << "none?" << std::endl;
                break;
            case 1:
                // Count number of consecutive values
                i++;
                break;
            default:
                break;
        }
        prec = *yt;
    }
    // Count last consecutive values
    combinations *= countComb(i);

    return combinations;
}

uint64_t day10::countComb(int64_t i) {
    // Count combinations of consecutive values
    if (i < 0) {
        return 0;
    }
    if (i == 0 || i == 1) {
        return 1;
    }

    return countComb(i-1) + countComb(i-2) + countComb(i-3);
}