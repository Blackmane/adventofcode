/**
 * @file    day14.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    14 Dec 2020
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
#include <vector>
#include <unordered_map>

namespace day14 {

struct Mask {
    uint64_t or_m = 0;
    uint64_t and_m = 0;
};

struct Operation {
    uint64_t dest;
    Mask mask;
    uint64_t value;
};

typedef std::unordered_map<uint64_t, uint64_t> Memory;

template<class M, class L, class S>
void parseMultiIf(std::string inputFilename, char delimiter, 
        std::function <M(std::string)> convertMask, 
        std::function <L(std::string, M)> convertLine, 
        std::function <void(L, S)> insert, S structure) {
    
    std::ifstream source;
    source.open(inputFilename);
    M mask;
    std::string part;
    while (std::getline(source, part, delimiter)) {
        if (part.substr(0,3) == "mem") {
            insert(convertLine(part, mask), structure);
        } else if (part.substr(0,3) == "mas") {
            mask = convertMask(part);
        }
    }
}

std::string combineMask (uint64_t value, std::string mask);
void combineOperations (uint64_t value, std::string combinedMask, std::vector<uint64_t> *addrList);

uint64_t process1(std::string file);
uint64_t process2(std::string file);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto toMask = [](std::string part) -> Mask {
    Mask mask;
    size_t len = part.length();
    size_t pos = part.find("= ", 0) + 2;
    for (size_t i = pos; i < len; i++) {
        mask.or_m  = mask.or_m << 1;
        mask.and_m = mask.and_m << 1;
        switch (part[i]) {
        case 'X':
            mask.or_m  += 0;
            mask.and_m += 1;
            break;
        case '1':
            mask.or_m  += 1;
            mask.and_m += 1;
            break;
        case '0':
            mask.or_m  += 0;
            mask.and_m += 0;
            break;
        default:
            break;
        }
    }
    return mask;
};

auto toOperation = [](std::string part, Mask mask) -> Operation {
    Operation op;
    op.mask = mask;

    std::size_t pos = part.find("[") + 1;
    std::size_t to = part.find("]", pos);
    op.dest = std::stol(part.substr(pos, to-pos));
    pos = part.find("= ") + 2;
    to = part.length();
    op.value = std::stol(part.substr(pos, to-pos));
    return op;
};

auto insert = [](Operation op, Memory* mem) -> void { 
    (*mem)[op.dest] = (op.value & op.mask.and_m) | op.mask.or_m;
};

auto getMask = [](std::string part) -> std::string {
    size_t len = part.length();
    size_t pos = part.find("= ", 0) + 2;
    return part.substr(pos, len-pos);
};

auto toOperations = [](std::string part, std::string mask) -> std::pair<std::vector<uint64_t>, uint64_t> {
    std::size_t pos = part.find("[") + 1;
    std::size_t to = part.find("]", pos);
    uint64_t addr = std::stol(part.substr(pos, to-pos));
    pos = part.find("= ") + 2;
    to = part.length();
    uint64_t value = std::stol(part.substr(pos, to-pos));
    
    std::vector<uint64_t> addrList;
    combineOperations(0, combineMask (addr, mask), &addrList);

    return std::make_pair(addrList, value);
};

auto applyOperations = [](std::pair<std::vector<uint64_t>, uint64_t> ops, Memory* mem) -> void { 
    int i = 0;
    for(auto addr : ops.first){
        (*mem)[addr] = ops.second;
        i++;
    }
};


} // namespace day14

// ===== ===== ===== Implementations ===== ===== ===== 

std::string day14::combineMask (uint64_t addr, std::string mask) {
    std::string combined(mask);
    size_t len = combined.length();
    for (size_t i = 0; i < len; i++) {
        if (combined[i] == '0') {
            if ((addr >> (len -i-1)) %2 == 1) {
                combined[i] = '1';
            }
        }
    }
    return combined;
}


void day14::combineOperations (uint64_t value, std::string combinedMask, std::vector<uint64_t> * addrList) {
    size_t len = combinedMask.length();
    if (len > 0) {
        uint64_t newValue = value << 1;
        std::string newMask = combinedMask.substr(1, len-1);
        if (len > 1) {
            switch (combinedMask[0]) {
            case 'X':
                combineOperations (newValue, newMask, addrList);
                combineOperations (newValue+1, newMask, addrList);
                break;
            case '1':
                combineOperations (newValue+1, newMask, addrList);
                break;
            case '0':
                combineOperations (newValue, newMask, addrList);
                break;
            default:
                break;
            }
        } else {
            switch (combinedMask[0]) {
            case 'X':
                addrList->push_back(newValue);
                addrList->push_back(newValue+1);
                break;
            case '1':
                addrList->push_back(newValue+1);
                break;
            case '0':
                addrList->push_back(newValue);
                break;
            default:
                break;
            }
        }
    }
    return;
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
    std::cout << day14::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day14::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Solutions ===== ===== ===== 

uint64_t day14::process1(std::string file) {
    Memory memory;
    parseMultiIf<Mask, Operation, Memory*>(file, '\n', 
                            toMask, 
                            toOperation, 
                            insert, &memory);
    uint64_t result = 0;
    for(auto memCel : memory) {
        result += memCel.second;
    }
    return result;
}

uint64_t day14::process2(std::string file) {
    Memory memory;
    parseMultiIf<std::string, std::pair<std::vector<uint64_t>, uint64_t>, Memory*>(file, '\n', 
                            getMask, 
                            toOperations, 
                            applyOperations, &memory);
    uint64_t result = 0;
    for(auto memCel : memory) {
        result += memCel.second;
    }
    return result;
}