/**
 * @file    day20.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    20 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day20.h"

#include "common.h"

#include <queue>
#include <unordered_set>

struct Node {
    int i = 0;
    int j = 0;
    int fromS = 0;
    int toE = 0;
    int hash()
    {
        return (i << 8) + (j);
    }
};

int bfs(const std::vector<std::string> &map, int n, int m, int i, int j, std::unordered_map<int, Node> &path)
{
    std::queue<Node> nexts;
    nexts.push({ i, j, 0 });

    std::unordered_set<int> visited;
    visited.reserve(n * m);

    auto addNext = [&](int cost, int pos_i, int pos_j) {
        if (pos_i >= 0 && pos_i < n && pos_j >= 0 && pos_j < m && map[pos_i][pos_j] != '#') {
            nexts.push({ pos_i, pos_j, cost });
        }
    };

    while (!nexts.empty()) {
        auto cur = nexts.front();
        nexts.pop();

        auto hash = cur.hash();
        if (visited.find(hash) != visited.end()) {
            continue;
        }
        visited.insert(hash);

        path.insert({ hash, { cur.i, cur.j, cur.fromS, 0 } });

        if (map[cur.i][cur.j] == 'E') {
            //  Found
            return cur.fromS;
        }

        addNext(cur.fromS + 1, cur.i - 1, cur.j);
        addNext(cur.fromS + 1, cur.i, cur.j + 1);
        addNext(cur.fromS + 1, cur.i + 1, cur.j);
        addNext(cur.fromS + 1, cur.i, cur.j - 1);
    }
    return 0;
}

uint64_t run(std::string &file, int distance)
{
    std::vector<std::pair<int, int>> manhattanNeighbours;
    for (int i = -distance; i <= distance; i++) {
        for (int j = -distance; j <= distance; j++) {
            if (std::abs(i) + std::abs(j) <= distance) {
                manhattanNeighbours.push_back({ i, j });
            }
        }
    }

    auto map = parse::read_all(file);
    const int n = map.size();
    const int m = map[0].size();

    auto [starti, startj] = [&]() -> std::pair<int, int> {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == 'S') {
                    return { i, j };
                }
            }
        }
        return { 0, 0 };
    }();

    std::unordered_map<int, Node> path;
    auto baseTime = bfs(map, n, m, starti, startj, path);
    for (auto &step : path) {
        step.second.toE = baseTime - step.second.fromS;
    }

    uint64_t count = 0;
    auto idxs = [](int idx) -> std::pair<int, int> { return { idx >> 8, idx & 255 }; };
    for (auto &step : path) {
        for (auto [i, j] : manhattanNeighbours) {
            auto manhattanDistance = std::abs(i) + std::abs(j);
            auto [ii, jj] = idxs(step.first);
            i += ii;
            j += jj;
            if (i >= 0 && i < n && j >= 0 && j < m && map[i][j] != '#') {
                auto c = path[(i << 8) + (j)];
                int newTime = step.second.fromS + manhattanDistance + c.toE;
                if (baseTime - newTime >= 100) {
                    count++;
                }
            }
        }
    }
    return count;
}

std::string day20::process1(std::string file)
{
    auto count = run(file, 2);
    return std::to_string(count);
}

std::string day20::process2(std::string file)
{
    auto count = run(file, 20);
    return std::to_string(count);
}