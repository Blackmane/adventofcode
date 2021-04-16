/**
 * @file    day05.cpp
 * @brief   
 * @project advent of code
 * 
 * @author  Niccolò Pieretti
 * @date    22 Mar 2021
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

namespace day05 {

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

// ===== ===== ===== Lambdas ===== ===== ===== 

auto isNice = [](std::string part) -> bool { 
    uint vowels = 0;
    bool almostTwice = false;

    auto prec = '\0';
    for(auto c : part) {
        switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            vowels++;
            break;
        case 'b':
        case 'd':
        case 'q':
        case 'y':
            if (prec + 1 == c) {
                return false;
            }
            break;
        default:
            break;
        }
        if (prec == c) {
            almostTwice = true;
        }
        prec = c;
    }

    return vowels >= 3 && almostTwice;
};

auto isNice2 = [](std::string part) -> bool { 
    bool almostTwice = false;
    bool almostRepeat = false;

    auto prec = '\0';
    auto precprec = ' ';
    for (size_t i = 0; i < part.length(); i++) {
        if (!almostTwice && prec != '\0') {
            // Check if repeat
            for (size_t j = i+1; j < part.length()-1; j++) {
                if (prec == part[j] && part[i] == part[j+1]) {
                    almostTwice = true;
                    break;
                }
            }
        }
        if (precprec == part[i]) {
            almostRepeat = true;
        }
        precprec = prec;
        prec = part[i];
    }
    return almostTwice && almostRepeat;
};


auto foldl = [](bool isnice, uint64_t count) -> uint64_t { 
    return isnice ? count + 1 : count; 
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
                            day05::isNice, 
                            day05::foldl, 0);
    return result;
}

uint64_t day05::process2(std::string file) {
    uint64_t result = day05::parse<uint64_t, uint64_t>(file, '\n', 
                            day05::isNice2, 
                            day05::foldl, 0);
    return result;
}

