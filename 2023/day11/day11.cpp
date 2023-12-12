/**
 * @file    day11.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    11 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day11.h"

#include "common.h"

std::pair<size_t, size_t> getExpandedPosition(std::pair<size_t, size_t> pos, std::vector<size_t> &emptyLines,
                                              std::vector<size_t> &emptyColumns, size_t expanding)
{
    size_t x = pos.first;
    for (auto &&l : emptyLines) {
        if (pos.first > l) {
            x += expanding - 1;
        } else {
            break;
        }
    }
    size_t y = pos.second;
    for (auto &&c : emptyColumns) {
        if (pos.second > c) {
            y += expanding - 1;
        } else {
            break;
        }
    }
    return { x, y };
}

uint64_t manhattanDistance(std::pair<size_t, size_t> a, std::pair<size_t, size_t> b)
{
    return std::abs(long(a.first - b.first)) + std::abs(long(a.second - b.second));
}

uint64_t getDistanceSum(std::vector<std::string> &map, size_t expanding)
{
    std::vector<size_t> emptyLines;
    for (int i = 0, n = map.size(); i < n; i++) {
        bool empty = std::all_of(map[i].begin(), map[i].end(), [](char c) { return c == '.'; });
        if (empty) {
            emptyLines.push_back(i);
        }
    }
    std::vector<size_t> emptyColumns;
    for (int j = 0, m = map[0].size(); j < m; j++) {
        bool empty = true;
        for (int i = 0, n = map.size(); i < n; i++) {
            if (map[i][j] != '.') {
                empty = false;
                break;
            }
        }
        if (empty) {
            emptyColumns.push_back(j);
        }
    }

    std::vector<std::pair<int, int>> stars;
    for (int i = 0, n = map.size(); i < n; i++) {
        for (int j = 0, m = map[0].size(); j < m; j++) {
            if (map[i][j] == '#') {
                stars.push_back(getExpandedPosition({ i, j }, emptyLines, emptyColumns, expanding));
            }
        }
    }

    uint64_t sum = 0;
    for (int i = 0, n = stars.size(); i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            sum += manhattanDistance(stars[i], stars[j]);
        }
    }
    return sum;
}

std::string day11::process1(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    return std::to_string(getDistanceSum(map, 2));
}

std::string day11::process2(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    return std::to_string(getDistanceSum(map, 1000000));
}