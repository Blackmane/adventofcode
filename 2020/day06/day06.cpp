/**
 * @file    day06.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    06 Dec 2020
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

namespace day06 {
/*
Same approach as on day05.
I have implemented a multiline parser, it works, but it's not good.

The part1 was easy using a set and checking the size.
The part2 was a nightmare of bugs.
For verify the "all" condition i have used a hard way:
1- transform every answer into a binary number;
2- use of th bitwise AND operator to combine group answers
3- count the answers.
Maybe it could be simpler.
*/

template<class T, class P, class R>
R multiparse(std::string inputFilename, char delimiter, 
        std::function <P(P, std::string)> combineLines, P lineNeutral, 
        std::function <T(P)> convert, 
        std::function <R(T, R)> foldl, R accumulatorValue) {
    
    std::ifstream source;
    source.open(inputFilename);
    R accumulator = accumulatorValue;
    std::string part;
    P complete = lineNeutral;
    while (std::getline(source, part, delimiter)) {
        if (part != "") {
            complete = combineLines(complete, part);
        } else {
            // End
            accumulator = foldl(convert(complete), accumulator);
            complete = lineNeutral;
        }
    }
    // Last one
    accumulator = foldl(convert(complete), accumulator);

    return accumulator ;
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto map = [](std::string part) -> uint64_t { 
    std::set<char> answers;
    for (long unsigned int i = 0; i < part.length(); ++i) {
        answers.insert(part[i]);
    }
    return answers.size();
};


auto foldl = [](uint64_t answers, uint64_t total) -> uint64_t { 
    return answers + total; 
};


auto toBinary = [](uint64_t answers, std::string answer) -> uint64_t {
    uint64_t value = 0;
    for (long unsigned int i = 0; i < answer.length(); ++i) {
        uint64_t increment = 0;
        if (answer[i] >= 'a' && answer[i] <= 'z') {
            increment++;
            increment = increment << (answer[i] - 'a');
        }
        value += increment;
    }
    return answers & value;
};

auto countAll = [](uint64_t number) -> uint64_t { 
    uint64_t partial = number;
    uint64_t sum = 0;
    while (partial > 0) {
        sum += partial % 2;
        partial = partial >> 1;
    }
    return sum;
};


} // namespace day06


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day06::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day06::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day06::process1(std::string file) {
    uint64_t result = day06::multiparse<uint64_t, std::string, uint64_t>(file, '\n', 
        [](std::string complete, std::string part){return complete + part;}, "",
                            day06::map, 
                            day06::foldl, 0);
    return result;
}

uint64_t day06::process2(std::string file) {
    uint64_t result = day06::multiparse<uint64_t, uint64_t, uint64_t>(file, '\n', 
                            day06::toBinary, 67108863, // 2^26-1
                            day06::countAll, 
                            day06::foldl, 0);
    return result;
}