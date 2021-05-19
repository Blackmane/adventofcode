/**
 * @file    day01.cpp
 * @brief   
 * @project advent of code 2016
 * 
 * @author  Niccolò Pieretti
 * @date    17 May 2021
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
#include <set>

namespace day01 {

enum Direction {
    north = 0,
    east = 1,
    sud = 2,
    west = 3,
};

class Position {
public:
    std::pair<int64_t, int64_t> getPosition();
    uint getDistace();
    void turnRight();
    void turnLeft();
    void walk(uint steps);
private:
    Direction _direction = Direction::north;
    int64_t _north = 0;
    int64_t _east = 0;
};


template<class L, class S>
void read(std::string inputFilename, char delimiter, 
        std::function <void(S, L)> insert, S structure) {
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    while (std::getline(source, part, delimiter)) {
        insert(structure, part);
    }
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

uint64_t findSolution(std::vector<std::string> * list);
uint64_t findSolution2(std::vector<std::string> * list);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto push_back = [](std::vector<std::string> * list, std::string part) -> void { 
    list->push_back(part);
};

auto map2 = [](std::string part) -> uint64_t { 

    return 0;
};


} // namespace day01


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day01::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day01::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day01::process1(std::string file) {
    std::vector<std::string> stepsList;
    read<std::string, std::vector<std::string>*>(file, '\n', push_back, &stepsList);

    uint64_t result = findSolution(&stepsList);
    return result;
}

uint64_t day01::process2(std::string file) {
    std::vector<std::string> stepsList;
    read<std::string, std::vector<std::string>*>(file, '\n', push_back, &stepsList);

    uint64_t result = findSolution2(&stepsList);
    return result;
}


uint64_t day01::findSolution(std::vector<std::string> * list) {
    Position pos;
    for(auto mov : *list)
    {
        auto steps = std::stoi(mov.substr(1, mov.length() - 1));
        switch (mov[0])
        {
        case 'L':
            pos.turnLeft();
            break;
        case 'R':
            pos.turnRight();
            break;
        }
        pos.walk(steps);
    }
    return pos.getDistace();
}

uint64_t day01::findSolution2(std::vector<std::string> * list) {
    std::set<std::pair<int64_t, int64_t>> visited;
    Position pos;
    for(auto mov : *list)
    {
        auto steps = std::stoi(mov.substr(1, mov.length() - 1));
        switch (mov[0])
        {
        case 'L':
            pos.turnLeft();
            break;
        case 'R':
            pos.turnRight();
            break;
        }
        for (auto i = 0; i < steps; i++) {
            pos.walk(1);
            auto nowPos = pos.getPosition();
            auto it = visited.find(nowPos);
            if (it == visited.end()) {
                visited.insert(nowPos);
            } else {
                return pos.getDistace();
            }
        }
    }
    return 0;
}


std::pair<int64_t, int64_t> day01::Position::getPosition() {
    return std::pair<int64_t, int64_t>(_north, _east);
}

uint day01::Position::getDistace() {
    return std::abs(_north) + std::abs(_east);
}

void day01::Position::turnRight() {
    _direction = static_cast<Direction>( (_direction + 1) % 4 );
}

void day01::Position::turnLeft() {
    _direction = static_cast<Direction>( (_direction + 3) % 4 );
}

void day01::Position::walk(uint steps) {
    switch (_direction)
    {
    case Direction::north:
        _north += steps;
        break;
    case Direction::sud:
        _north -= steps;
        break;
    case Direction::east:
        _east += steps;
        break;
    case Direction::west:
        _east -= steps;
        break;
    }
}