/**
 * @file    day03.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    03 Dec 2020
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
#include <sstream>
#include <string>
#include <vector>

namespace day03 {
/*
The idea is simple, check the map as a matrix.
The movement to right must be "circular"  within the index of the matrix, 
so the modulo operation is important.
In the second part, however, the downward movement could be greater than one.
Therefore, iterating the vector with more than one step was not, initially, trivial.
The solution was to continue the iteration one step at a time, 
but check for the presence of the tree only if the movement is complete.
*/
std::vector<std::string> loader (const std::string& filename);
int countTree(std::vector<std::string> forest, int right, int down);

} // namespace day03

// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    std::vector<std::string> forest = day03::loader(inputFilename);
    int count = day03::countTree(forest, 3, 1);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << count << std::endl;
    std::cout << std::endl;
    
    // Part 2
    int mul = 1;
    std::cout << "Part2" << std::endl;
    mul *= day03::countTree(forest, 1, 1);
    mul *= day03::countTree(forest, 3, 1);
    mul *= day03::countTree(forest, 5, 1);
    mul *= day03::countTree(forest, 7, 1);
    mul *= day03::countTree(forest, 1, 2);
    std::cout << mul << std::endl;
    std::cout << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 
std::vector<std::string> day03::loader (const std::string& filename) {
    std::vector<std::string> forest;
    std::ifstream source;
    source.open(filename);
    std::string line;
    while (std::getline(source, line)) {
        forest.push_back(line);
    }
    return forest;
}

int day03::countTree(std::vector<std::string> forest, int right, int down) {
    int counter = 0;
    int position = 0;
    int deep = 0;
    for (auto line = std::begin(forest); line != std::end(forest); line++) {
        if (deep % down == 0) {
            if ((*line)[position] == '#') {
                counter++;
            }
            position = (position + right) % line->length();
        }
        deep++;
    }
    return counter;
}
