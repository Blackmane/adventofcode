/**
 * @file    day12.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day12.h"

#include "common.h"

uint64_t group(std::vector<std::string> &map, int i, int j)
{
    uint64_t perimeter = 0;
    uint64_t count = 0;
    int n = map.size();
    int m = map[0].size();
    char groupName = map[i][j];

    std::set<std::pair<int, int>> visited;
    std::vector<std::pair<int, int>> cells;
    cells.push_back({ i, j });
    visited.insert({ i, j });
    while (!cells.empty()) {
        auto cell = cells.back();
        cells.pop_back();
        auto neighbours = matrix::neighbours4(cell.first, cell.second, n, m);
        count++;
        perimeter += 4;
        for (auto neighbour : neighbours) {
            if (map[neighbour.first][neighbour.second] == groupName) {
                perimeter -= 1;
                if (visited.count(neighbour) == 0) {
                    cells.push_back(neighbour);
                    visited.insert(neighbour);
                }
            }
        }
    }
    for (auto cell : visited) {
        map[cell.first][cell.second] = '.';
    }
    return perimeter * count;
}

void increment(std::map<std::pair<int, int>, int> &map, std::pair<int, int> key)
{
    auto it = map.find(key);
    if (it == map.end()) {
        map.insert({ key, 1 });
    } else {
        it->second++;
    }
}

uint64_t groupBulk(std::vector<std::string> &map, int i, int j)
{
    uint64_t count = 0;
    int n = map.size();
    int m = map[0].size();
    char groupName = map[i][j];

    // TL of a cell
    std::map<std::pair<int, int>, int> corners;
    std::set<std::pair<int, int>> visited;
    std::vector<std::pair<int, int>> cells;
    cells.push_back({ i, j });
    visited.insert({ i, j });
    while (!cells.empty()) {
        auto cell = cells.back();
        cells.pop_back();

        increment(corners, { cell.first, cell.second });
        increment(corners, { cell.first + 1, cell.second });
        increment(corners, { cell.first, cell.second + 1 });
        increment(corners, { cell.first + 1, cell.second + 1 });

        auto neighbours = matrix::neighbours4(cell.first, cell.second, n, m);
        count++;
        for (auto neighbour : neighbours) {
            if (map[neighbour.first][neighbour.second] == groupName) {
                if (visited.count(neighbour) == 0) {
                    cells.push_back(neighbour);
                    visited.insert(neighbour);
                }
            }
        }
    }

    uint64_t fences = 0;
    for (auto cornerCount : corners) {
        if (cornerCount.second % 2 == 1) {
            fences++;
        } else {
            auto c = cornerCount.first;
            if (c.first >= 1 && c.second >= 1 && c.first < n && c.second < m) {
                // Check for a corner connected diagonally to two parts of the group
                bool tl = map[c.first - 1][c.second - 1] == groupName;
                bool br = map[c.first][c.second] == groupName;
                bool bl = map[c.first - 1][c.second] == groupName;
                bool tr = map[c.first][c.second - 1] == groupName;
                if (tl == br && bl == tr && tl != tr) {
                    fences += 2;
                }
            }
        }
    }

    for (auto cell : visited) {
        map[cell.first][cell.second] = '.';
    }

    return fences * count;
}

std::string run(std::string &file, std::function<uint64_t(std::vector<std::string> &map, int i, int j)> grouping)
{
    auto map = parse::read_all(file);
    int n = map.size();
    int m = map[0].size();

    uint64_t count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == '.') {
                continue;
            }
            count += grouping(map, i, j);
        }
    }

    return std::to_string(count);
}

std::string day12::process1(std::string file)
{
    return run(file, group);
}

std::string day12::process2(std::string file)
{
    return run(file, groupBulk);
}