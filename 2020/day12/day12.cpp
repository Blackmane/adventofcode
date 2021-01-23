/**
 * @file    day12.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    12 Dec 2020
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

namespace day12 {

struct Action {
    char type;
    uint64_t value = 0;
};

const int NORD = 0;
const int EST  = 1;
const int SUD  = 2;
const int WEST = 3;

struct Position {
    int dir = EST;
    int64_t latitude  = 0;
    int64_t longitude = 0;
    uint64_t manhattanDistance() {return abs(latitude) + abs(longitude);};
};

struct PositionWaypoint {
    int64_t waypointLat = 1;
    int64_t waypointLon = 10;
    int64_t latitude  = 0;
    int64_t longitude = 0;
    uint64_t manhattanDistance() {return abs(latitude) + abs(longitude);};
    void rotate() { // Rotate right
        int temp = waypointLat;
        waypointLat = -1 * waypointLon;
        waypointLon = temp;
    };
};

/* 
Rotation right (clockwise) schema
10 E  4 N     4 Lat  10 Lon
 4 E 10 S   -10 Lat   4 Lon
10 O  4 S   - 4 Lat 1-10 Lon
 4 O 10 N    10 Lat - 4 Lon
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

uint64_t process1(std::string file);
uint64_t process2(std::string file);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto toAction = [](std::string part) -> Action {
    Action action;
    action.type = part[0];
    action.value = std::stol(part.substr(1, part.length()-1));

    return action;
};

auto foldl = [](Action action, Position pos) -> Position { 
    Position newPos(pos);
    // Apply action
    switch (action.type) {
    case 'N':
        newPos.latitude += action.value;
        break;
    case 'S':
        newPos.latitude -= action.value;
        break;
    case 'E':
        newPos.longitude += action.value;
        break;
    case 'W':
        newPos.longitude -= action.value;
        break;
    case 'L':
        newPos.dir = (newPos.dir - (action.value/90)) % 4;
        break;
    case 'R':
        newPos.dir = (newPos.dir + (action.value/90)) % 4;
        break;
    case 'F':
        switch (newPos.dir) {
        case NORD:
            newPos.latitude += action.value;
            break;
        case SUD:
            newPos.latitude -= action.value;
            break;
        case EST:
            newPos.longitude += action.value;
            break;
        case WEST:
            newPos.longitude -= action.value;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return newPos;
};

auto foldl2 = [](Action action, PositionWaypoint pos) -> PositionWaypoint { 
    int rotations = 0;
    PositionWaypoint newPos(pos);
    // Apply action
    switch (action.type) {
    case 'N':
        newPos.waypointLat += action.value;
        break;
    case 'S':
        newPos.waypointLat -= action.value;
        break;
    case 'E':
        newPos.waypointLon += action.value;
        break;
    case 'W':
        newPos.waypointLon -= action.value;
        break;
    case 'L':
        // Count rotation left as rotation right
        rotations = (4 - action.value/90) % 4;
        for (int i = 0; i < rotations; i++) {
            newPos.rotate();
        }
        break;
    case 'R':
        rotations = (action.value/90) % 4;
        for (int i = 0; i < rotations; i++) {
            newPos.rotate();
        }
        break;
    case 'F':
        for (uint64_t i = 0; i < action.value; i++) {
            newPos.latitude += newPos.waypointLat;
            newPos.longitude += newPos.waypointLon;
        }
        break;
    default:
        break;
    }
    return newPos;
};

} // namespace day12


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day12::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day12::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Solutions ===== ===== ===== 

uint64_t day12::process1(std::string file) {
    Position pos;
    Position result = parse<Action, Position>(file, '\n', 
                            toAction, 
                            foldl, pos);
    return result.manhattanDistance();
}

uint64_t day12::process2(std::string file) {
    PositionWaypoint pos;
    PositionWaypoint result = parse<Action, PositionWaypoint>(file, '\n', 
                            toAction, 
                            foldl2, pos);
    return result.manhattanDistance();
}