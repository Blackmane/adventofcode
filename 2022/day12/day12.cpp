/**
 * @file    day12.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2022
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

#include <queue>

typedef std::pair<size_t, size_t> Node;
typedef std::pair<uint64_t, Node> Visit;

uint64_t dijkstra(std::vector<std::string> *map, bool startFromA = false)
{
    size_t height = map->size();
    size_t width = map->at(0).size();

    auto cmp = [](Visit left, Visit right) { return left.first > right.first; };
    std::priority_queue<Visit, std::deque<Visit>, decltype(cmp)> queue(cmp);

    Node end(0, 0);
    for (int i = 0, n = height; i < n; ++i) {
        for (int j = 0, m = width; j < m; ++j) {
            if (map->at(i)[j] == 'S' || (startFromA && map->at(i)[j] == 'a')) {
                map->at(i)[j] = 'a';
                queue.push(std::make_pair(0, Node(i, j)));
            }
            if (map->at(i)[j] == 'E') {
                end.first = i;
                end.second = j;
                map->at(i)[j] = 'z';
            }
        }
    }

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
            char from = map->at(node.first)[node.second];
            char to = map->at(n.first)[n.second];
            if (to - from <= 1) {
                auto newDistance = distance + 1;
                if (newDistance < minDistance[n.first * width + n.second]) {
                    minDistance[n.first * width + n.second] = newDistance;
                    queue.push(std::make_pair(newDistance, n));
                }
            }
        }
    }

    return 0;
}

std::string process1(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    auto result = dijkstra(&map);
    return std::to_string(result);
}

std::string process2(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    auto result = dijkstra(&map, true);
    return std::to_string(result);
}
