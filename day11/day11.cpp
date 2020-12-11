/**
 * @file    day11.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    11 Dec 2020
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
#include <vector>
#include <functional>


namespace day11 {

/*
Game of seats
*/

enum Seat {
    floor,
    empty,
    occupied
};

typedef std::vector<std::vector<Seat>> WaitingArea;


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

uint64_t findSolution(WaitingArea &vector, uint64_t rule, 
                                        std::function <uint64_t(WaitingArea &, size_t, size_t)> near);
std::pair<WaitingArea, uint64_t> calcNewWaitingArea(WaitingArea &waitingArea, uint64_t rule,
                                        std::function <uint64_t(WaitingArea &, size_t, size_t)> near);
uint64_t near(WaitingArea & area, size_t r, size_t c);
uint64_t seen(WaitingArea & area, size_t r, size_t c);



// ===== ===== ===== Lambdas ===== ===== ===== 

auto toSeats = [](std::string part) -> std::vector<Seat> {
    std::vector<Seat> seats;
    size_t n = part.size();
    for (size_t i = 0; i < n; ++i) {
        Seat seat = floor;
        if (part[i] == 'L') {
            seat = empty;
        }else if (part[i] == '#') {
            seat = occupied;
        }
        seats.push_back(seat);
    }
    
    return seats;
};

auto insert = [](std::vector<Seat> seats, WaitingArea* waitingArea ) {
    waitingArea->push_back(seats);
};

} // namespace day11


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day11::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day11::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Solutions ===== ===== ===== 

uint64_t day11::process1(std::string file) {
    std::vector<std::vector<Seat>> vector;
    read<std::vector<Seat>, WaitingArea*>(file, '\n', 
                toSeats, 
                insert, &vector);

    uint64_t result = day11::findSolution(vector, 4, near);
    return result;
}

uint64_t day11::process2(std::string file) {
    std::vector<std::vector<Seat>> vector;
    read<std::vector<Seat>, WaitingArea*>(file, '\n', 
                toSeats, 
                insert, &vector);

    uint64_t result = day11::findSolution(vector, 5, seen);
    return result;
}

// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day11::findSolution(WaitingArea &waitingArea, uint64_t rule, std::function <uint64_t(WaitingArea&, size_t, size_t)> near) {
    bool satisfied = false;
    auto newarea = calcNewWaitingArea(waitingArea, rule, near);
    uint64_t occupied = newarea.second;
    while (!satisfied) {
        newarea = calcNewWaitingArea(newarea.first, rule, near);
        // Terminate if the solution is the same (base on number of the occupied seats)
        satisfied = occupied == newarea.second;
        occupied = newarea.second;
    }

    return occupied;
}

std::pair<day11::WaitingArea, uint64_t> day11::calcNewWaitingArea(WaitingArea &waitingArea, uint64_t rule, std::function <uint64_t(WaitingArea&, size_t, size_t)> near) {
    // Apply rules on waiting area and get new area
    WaitingArea newArea(waitingArea);
    uint64_t people = 0;
    size_t row = waitingArea.size();
    size_t col = waitingArea[0].size();
    // Iterate every position
    for (size_t r = 0; r < row; r++) {
        for (size_t c = 0; c < col; c++) {
            // Check position status
            switch (waitingArea[r][c]) {
                case Seat::empty:
                    if (near(waitingArea, r, c) == 0) {
                        newArea[r][c] = occupied;
                        people++;
                    }
                    break;
                case Seat::occupied:
                    if (near(waitingArea, r, c) >= rule) {
                        newArea[r][c] = empty;
                    } else {
                        // Count as occupied
                        people++;
                    }
                    break;
                default:
                    // Floor: nothing to do
                    break;
            }
        }
    }

    return std::make_pair(newArea, people);
}

uint64_t day11::near(WaitingArea &area, size_t r, size_t c) {
    uint64_t near = 0;
    int64_t maxr = area.size();
    int64_t maxc = area[0].size();
    int directionsR[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int directionsC[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
    // Iterate directions
    for (size_t d = 0; d < 8; d++) {
        int64_t posr = r + directionsR[d];
        int64_t posc = c + directionsC[d];
        // Count if is a valid position (inside limits) and occupied
        if (posr >= 0 && posr < maxr && 
            posc >= 0 && posc < maxc && 
            area[posr][posc] == occupied) {
            near++;
        }
    }
    return near;
}

uint64_t day11::seen(WaitingArea &area, size_t r, size_t c) {
    uint64_t near = 0;
    size_t maxr = area.size();
    size_t maxc = area[0].size();
    int directionsR[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int directionsC[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
    // Iterate directions
    for (size_t d = 0; d < 8; d++) {
        // Check in a direction
        for (size_t i = r + directionsR[d], j = c + directionsC[d]; i<maxr && j<maxc; ) {
            if (area[i][j] != floor) {
                if (area[i][j] == occupied) {
                    near++;
                }
                // Check only the first not floor position
                break;
            }
            i += directionsR[d];
            j += directionsC[d];
        }
    }
    return near;
}
