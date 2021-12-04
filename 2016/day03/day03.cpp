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

#include <assert.h>

bool isTriangle(uint64_t A, uint64_t B, uint64_t C)
{
    return (A + B > C) && (B + C > A) && (C + A > B);
}

bool isTriangle(std::vector<uint64_t> sides)
{
    assert(sides.size() >= 3);
    return isTriangle(sides[0], sides[1], sides[2]);
}

std::string findSolution1(std::vector<std::string> *values)
{
    int count = 0;
    for (auto &value : *values) {
        auto integers = parse::getIntegers(value);
        if (isTriangle(integers)) {
            count++;
        }
    }
    return std::to_string(count);
}

std::string findSolution2(std::vector<std::string> *values)
{
    auto len = values->size();
    std::vector<std::array<uint64_t, 3>> list;
    for (auto &value : *values) {
        auto integers                = parse::getIntegers(value);
        std::array<uint64_t, 3> line = { integers[0], integers[1],
                                         integers[2] };
        list.emplace_back(line);
    }

    uint64_t count = 0;
    for (size_t i = 2; i < len; i += 3) {
        for (size_t j = 0; j < 3; j++) {
            if (isTriangle(list[i - 2][j], list[i - 1][j], list[i][j])) {
                count++;
            }
        }
    }

    return std::to_string(count);
}

std::string process1(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);

    std::string result = findSolution1(&valueList);
    return result;
}

std::string process2(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);

    std::string result = findSolution2(&valueList);
    return result;
}
