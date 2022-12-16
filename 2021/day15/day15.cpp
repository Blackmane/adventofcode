/**
 * @file    day15.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    15 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day15.h"

#include "common.h"

#include <queue>

typedef std::vector<std::vector<int>> Map;
typedef std::pair<size_t, size_t> Node;
typedef std::pair<uint64_t, Node> Visit;

void convertInput(Map *map, std::string line)
{
    std::vector<int> cur;
    for (auto c : line) {
        cur.push_back(c - '0');
    }
    map->push_back(cur);
}

uint64_t dijkstra(Map *map)
{
    size_t height = map->size();
    size_t width = map->at(0).size();
    Node start(0, 0);
    Node end(height - 1, width - 1);

    auto cmp = [](Visit left, Visit right) { return left.first > right.first; };
    std::priority_queue<Visit, std::deque<Visit>, decltype(cmp)> queue(cmp);
    queue.push(std::make_pair(0, start));

    std::vector<uint64_t> minDistance(height * width, -1);
    std::set<Node> visited;

    while (!queue.empty()) {
        auto cur = queue.top();
        auto distance = cur.first;
        auto node = cur.second;
        queue.pop();

        if (node == end) {
            return distance;
        }
        if (visited.find(node) != visited.end()) {
            continue;
        }
        visited.insert(node);

        for (auto &n : matrix::neighbours4(node.first, node.second, height, width)) {
            auto newDistance = distance + map->at(n.first)[n.second];
            if (newDistance < minDistance[n.first * width + n.second]) {
                minDistance[n.first * width + n.second] = newDistance;
                queue.push(std::make_pair(newDistance, n));
            }
        }
    }

    return 0;
}

void extend(Map *map)
{
    // Extends rows
    for (auto &row : *map) {
        auto width = row.size();
        for (int c = 0; c < 4; ++c) {
            for (size_t j = 0; j < width; ++j) {
                row.push_back((row[j] + c) % 9 + 1);
            }
        }
    }
    // Extends columns
    auto height = map->size();
    for (int c = 0; c < 4; ++c) {
        for (size_t i = 0; i < height; ++i) {
            std::vector<int> newRow;
            for (auto val : map->at(i)) {
                newRow.push_back((val + c) % 9 + 1);
            }
            map->push_back(newRow);
        }
    }
}

std::string day15::process1(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', convertInput, &map);
    auto res = dijkstra(&map);
    return std::to_string(res);
}

std::string day15::process2(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', convertInput, &map);
    extend(&map);
    auto res = dijkstra(&map);
    return std::to_string(res);
}
