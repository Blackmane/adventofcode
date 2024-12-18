/**
 * @file    day18.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    18 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day18.h"

#include "common.h"

#include <queue>
#include <unordered_set>

typedef std::set<std::pair<int, int>> Memory;

struct Node {
    Node(int ii, int jj, int ccost) : i(ii), j(jj), cost(ccost) {}
    int i = 0;
    int j = 0;
    int cost = 0;
    int hash()
    {
        return (i << 8) + (j);
    }
};

int minPathMap(const std::vector<std::vector<bool>> &memory, int n, int m)
{
    const int i = 0;
    const int j = 0;
    const int end_i = n - 1;
    const int end_j = m - 1;

    auto cmp = [](Node a, Node b) { return a.cost > b.cost; };
    std::priority_queue<Node, std::deque<Node>, decltype(cmp)> queue(cmp);
    queue.push({ i, j, 0 });

    std::unordered_set<int> visited;
    visited.reserve(n * m);

    auto addByte = [&](int cost, int pos_i, int pos_j) {
        if (pos_i >= 0 && pos_i < n && pos_j >= 0 && pos_j < m && !memory[pos_i][pos_j]) {
            queue.push({ pos_i, pos_j, cost });
        }
    };

    while (!queue.empty()) {
        auto cur = queue.top();
        queue.pop();

        if (cur.i == end_i && cur.j == end_j) {
            //  Found
            return cur.cost;
        }

        auto hash = cur.hash();
        if (visited.find(hash) != visited.end()) {
            continue;
        }
        visited.insert(hash);

        addByte(cur.cost + 1, cur.i - 1, cur.j);
        addByte(cur.cost + 1, cur.i, cur.j + 1);
        addByte(cur.cost + 1, cur.i + 1, cur.j);
        addByte(cur.cost + 1, cur.i, cur.j - 1);
    }
    return 0;
}

std::string day18::process1(std::string file)
{
    std::vector<bool> emptyLine(71, false);
    std::vector<std::vector<bool>> memoryMap(71, emptyLine);

    int count = 0;
    std::string found;
    parse::read<int &>(
        file, '\n',
        [&](int &i, const std::string &line) {
            if (i < 1024) {
                auto parts = parse::split(line, ',');
                int x = stoi(parts[0]);
                int y = stoi(parts[1]);
                if (i < 1024) {
                    memoryMap[x][y] = true;
                }
            }
            i++;
        },
        count);

    return std::to_string(minPathMap(memoryMap, 71, 71));
}

std::string day18::process2(std::string file)
{
    std::vector<bool> emptyLine(71, false);
    std::vector<std::vector<bool>> memoryMapFrom(71, emptyLine);

    std::vector<std::pair<int, int>> bytes;

    int count = 0;
    std::string found;
    parse::read<int &>(
        file, '\n',
        [&](int &i, const std::string &line) {
            auto parts = parse::split(line, ',');
            int x = stoi(parts[0]);
            int y = stoi(parts[1]);
            bytes.push_back({ x, y });
            if (i < 1024) {
                memoryMapFrom[x][y] = true;
            }
            i++;
        },
        count);

    // Binary search
    int from = 1024 - 1;
    int to = bytes.size() - 1;
    while (from + 1 != to) {
        int mid = (from + to) / 2;

        auto memoryMap = memoryMapFrom;
        for (int i = from; i <= mid; i++) {
            auto [x, y] = bytes[i];
            memoryMap[x][y] = true;
        }
        auto result = minPathMap(memoryMap, 71, 71);
        if (result == 0) {
            to = mid;
        } else {
            from = mid;
            memoryMapFrom = memoryMap;
        }
    }

    auto [x, y] = bytes[to];
    auto res = "" + std::to_string(x) + "," + std::to_string(y);
    return res;
}