/**
 * @file    day01.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    30 Nov 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day01.h"
#include "common.h"

std::string findSolution1(std::vector <uint64_t> *values) {
    uint64_t prev = UINT64_MAX;
    int count = 0;
    for (auto &value: *values) {
        if (prev < value) {
            count++;
        }
        prev = value;
    }
    return std::to_string(count);
}

std::string findSolution2(std::vector <uint64_t> *values) {
    uint64_t prev = UINT64_MAX;
    int count = 0;
    for (size_t j = 2, n = values->size(); j < n; j++) {
        auto sum = values->at(j - 2) + values->at(j - 1) + values->at(j);
        if (prev < sum) {
            count++;
        }
        prev = sum;
    }
    return std::to_string(count);
}


std::string process1(std::string file) {
    std::vector <uint64_t> valueList;
    parse::read_all_integers(file, &valueList);

    std::string result = findSolution1(&valueList);
    return result;
}


std::string process2(std::string file) {
    std::vector <uint64_t> valueList;
    parse::read_all_integers(file, &valueList);

    std::string result = findSolution2(&valueList);
    return result;
}

