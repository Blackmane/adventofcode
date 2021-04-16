/**
 * @file    day04.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    04 Dec 2020
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
#include <memory>
#include <map>
#include <regex>

namespace day04 {
/*
The hardest part was parse data from file.
Loading the data into a map therefore makes it easier to check whether all fields are present or not.
In the second part it was easy to think of regex to control some fields.
It was useful to create some test functions (no longer present here) to verify the correct functioning of the controls.
*/

typedef std::unique_ptr<std::map<std::string, std::string>> Passport;

std::pair<int, int> counter (const std::string& filename);
void setPassport(Passport &pass, std::string data);
void addToPassport(Passport &pass, std::string data);
bool checkPassport(Passport &pass);
bool checkPassport2(Passport &pass);
bool checkData(std::string field, std::string data);

} // namespace day04


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);
    auto counters = day04::counter(inputFilename);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << counters.first << std::endl;
    std::cout << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << counters.second << std::endl;
    std::cout << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 
std::pair<int, int> day04::counter (const std::string& filename) {

    std::ifstream source;
    source.open(filename);
    std::string line;
    Passport passport = Passport(new std::map<std::string, std::string>);
    int count = 0;
    int count2 = 0;
    while (std::getline(source, line)) {
        if (line != "") {
            setPassport(passport, line);
        } else {
            // Passport end
            if (checkPassport(passport)) {
                count++;
                if (checkPassport2(passport)) {
                    count2++;
                }
            }
            // New passport
            passport = Passport(new std::map<std::string, std::string>);
        }
    }
    // Last passport
    if (checkPassport(passport)) {
        count++;
        if (checkPassport2(passport)) {
            count2++;
        }
    }
    return std::pair<int, int>(count, count2);
}


void day04::setPassport(Passport &pass, std::string data) {

    std::string delimiterData = " ";
    size_t last = 0; 
    size_t next = 0; 
    while ((next = data.find(delimiterData, last)) != std::string::npos) {
        addToPassport(pass, data.substr(last, next-last));
        last = next + 1; 
    } 
    addToPassport(pass, data.substr(last));
}


void day04::addToPassport(Passport &pass, std::string data) {

    std::string delimiterData = ":";
    size_t last = 0; 
    size_t next = data.find(delimiterData, last); 
    
    std::string field = data.substr(0, next);
    std::string field_data = data.substr(next+1);
    pass->insert(std::make_pair(field, field_data));
}


bool day04::checkPassport(Passport &pass) {

    return pass->find("byr") != pass->end()
        && pass->find("iyr") != pass->end()
        && pass->find("eyr") != pass->end()
        && pass->find("hgt") != pass->end()
        && pass->find("hcl") != pass->end()
        && pass->find("ecl") != pass->end()
        && pass->find("pid") != pass->end();
}


bool day04::checkPassport2(Passport &pass) {

    for (auto it = pass->begin(); it != pass->end(); ++it ) {
        if (!checkData(it->first, it->second)) {
            return false;
        }
    }
    return true;
}


bool day04::checkData(std::string field, std::string data) {

    if (field == "byr") {
        int year = std::stoi(data);
        return year >= 1920 && year <= 2002;

    } else if (field == "iyr") {
        int year = std::stoi(data);
        return year >= 2010 && year <= 2020;


    } else if (field == "eyr") {
        int year = std::stoi(data);
        return year >= 2020 && year <= 2030;

    } else if (field == "hgt") {
        if (std::regex_match (data, std::regex("1\\d{2}cm") )) {
            int height = std::stoi(data.substr(0, 3));
            return height >= 150 && height <= 193;

        } else if (std::regex_match (data, std::regex("\\d{2}in") )) {
            int height = std::stoi(data.substr(0, 2));
            return height >= 59 && height <= 76;

        }
        return false;

    } else if (field == "hcl") {
        return std::regex_match (data, std::regex("#[0-9a-f]{6}") );

    } else if (field == "ecl") {
        return std::regex_match (data, std::regex("amb|blu|brn|gry|grn|hzl|oth") );

    } else if (field == "pid") {
        return std::regex_match (data, std::regex("\\d{9}") );
    }
    return true;
}