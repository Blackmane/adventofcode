/**
 * @file    day05.cpp
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

#include "day05.h"

#include "common.h"

#include <algorithm>
#include <assert.h>
#include <map>

typedef std::map<std::pair<uint64_t, uint64_t>, uint64_t> VentMap;

constexpr int direction(uint64_t a, uint64_t b)
{
    return a < b ? 1 : a > b ? -1 : 0;
}

std::string findSolution1(std::vector<std::string> *coordinates)
{
    VentMap ventMap;
    for (auto &coordinate : *coordinates) {
        std::replace(coordinate.begin(), coordinate.end(), ',', ' ');
        auto values = parse::getIntegers(coordinate);
        assert(values.size() == 4);
        if ((values[0] == values[2]) || (values[1] == values[3])) {
            const int x_direction = direction(values[0], values[2]);
            const int y_direction = direction(values[1], values[3]);
            const int steps = std::max(std::abs((int64_t)values[2] - (int64_t)values[0]),
                                       std::abs((int64_t)values[3] - (int64_t)values[1]));
            for (int i = 0, x = values[0], y = values[1]; i <= steps; ++i, x += x_direction, y += y_direction) {
                ventMap[std::make_pair(x, y)]++;
            }
        }
    }
    uint64_t count = 0;
    for (auto &point : ventMap) {
        if (point.second > 1) {
            count++;
        }
    }

    return std::to_string(count);
}

std::string findSolution2(std::vector<std::string> *coordinates)
{
    VentMap ventMap;
    for (auto &coordinate : *coordinates) {
        std::replace(coordinate.begin(), coordinate.end(), ',', ' ');
        auto values = parse::getIntegers(coordinate);
        assert(values.size() == 4);
        if ((values[0] == values[2]) || (values[1] == values[3]) ||
            (std::abs((int64_t)values[0] - (int64_t)values[2]) == std::abs((int64_t)values[1] - (int64_t)values[3]))) {
            auto x_direction = direction(values[0], values[2]);
            auto y_direction = direction(values[1], values[3]);
            uint64_t steps = std::max(std::abs((int64_t)values[2] - (int64_t)values[0]),
                                  std::abs((int64_t)values[3] - (int64_t)values[1]));
            for (uint64_t i = 0, x = values[0], y = values[1]; i <= steps; ++i, x += x_direction, y += y_direction) {
                ventMap[std::make_pair(x, y)]++;
            }
        }
    }
    uint64_t count = 0;
    for (auto &point : ventMap) {
        if (point.second > 1) {
            count++;
        }
    }

    return std::to_string(count);
}

std::string day05::process1(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    std::string result = findSolution1(&valueList);
    return result;
}

std::string day05::process2(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    std::string result = findSolution2(&valueList);
    return result;
}
