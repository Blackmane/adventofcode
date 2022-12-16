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

std::string findSolution1(std::vector<std::string> *values)
{
    auto len = values->at(0).size();
    std::vector<uint64_t> countOnes(len, 0);

    for (auto &value : *values) {
        for (size_t i = 0; i < len; ++i) {
            if (value[i] == '1') {
                countOnes[i]++;
            }
        }
    }
    uint64_t n = values->size();

    uint64_t gammaRate   = 0;
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

std::vector<uint64_t> mostCommon(std::vector<std::string> *values)
{
    auto len = values->at(0).size();
    std::vector<uint64_t> countOnes(len, 0);

    for (auto &value : *values) {
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

std::string findSolution2(std::vector<std::string> *values)
{
    // Is ordered
    auto len    = values->at(0).size();
    size_t from = 0;
    size_t to   = values->size() - 1;
    for (size_t j = 0; j < len; ++j) {
        auto diff     = to - from + 1;
        auto half     = diff / 2;
        int isPair    = diff % 2;
        char chalf    = values->at(from + half - 1).at(j);
        char chalfone = values->at(from + half).at(j);
        if ((isPair == 0 && chalf != chalfone) || chalfone == '1') {
            // Pair or more 1 => 1
            do {
                from++;
            } while (values->at(from).at(j) == '0' && from < to);
        } else {
            // More 0 => 0
            do {
                to--;
            } while (values->at(to).at(j) == '1' && from < to);
        }
        if (from == to) {
            // Found
            break;
        }
    }
    uint64_t oxigenRate = convert::fromBinary(values->at(from));

    from = 0;
    to   = values->size() - 1;
    for (size_t j = 0; j < len; ++j) {
        auto diff     = to - from + 1;
        auto half     = diff / 2;
        int isPair    = diff % 2;
        char chalf    = values->at(from + half - 1).at(j);
        char chalfone = values->at(from + half).at(j);
        if ((isPair == 0 && chalf != chalfone) || chalfone == '1') {
            // Pair or more 1 => 0
            // So decrease 'to'
            do {
                to--;
            } while (values->at(to).at(j) == '1' && from < to);
        } else {
            // More 0 => 1
            // So increase 'from'
            do {
                from++;
            } while (values->at(from).at(j) == '0' && from < to);
        }
        if (from == to) {
            // Found
            break;
        }
    }
    uint64_t co2Rate = convert::fromBinary(values->at(from));

    return std::to_string(oxigenRate * co2Rate);
}

std::string day03::process1(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);

    std::string result = findSolution1(&valueList);
    return result;
}

std::string day03::process2(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    std::sort(valueList.begin(), valueList.end());

    std::string result = findSolution2(&valueList);
    return result;
}
