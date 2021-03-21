/**
 * @file    day02.cpp
 * @brief   
 * @project advent of code 2015
 * 
 * @author  Niccolò Pieretti
 * @date    20 mar 2021
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
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

namespace day03 {

struct Position {
    
    int32_t x;
    int32_t y;
    
    bool operator==(const Position& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    Position () {
        x = 0;
        y = 0;
    }
};

std::string readAsSingleLine(std::string inputFilename) {
    std::ifstream source;
    source.open(inputFilename);
    std::string accumulator = "";
    std::string part;
    while (std::getline(source, part, '\n')) {
        accumulator += part;
    }
    return accumulator;
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

std::unordered_map<Position, int> execute(std::string &istructions);
std::unordered_map<Position, int> execute2(std::string &istructions);
uint64_t findSolution(std::unordered_map<Position, int> &houses);

} // namespace day03

namespace std {
    template <>
    struct hash<day03::Position> {
        size_t operator() (const day03::Position& pos) const {
            return (pos.x << 16) | pos.y;
        }
    };
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
    std::cout << day03::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day03::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day03::process1(std::string file) {
    std::string istructions = readAsSingleLine(file);
    auto houses = execute(istructions);
    return findSolution(houses);
}

uint64_t day03::process2(std::string file) {
    std::string istructions = readAsSingleLine(file);
    auto houses = execute2(istructions);
    return findSolution(houses);
}

std::unordered_map<day03::Position, int> day03::execute(std::string &istructions) {
    std::unordered_map<Position, int> houses;
    Position pos;
    houses.insert(std::make_pair(pos, 1));
    for(auto i : istructions) {
        switch (i) {
            case '>':
                pos.x++;
                break;
            case '<':
                pos.x--;
                break;
            case '^':
                pos.y++;
                break;
            case 'v':
                pos.y--;
                break;
            default:
                continue;
        }
        auto it = houses.find(pos);
        if (it != houses.end()) {
            it->second++;
        } else {
            houses.insert(std::make_pair(pos, 1));
        }
    }
    return houses;
}

std::unordered_map<day03::Position, int> day03::execute2(std::string &istructions) {
    std::unordered_map<Position, int> houses;
    Position posSanta;
    Position posRobot;
    houses.insert(std::make_pair(posSanta, 2));
    bool santaTurn = true;
    for(auto i : istructions) {
        Position *curPos;
        if (santaTurn) {
            curPos = &posSanta;
        } else {
            curPos = &posRobot;
        }
        switch (i) {
            case '>':
                curPos->x++;
                break;
            case '<':
                curPos->x--;
                break;
            case '^':
                curPos->y++;
                break;
            case 'v':
                curPos->y--;
                break;
            default:
                continue;
        }
        auto it = houses.find(*curPos);
        if (it != houses.end()) {
            it->second++;
        } else {
            houses.insert(std::make_pair(*curPos, 1));
        }
        santaTurn = !santaTurn;
    }
    return houses;
}

uint64_t day03::findSolution(std::unordered_map<Position, int> &houses) {
    return houses.size();
}