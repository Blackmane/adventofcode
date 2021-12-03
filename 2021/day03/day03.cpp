/**
 * @file    day03.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    03 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day03.h"
#include "common.h"
#include <algorithm>

std::string findSolution1(std::vector <std::string> *values) {
    auto len = values->at(0).size();
    std::vector<uint64_t> countOnes(len, 0);
    
    for (auto &value: *values) {
        for (size_t i = 0; i < len; ++i) {
            if (value[i] == '1') {
                countOnes[i]++;
            }
        }
    }
    uint64_t n = values->size();

    uint64_t gammaRate = 0;
    uint64_t epsilonRate = 0;
    for (size_t i = 0; i < len; ++i) {
        gammaRate *= 2;
        epsilonRate *= 2;
        if (countOnes[i] > n / 2) {
            gammaRate++;
        } else {
            epsilonRate++;
        }
    }

    return std::to_string(gammaRate * epsilonRate);
}

std::vector<uint64_t> mostCommon(std::vector <std::string> *values) {
    auto len = values->at(0).size();
    std::vector<uint64_t> countOnes(len, 0);
    
    for (auto &value: *values) {
        for (size_t i = 0; i < len; ++i) {
            if (value[i] == '1') {
                countOnes[i]++;
            }
        }
    }
    uint64_t n = values->size();

    for (size_t i = 0; i < len; ++i) {
        std::cout << countOnes[i] << std::endl;
        if (countOnes[i] < n / 2) {
            countOnes[i] = 0;
        } else if (countOnes[i] == n / 2) {
            countOnes[i] = 2;
        } else {
            countOnes[i] = 1;
        }
    }
    return countOnes;
}

std::string findSolution2(std::vector <std::string> *values) {
    // Is ordered
    auto len = values->at(0).size();
    size_t from = 0;
    size_t to = values->size() - 1;
    for (size_t j = 0; j < len; ++j) {
        size_t countZero = 0;
        for (size_t i = from; i <= to; ++i) {
            if (values->at(i).at(j) == '0') {
                countZero++;
            } else {
                // Is ordered, so when found a '1' is finished
                break;
            }
        }
        auto half = (to - from + 1) / 2 ;
        std::cout << "Count 0 are : " << countZero << " of " << half << std::endl;
        if (countZero <= half) {
            // Oxigen: most common or 1 if equal
            // 1
            // So increase from
            do {
                from++;
            } while (values->at(from).at(j) == '0' && from < to );
        } else {
            //0
            // So decrease to
            do {
                to--;
            } while (values->at(to).at(j) == '1' && from < to );
        }
        if (from == to) {
            // Found
            break;
        }
    }
    uint64_t oxigenRate = 0;
    for (size_t i = 0; i < len; ++i) {
        oxigenRate *= 2;
        if (values->at(from).at(i) == '1') {
            oxigenRate++;
        }
    }


    from = 0;
    to = values->size() - 1;
    for (size_t j = 0; j < len; ++j) {
        size_t countZero = 0;
        for (size_t i = from; i <= to; ++i) {
            if (values->at(i).at(j) == '0') {
                countZero++;
            } else {
                // Is ordered, so when found a '1' is finished
                break;
            }
        }
        auto half = (to - from + 1) / 2 ;
        if (countZero <= half) {
            // Co2: less common or 0 if equal
            // 0
            // So decrease 'to'
            do {
                to--;
            } while (values->at(to).at(j) == '1' && from < to );
        } else {
            //1
            // So increase 'from'
            do {
                from++;
            } while (values->at(from).at(j) == '0' && from < to );

        }
        if (from == to) {
            // Found
            break;
        }
    }
    uint64_t co2Rate = 0;
    for (size_t i = 0; i < len; ++i) {
        co2Rate *= 2;
        if (values->at(from).at(i) == '1') {
            co2Rate++;
        }
    }

    return std::to_string(oxigenRate * co2Rate);
}

std::string process1(std::string file) {
    std::vector <std::string> valueList;
    parse::read_all(file, &valueList);

    std::string result = findSolution1(&valueList);
    return result;
}


std::string process2(std::string file) {
    std::vector <std::string> valueList;
    parse::read_all(file, &valueList);
    std::sort (valueList.begin(), valueList.end());

    std::string result = findSolution2(&valueList);
    return result;
}

