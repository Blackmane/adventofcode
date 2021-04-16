/**
 * @file    day23.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    12 Gen 2021
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
#include <forward_list>
#include <string>
#include <vector>

std::string INPUT = "398254716";

namespace day23 {


class Game {
public:
    Game(std::string order);
    uint64_t play(uint64_t steps);
protected:
    std::vector<uint64_t> cups;
    size_t len = 0;
    void playStep();
    uint64_t solution();
};

class Game2 {
public:
    Game2(std::string order, uint64_t count);
    uint64_t play(uint64_t steps);
private:
    std::vector<uint64_t> cups;
    size_t len = 0;
    size_t index = 0;
    void playStep();
    uint64_t solution();
};

uint64_t process1();
uint64_t process2();

} // namespace day23


// ===== ===== ===== Main ===== ===== ===== 
int main () {

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day23::process1() << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day23::process2() << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day23::process1() {
    Game game(INPUT);
    return game.play(100);
}


uint64_t day23::process2() {
    Game2 game(INPUT, 1000000);
    return game.play(10000000);
}

// ===== ===== ===== Implementations ===== ===== ===== 


day23::Game::Game(std::string order) {
    // Save cups value
    for (auto cup : order) {
        cups.push_back(cup - '0');
    }
    len = cups.size();
}


uint64_t day23::Game::play(uint64_t steps) {
    // Do all steps
    for (size_t i = 0; i < steps; i++) {
        playStep();
    }
    return solution();
}


void day23::Game::playStep() {
    // Step start from 0s cup
    uint64_t current = cups[0];
    // Picked cups at index 1 to 3
    uint64_t picked[3] = {cups[1], cups[2], cups[3]};
    // Calculate destination cup
    uint64_t destination = current;
    bool found = true;
    while (found) {
        destination = destination == 1 ? len : destination - 1;
        // Check destination presence in picked values
        found = picked[0] == destination || 
                picked[1] == destination || 
                picked[2] == destination;
    }
    // Copy cups
    size_t j = 0;
    for (size_t i = 4; i < len; i++) {
        cups[j] = cups[i];
        j++;
        if (cups[i] == destination) {
            // Copy picked values
            cups[j++] = picked[0];
            cups[j++] = picked[1];
            cups[j++] = picked[2];
        }
    }
    // Copy current cup to the end
    cups[len-1] = current;
}


uint64_t day23::Game::solution() {
    uint64_t sol = 0;
    // Print from 1 to end
    bool found = false;
    for (auto cup : cups) {
        if (found) {
            sol += cup;
            sol *= 10;
        }
        if (cup == 1) {
            found = true;
        }
    }
    // Print from start to end
    for (auto cup : cups) {
        if (cup == 1) {
            break;
        }
        sol += cup;
        sol *= 10;
    }
    return sol / 10;
}


// ===== ===== ===== game2 ===== ===== ===== 

day23::Game2::Game2(std::string order, uint64_t count) {
    cups.reserve(count+1);
    // Save cups value
    auto leng = order.length();
    index = order[0] - '0';
    uint64_t cur = index;
    for (size_t i = 1; i < leng; i++) {
        cups[cur] = order[i] - '0';
        cur = order[i] - '0';
    }
    // Populate remaning numbers
    for (size_t i = order.length() + 1; i <= count; i++) {
        cups[cur] = i;
        cur = i;
    }
    cups[count] = index;
    len = count;
}


uint64_t day23::Game2::play(uint64_t steps) {
    // Do all steps
    for (size_t i = 0; i < steps; i++) {
        playStep();
    }
    return solution();
}

void day23::Game2::playStep() {
    // Pick numbers
    uint64_t picked = cups[index];
    uint64_t pickedLast = cups[cups[picked]];
    // Calculate destination cup
    uint64_t destination = index;
    bool found = true;
    while (found) {
        destination = destination == 1 ? len : destination - 1;
        // Check destination presence in picked values
        found = picked == destination || 
                cups[picked] == destination || 
                pickedLast == destination;
    }
    // Connect index cup to the one after picked cups
    cups[index] = cups[pickedLast];
    // Connect picked after destination
    uint64_t temp = cups[destination];
    cups[destination] = picked;
    cups[pickedLast] = temp;
    // Next index
    index = cups[index];
}


uint64_t day23::Game2::solution() {
    uint64_t mul = cups[1] * cups[cups[1]];
    return mul;
}
