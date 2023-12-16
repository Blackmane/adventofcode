/**
 * @file    day16.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    16 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day16.h"

#include "common.h"

uint64_t getEnergized(std::vector<std::string> &map, std::pair<int8_t, int8_t> initialPos,
                      std::pair<int8_t, int8_t> initialDir)
{
    const int n = map.size();
    const int m = map[0].size();
    std::vector<uint8_t> empty(m, 0);
    std::vector<std::vector<uint8_t>> energizedMap(n, empty);
    std::set<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> visited;

    std::function<void(std::pair<int8_t, int8_t> pos, std::pair<int8_t, int8_t>)> laser;
    laser = [&](std::pair<int8_t, int8_t> pos, std::pair<int8_t, int8_t> dir) {
        if (pos.first < 0 || pos.first >= n || pos.second < 0 || pos.second >= m) {
            return;
        }

        std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> key = { pos.first, pos.second, dir.first, dir.second };
        if (visited.find(key) != visited.end()) {
            energizedMap[pos.first][pos.second] += 100;
            return;
        } else {
            visited.insert(key);
        }

        energizedMap[pos.first][pos.second]++;

        switch (map[pos.first][pos.second]) {
            case '-':
                if (dir.first != 0) {
                    // Split
                    laser({ pos.first, pos.second - 1 }, { 0, -1 });
                    laser({ pos.first, pos.second + 1 }, { 0, 1 });
                    return;
                }
                break;
            case '|':
                if (dir.second != 0) {
                    // Split
                    laser({ pos.first - 1, pos.second }, { -1, 0 });
                    laser({ pos.first + 1, pos.second }, { 1, 0 });
                    return;
                }
                break;
            case '/':
                std::swap(dir.first, dir.second);
                dir.first *= -1;
                dir.second *= -1;
                break;
            case '\\':
                std::swap(dir.first, dir.second);
                break;
            case '.':
            default:
                break;
        }
        laser({ pos.first + dir.first, pos.second + dir.second }, dir);
    };
    laser(initialPos, initialDir);

    uint64_t count = 0;
    for (auto &energyLine : energizedMap) {
        for (auto energy : energyLine) {
            if (energy > 0) {
                count++;
            }
        }
    }
    return count;
}

std::string day16::process1(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    return std::to_string(getEnergized(map, { 0, 0 }, { 0, 1 }));
}

std::string day16::process2(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    uint64_t max = 0;
    const int n = map.size();
    const int m = map[0].size();
    for (int i = 0; i < n; i++) {
        auto res = getEnergized(map, { i, 0 }, { 0, 1 });
        max = max < res ? res : max;
        res = getEnergized(map, { i, m - 1 }, { 0, -1 });
        max = max < res ? res : max;
    }
    for (int j = 0; j < m; j++) {
        auto res = getEnergized(map, { 0, j }, { 1, 0 });
        max = max < res ? res : max;
        res = getEnergized(map, { n - 1, j }, { -1, 0 });
        max = max < res ? res : max;
    }
    return std::to_string(max);
}