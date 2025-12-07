/**
 * @file    day07.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    07 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day07.h"

#include "common.h"

std::string day07::process1(std::string file)
{
    auto map = parse::read_all(file);
    uint64_t count = 0;
    std::set<int> columns;
    for (int j = 0, m = map[0].size(); j < m; j++) {
        if (map[0][j] == 'S') {
            columns.insert(j);
            break;
        }
    }
    for (int i = 2, n = map.size(); i < n - 1; i = i + 2) {
        std::set<int> nextColumns;
        for (auto c : columns) {
            if (map[i][c] == '.') {
                nextColumns.insert(c);
            }
            if (map[i][c] == '^') {
                nextColumns.insert(c - 1);
                nextColumns.insert(c + 1);
                count++;
            }
        }
        columns.swap(nextColumns);
    }
    return std::to_string(count);
}

std::string day07::process2(std::string file)
{
    auto map = parse::read_all(file);
    // Column -> occurrences
    std::map<int, uint64_t> columns;
    for (int j = 0, m = map[0].size(); j < m; j++) {
        if (map[0][j] == 'S') {
            columns.insert({ j, 1 });
            break;
        }
    }
    for (int i = 2, n = map.size(); i < n - 1; i = i + 2) {
        std::map<int, uint64_t> nextColumns;
        for (auto [c, occurrence] : columns) {
            if (map[i][c] == '.') {
                op::increaseOrInsert<int, uint64_t>(&nextColumns, c, occurrence);
            }
            if (map[i][c] == '^') {
                op::increaseOrInsert<int, uint64_t>(&nextColumns, c - 1, occurrence);
                op::increaseOrInsert<int, uint64_t>(&nextColumns, c + 1, occurrence);
            }
        }
        columns.swap(nextColumns);
    }

    uint64_t sum = 0;
    for (auto col : columns) {
        sum += col.second;
    }
    return std::to_string(sum);
}
