/**
 * @file    day17.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    17 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day17.h"

#include "common.h"

#include <queue>

enum Dir { north = 0, east = 1, south = 2, west = 3 };

struct Visit {
    int heat;
    int i;
    int j;
    Dir dir;
    int hash()
    {
        return (i << 10) + (j << 2) + dir;
    }
};

int minHeatPath(const std::vector<std::string> &map, bool part1 = true)
{
    const int n = map.size();
    const int m = map[0].size();
    auto isGood = [&](int x, int y) -> bool { return x >= 0 && x < (int)n && y >= 0 && y < (int)m; };

    auto cmp = [](Visit left, Visit right) { return left.heat > right.heat; };
    std::priority_queue<Visit, std::deque<Visit>, decltype(cmp)> queue(cmp);

    std::set<int> visited;

    int from_k = 1;
    int to_k = 3;
    if (!part1) {
        from_k = 4;
        to_k = 10;
    }

    auto addDir = [&](int heat, int pos_i, int pos_j, int dir_i, int dir_j, Dir dir) {
        int cost = heat;
        int k = 1;
        for (; k < from_k; k++) {
            pos_i += dir_i;
            pos_j += dir_j;
            if (!isGood(pos_i, pos_j)) {
                break;
            }
            cost += map[pos_i][pos_j] - '0';
        }
        for (; k <= to_k; k++) {
            pos_i += dir_i;
            pos_j += dir_j;
            if (!isGood(pos_i, pos_j)) {
                break;
            }
            cost += map[pos_i][pos_j] - '0';
            queue.push({ cost, pos_i, pos_j, dir });
        }
    };

    addDir(0, 0, 0, 1, 0, Dir::south);
    addDir(0, 0, 0, 0, 1, Dir::east);

    while (!queue.empty()) {
        auto cur = queue.top();
        queue.pop();

        if (cur.i == n - 1 && cur.j == m - 1) {
            // Found
            return cur.heat;
        }

        auto hash = cur.hash();
        if (visited.find(hash) != visited.end()) {
            continue;
        }
        visited.insert(hash);

        switch (cur.dir) {
            case Dir::north:
            case Dir::south:
                addDir(cur.heat, cur.i, cur.j, 0, 1, Dir::east);
                addDir(cur.heat, cur.i, cur.j, 0, -1, Dir::west);
                break;
            case Dir::east:
            case Dir::west:
                addDir(cur.heat, cur.i, cur.j, 1, 0, Dir::south);
                addDir(cur.heat, cur.i, cur.j, -1, 0, Dir::north);
                break;
        }
    }
    return 0;
}

std::string day17::process1(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    return std::to_string(minHeatPath(map));
}

std::string day17::process2(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    return std::to_string(minHeatPath(map, false));
}