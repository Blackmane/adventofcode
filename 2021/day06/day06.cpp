/**
 * @file    day06.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    05 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day06.h"

#include "common.h"

void populate(std::vector<uint64_t> *fishes, std::vector<std::string> *valuelist)
{
    for (auto &value : *valuelist) {
        auto splitted = parse::split(value, ',');
        for (auto &val : splitted) {
            auto idx = std::stoll(val);
            fishes->at(idx)++;
        }
    }
}

std::string findSolution1(std::vector<std::uint64_t> *fishes, uint64_t days)
{
    uint64_t sevenIdx   = 0;
    uint64_t sevenValue = 0;
    uint64_t eightIdx   = 0;
    uint64_t eightValue = 0;
    for (size_t i = 0; i < days; i++) {
        // Save the new fishes of the day
        uint64_t nextIdx   = i % 7;
        uint64_t nextValue = fishes->at(nextIdx);
        // Add the now reproductive fishes
        fishes->at(i % 7) += sevenValue;
        // Save the young fishes and slide the yesterday fishes
        sevenIdx   = eightIdx;
        sevenValue = eightValue;
        eightIdx   = nextIdx;
        eightValue = nextValue;

    }
    // Add the young fishes
    fishes->at((sevenIdx + 2) % 7) += sevenValue;
    fishes->at((eightIdx + 2) % 7) += eightValue;

    uint64_t sum = 0;
    for (auto &fish : *fishes) {
        sum += fish;
    }

    return std::to_string(sum);
}

std::string process1(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    std::vector<uint64_t> fishes(7, 0);
    populate(&fishes, &valueList);
    std::string result = findSolution1(&fishes, 80);
    return result;
}

std::string process2(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    std::vector<uint64_t> fishes(7, 0);
    populate(&fishes, &valueList);
    std::string result = findSolution1(&fishes, 256);
    return result;
}
