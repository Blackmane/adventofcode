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

void set(VentMap *map, uint64_t x, uint64_t y)
{
    auto point = std::pair<int64_t, int64_t>(x, y);
    auto it    = map->find(point);
    if (it != map->end()) {
        it->second++;
    } else {
        map->emplace(point, 1);
    }
}

std::string findSolution1(std::vector<std::string> *coordinates)
{
    VentMap ventMap;
    for (auto &coordinate : *coordinates) {
        std::replace(coordinate.begin(), coordinate.end(), ',', ' ');
        auto values = parse::getIntegers(coordinate);
        assert(values.size() == 4);

        if (values[0] == values[2]) {
            uint64_t maxi = std::max(values[1], values[3]);
            for (uint64_t i = std::min(values[1], values[3]); i <= maxi; ++i) {
                set(&ventMap, values[0], i);
            }
        } else if (values[1] == values[3]) {
            uint64_t maxi = std::max(values[0], values[2]);
            for (uint64_t i = std::min(values[0], values[2]); i <= maxi; ++i) {
                set(&ventMap, i, values[1]);
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

        if (values[0] == values[2]) {
            uint64_t maxi = std::max(values[1], values[3]);
            for (uint64_t i = std::min(values[1], values[3]); i <= maxi; ++i) {
                set(&ventMap, values[0], i);
            }
        } else if (values[1] == values[3]) {
            uint64_t maxi = std::max(values[0], values[2]);
            for (uint64_t i = std::min(values[0], values[2]); i <= maxi; ++i) {
                set(&ventMap, i, values[1]);
            }
        } else if (std::abs((int64_t)values[0] - (int64_t)values[2]) ==
                   std::abs((int64_t)values[1] - (int64_t)values[3])) {
            auto steps = std::abs((int64_t)values[0] - (int64_t)values[2]);
            bool straight =
                (values[0] < values[2] && values[1] < values[3]) || (values[0] > values[2] && values[1] > values[3]);
            auto xmin = std::min(values[0], values[2]);
            auto ymin = std::min(values[1], values[3]);
            auto ymax = std::max(values[1], values[3]);
            for (auto i = 0; i <= steps; ++i) {
                uint64_t x = xmin + i;
                uint64_t y = straight ? ymin + i : ymax - i;
                set(&ventMap, x, y);
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
