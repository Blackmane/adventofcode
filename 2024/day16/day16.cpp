/**
 * @file    day16.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    16 Dec 2024
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

#include <queue>
#include <unordered_set>

enum Dir { north = 0, east = 1, south = 2, west = 3 };

int rotCost(Dir from, Dir to)
{
    if (from == to) {
        return 1;
    }
    int diff = abs(from - to);
    if (diff == 3) {
        return 1000 + 1;
    }
    return diff * 1000 + 1;
}

struct Node {
    Node(int ii, int jj, Dir ddir, int ccost) : i(ii), j(jj), dir(ddir), cost(ccost) {}
    int i = 0;
    int j = 0;
    Dir dir = Dir::east;
    int cost = 0;
    int hash()
    {
        return (i << 10) + (j << 2) + dir;
    }
};

int minPath(const std::vector<std::string> &map)
{
    const int n = map.size();
    const int m = map[0].size();
    const int i = n - 2;
    const int j = 1;
    const int end_i = 1;
    const int end_j = m - 2;

    auto cmp = [](Node a, Node b) { return a.cost > b.cost; };
    std::priority_queue<Node, std::deque<Node>, decltype(cmp)> queue(cmp);
    queue.push({ i, j, Dir::east, 0 });

    std::unordered_set<int> visited;

    auto addDir = [&](int cost, int pos_i, int pos_j, Dir dir) {
        if (pos_i >= 0 && pos_i < n && pos_j >= 0 && pos_j < m && map[pos_i][pos_j] != '#') {
            queue.push({ pos_i, pos_j, dir, cost });
        }
    };

    while (!queue.empty()) {
        auto cur = queue.top();
        queue.pop();

        if (cur.i == end_i && cur.j == end_j) {
            // Found
            return cur.cost;
        }

        auto hash = cur.hash();
        if (visited.find(hash) != visited.end()) {
            continue;
        }
        visited.insert(hash);

        addDir(cur.cost + rotCost(cur.dir, Dir::north), cur.i - 1, cur.j, Dir::north);
        addDir(cur.cost + rotCost(cur.dir, Dir::east), cur.i, cur.j + 1, Dir::east);
        addDir(cur.cost + rotCost(cur.dir, Dir::south), cur.i + 1, cur.j, Dir::south);
        addDir(cur.cost + rotCost(cur.dir, Dir::west), cur.i, cur.j - 1, Dir::west);
    }
    return 0;
}

struct NodePath {
    NodePath(int ii, int jj, Dir d, int c, std::vector<int> p) : i(ii), j(jj), dir(d), cost(c), prec(std::move(p)) {}
    int i = 0;
    int j = 0;
    Dir dir = Dir::east;
    int cost = 0;
    std::vector<int> prec;
    int hash()
    {
        return (i << 10) + (j << 2) + dir;
    }
};

int countCells(const std::vector<std::string> &map)
{
    const int n = map.size();
    const int m = map[0].size();
    const int i = n - 2;
    const int j = 1;
    const int end_i = 1;
    const int end_j = m - 2;

    int limit = INT32_MAX;

    auto cmp = [](NodePath a, NodePath b) { return a.cost > b.cost; };
    std::priority_queue<NodePath, std::deque<NodePath>, decltype(cmp)> queue(cmp);
    queue.push({ i, j, Dir::east, 0, {} });

    std::unordered_map<int, int> visited;
    std::unordered_set<int> uniqueVisited;

    auto addDir = [&](int cost, int pos_i, int pos_j, Dir dir, std::vector<int> &prec) {
        if (cost < limit && pos_i >= 0 && pos_i < n && pos_j >= 0 && pos_j < m && map[pos_i][pos_j] != '#') {
            queue.push({ pos_i, pos_j, dir, cost, prec });
        }
    };

    while (!queue.empty()) {
        auto cur = queue.top();
        queue.pop();

        if (cur.i == end_i && cur.j == end_j) {
            // Found
            if (cur.cost <= limit) {
                limit = cur.cost;
                uniqueVisited.insert(cur.prec.begin(), cur.prec.end());
            }
        }

        auto hash = cur.hash();
        auto it = visited.find(hash);
        if (it != visited.end() && it->second < cur.cost) {
            continue;
        }
        visited.insert({ hash, cur.cost });

        cur.prec.push_back({ (cur.i << 8) + cur.j });
        addDir(cur.cost + rotCost(cur.dir, Dir::north), cur.i - 1, cur.j, Dir::north, cur.prec);
        addDir(cur.cost + rotCost(cur.dir, Dir::east), cur.i, cur.j + 1, Dir::east, cur.prec);
        addDir(cur.cost + rotCost(cur.dir, Dir::south), cur.i + 1, cur.j, Dir::south, cur.prec);
        addDir(cur.cost + rotCost(cur.dir, Dir::west), cur.i, cur.j - 1, Dir::west, cur.prec);
    }
    return uniqueVisited.size() + 1;
}

std::string day16::process1(std::string file)
{
    auto map = parse::read_all(file);
    auto count = minPath(map);
    return std::to_string(count);
}

std::string day16::process2(std::string file)
{
    auto map = parse::read_all(file);
    int count = countCells(map);
    return std::to_string(count);
}