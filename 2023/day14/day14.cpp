/**
 * @file    day14.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    14 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day14.h"

#include "common.h"

void tilt(std::vector<std::string> &map)
{
    auto n = map.size();
    auto m = map[0].size();
    for (size_t j = 0; j < m; j++) {
        size_t pos = 0;
        for (size_t i = 0; i < n; i++) {
            if (map[i][j] == 'O') {
                map[i][j] = '.';
                map[pos][j] = 'O';
                pos++;
            }
            if (map[i][j] == '#') {
                pos = i + 1;
            }
        }
    }
}

void tiltCycle(std::vector<std::string> &map)
{
    auto n = map.size();
    auto m = map[0].size();
    // North
    for (size_t j = 0; j < m; j++) {
        size_t pos = 0;
        for (size_t i = 0; i < n; i++) {
            if (map[i][j] == 'O') {
                map[i][j] = '.';
                map[pos][j] = 'O';
                pos++;
            }
            if (map[i][j] == '#') {
                pos = i + 1;
            }
        }
    }
    // West
    for (auto &line : map) {
        int pos = 0;
        for (size_t j = 0; j < m; j++) {
            if (line[j] == 'O') {
                line[j] = '.';
                line[pos] = 'O';
                pos++;
            }
            if (line[j] == '#') {
                pos = j + 1;
            }
        }
    }
    // South
    for (size_t j = 0; j < m; j++) {
        size_t pos = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (map[i][j] == 'O') {
                map[i][j] = '.';
                map[pos][j] = 'O';
                pos--;
            }
            if (map[i][j] == '#') {
                pos = i - 1;
            }
        }
    }
    // East
    for (auto &line : map) {
        int pos = m - 1;
        for (int j = m - 1; j >= 0; j--) {
            if (line[j] == 'O') {
                line[j] = '.';
                line[pos] = 'O';
                pos--;
            }
            if (line[j] == '#') {
                pos = j - 1;
            }
        }
    }
}

uint64_t totalLoad(std::vector<std::string> &map)
{
    uint64_t total = 0;
    auto n = map.size();
    for (auto &line : map) {
        for (auto &c : line) {
            if (c == 'O') {
                total += n;
            }
        }
        n--;
    }
    return total;
}

std::string day14::process1(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    tilt(map);
    return std::to_string(totalLoad(map));
}

std::string mapToLine(const std::vector<std::string> &map)
{
    std::string result;
    for (auto &line : map) {
        result.append(line);
    }
    return result;
}

std::string day14::process2(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);

    std::map<std::string, uint64_t> executions;
    uint64_t n = 1000000000;
    for (uint64_t i = 0; i < n; i++) {
        tiltCycle(map);

        auto lineMap = mapToLine(map);
        auto it = executions.find(lineMap);
        if (it == executions.end()) {
            executions.insert({ lineMap, i });
        } else {
            uint64_t cycle = i - it->second;
            i += ((n - i) / cycle) * cycle;
        }
    }
    return std::to_string(totalLoad(map));
}