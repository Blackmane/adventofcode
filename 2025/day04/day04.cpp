/**
 * @file    day04.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    04 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day04.h"

#include "common.h"

#include <queue>

std::string day04::process1(std::string file)
{
    auto map = parse::read_all(file);
    uint64_t count = 0;
    for (int i = 0, n = map.size(); i < n; i++) {
        for (int j = 0, m = map[i].size(); j < m; j++) {
            if (map[i][j] != '@') {
                continue;
            }
            int c = 0;
            for (auto &&neighbour : matrix::neighbours8(i, j, n, m)) {
                if (map[neighbour.first][neighbour.second] == '@') {
                    c++;
                }
                if (c >= 4) {
                    break;
                }
            }
            if (c < 4) {
                count++;
            }
        }
    }
    return std::to_string(count);
}

std::string day04::process2(std::string file)
{
    auto map = parse::read_all(file);
    int n = map.size();
    int m = map[0].size();

    auto isGood = [&](size_t i, size_t j) -> bool {
        int c = 0;
        for (auto &&neighbour : matrix::neighbours8(i, j, n, m)) {
            if (map[neighbour.first][neighbour.second] == '@') {
                c++;
            }
            if (c >= 4) {
                return false;
            }
        }
        return true;
    };

    uint64_t count = 0;
    std::queue<std::pair<int, int>> list;
    auto check = [&](size_t i, size_t j) {
        if (map[i][j] != '@') {
            return;
        }
        if (isGood(i, j)) {
            count++;
            list.push({ i, j });
            map[i][j] = '.';
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            check(i, j);
        }
    }
    while (!list.empty()) {
        auto [i, j] = list.front();
        list.pop();

        for (auto &&neighbour : matrix::neighbours8(i, j, n, m)) {
            check(neighbour.first, neighbour.second);
        }
    }

    return std::to_string(count);
}