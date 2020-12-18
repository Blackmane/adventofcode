/**
 * @file    day18.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    18 Dec 2020
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
#include <functional>


namespace day18 {

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

uint64_t evaluate (std::string part);
uint64_t evaluate2 (std::string part);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto evaluateLine = [](std::string part) -> uint64_t { 
    return evaluate(part); 
};

auto evaluateLine2 = [](std::string part) -> uint64_t { 
    return evaluate2(part); 
};


auto add = [](uint64_t value, uint64_t sum) -> uint64_t { 
    return sum + value; 
};


} // namespace day18


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day18::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day18::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day18::process1(std::string file) {
    uint64_t result = parse<uint64_t, uint64_t>(file, '\n', evaluateLine, add, 0);
    return result;
}


uint64_t day18::process2(std::string file) {
    uint64_t result = parse<uint64_t, uint64_t>(file, '\n', evaluateLine2, add, 0);
    return result;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day18::evaluate (std::string part) { 
    uint64_t result = 0;
    bool isSum = true;
    size_t partLen = part.length();
    for (size_t i = 0; i < partLen; i++) {
        switch (part[i]) {
        case ' ':
            // Skip
            break;
        case '+':
            isSum = true;
            break;
        case '*':
            isSum = false;
            break;
        case '(': {
            // Look for the corresponding closure
            size_t next = i + 1;
            size_t closure = part.find(")", next);
            // The closure is the one not anticipated by an opening
            while ( part.find("(", next) < closure ) {
                next = closure + 1;
                closure = part.find(")", next);
            }
            if (isSum) { 
                result += evaluate(part.substr(i+1, closure -i -1)); // -1 exclude the final ')'
            } else { 
                result *= evaluate(part.substr(i+1, closure -i -1)); // -1 exclude the final ')'
            }
            // Skip already evalued chars
            i = closure;
            } break;
        case ')':
            // never called by construction
            return result;
        default:
            // it is a number
            if (isSum) { 
                result += part[i] - '0';
            } else { 
                result *= part[i] - '0'; 
            }
            break;
        }
    }
    return result;
}

uint64_t day18::evaluate2 (std::string part) { 
    uint64_t result = 0;
    size_t partLen = part.length();
    for (size_t i = 0; i < partLen; i++) {
        switch (part[i]) {
        case ' ':
            // Skip
            break;
        case '+':
            // Skip
            break;
        case '*':
            return result * evaluate2( part.substr(i + 1) );
        case '(': {
            size_t next = i + 1;
            size_t closure = part.find(")", next);
            while ( part.find("(", next) < closure ) {
                next = closure + 1;
                closure = part.find(")", next);
            }
            result += evaluate2(part.substr(i+1, closure -i -1)); // -1 exclude the final ')'
            i = closure;
            } break;
        case ')':
            // never called by construction
            return result;
        default:
            // It is a number
            result += part[i] - '0';
            break;
        }
    }
    return result;
}