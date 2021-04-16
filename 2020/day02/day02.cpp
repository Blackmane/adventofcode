/**
 * @file    day02.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    02 Dec 2020
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

namespace day02 {

void checker (const std::string& filename);
bool checkPasswordConstraints(std::string password, char constraint, int min, int max);
bool checkPasswordConstraints2(std::string password, char constraint, int min, int max);

} // namespace day02

// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    day02::checker(inputFilename);

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 
void day02::checker (const std::string& filename) {
    std::ifstream source;
    source.open(filename);
    std::string line;
    int part1_counter = 0;
    int part2_counter = 0;
    while (std::getline(source, line)) {
        int min = 0;
        int max = 0;
        char constraint = '\0';
        std::string password;
        try {
            std::istringstream linestream(line);
            linestream >> min;
            linestream.get(); // -
            linestream >> max;
            linestream.get(); // 
            linestream >> constraint;
            linestream.get(); // :
            linestream.get(); // 
            std::getline (linestream, password);
            // 1-9 f: vrffffffxffnfbffff
            
            if (checkPasswordConstraints(password, constraint, min, max)) {
                part1_counter++;
            }
            if (checkPasswordConstraints2(password, constraint, min, max)) {
                part2_counter++;
            }
            
        } catch (const std::exception &e) {
            std::cout << "Error elaborating line: " << e.what() << std::endl;
            continue;
        }
    }

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << part1_counter << std::endl;
    std::cout << std::endl;

    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << part2_counter << std::endl;
    std::cout << std::endl;
}

bool day02::checkPasswordConstraints(std::string password, char constraint, int min, int max) {

    int length = password.length();
    int counter = 0;
    for (int i = 0; i < length; ++i) {
        if (constraint == password[i]) {
            counter++;
            if (counter > max) {
                return false;
            }
        }
    }

    return counter >= min;
}

bool day02::checkPasswordConstraints2(std::string password, char constraint, int min, int max) {
    if ( (password[min -1] == constraint) != (password[max -1] == constraint) ) {
        return true;
    }
    return false;
}