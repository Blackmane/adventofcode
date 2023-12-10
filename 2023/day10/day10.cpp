/**
 * @file    day10.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    10 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day10.h"

#include "common.h"

#include <queue>

struct Node {
    uint64_t step;
    size_t posX;
    size_t posY;
};

Node getS(std::vector<std::string> &map)
{
    for (size_t i = 0, n = map.size(); i < n; i++) {
        for (size_t j = 0, m = map[i].size(); j < m; j++) {
            if (map[i][j] == 'S') {
                return Node{ 0, i, j };
            }
        }
    }
    return Node{ 0, 0, 0 };
}

char convertS(size_t x, size_t y, std::vector<std::string> &map)
{
    bool up = x > 0 && std::string("F7|").find(map[x - 1][y], 0) != std::string::npos;
    bool down = x < map.size() - 1 && std::string("LJ|").find(map[x + 1][y], 0) != std::string::npos;
    bool left = y > 0 && std::string("LF-").find(map[x][y - 1], 0) != std::string::npos;
    bool right = y < map[0].size() - 1 && std::string("J7-").find(map[x][y + 1], 0) != std::string::npos;

    size_t pos = 0;
    pos += up ? 1 : 0;
    pos += down ? 2 : 0;
    pos += left ? 4 : 0;
    pos += right ? 8 : 0;

    return "...|.J7..LF.-"[pos];
}

std::map<std::pair<size_t, size_t>, uint64_t> getLoop(std::vector<std::string> &map)
{
    auto sNode = getS(map);
    map[sNode.posX][sNode.posY] = convertS(sNode.posX, sNode.posY, map);

    std::queue<Node> list;
    list.push(std::move(sNode));

    const size_t n = map.size();
    const size_t m = map[0].size();
    std::map<std::pair<size_t, size_t>, uint64_t> loopNodes;
    while (!list.empty()) {
        auto curr = list.front();
        list.pop();

        if (loopNodes.find(std::make_pair(curr.posX, curr.posY)) != loopNodes.end()) {
            continue;
        }
        loopNodes.insert(std::make_pair(std::make_pair(curr.posX, curr.posY), curr.step));

        char c = map[curr.posX][curr.posY];
        if (curr.posX > 0 && (c == '|' || c == 'L' || c == 'J'))
            list.push(Node{ curr.step + 1, curr.posX - 1, curr.posY });
        if (curr.posX < n - 1 && (c == '|' || c == '7' || c == 'F'))
            list.push(Node{ curr.step + 1, curr.posX + 1, curr.posY });
        if (curr.posY > 0 && (c == '-' || c == 'J' || c == '7'))
            list.push(Node{ curr.step + 1, curr.posX, curr.posY - 1 });
        if (curr.posY < m - 1 && (c == '-' || c == 'L' || c == 'F'))
            list.push(Node{ curr.step + 1, curr.posX, curr.posY + 1 });
    }
    return loopNodes;
}

uint64_t distance(std::vector<std::string> &map)
{
    auto loopNodes = getLoop(map);

    uint64_t maxDistance = 0;
    for (auto &&visit : loopNodes) {
        if (visit.second > maxDistance) {
            maxDistance = visit.second;
        }
    }
    return maxDistance;
}

uint64_t internalOddEven(std::vector<std::string> &map)
{
    auto loopNodes = getLoop(map);

    for (size_t i = 0, n = map.size(); i < n; ++i) {
        bool up = false;
        bool down = false;
        for (size_t j = 0, m = map[0].size(); j < m; ++j) {
            char symbol = map[i][j];
            auto isBorder = loopNodes.find(std::make_pair(i, j)) != loopNodes.end();
            if (isBorder) {
                if (symbol == '|' || symbol == 'L' || symbol == 'J')
                    up = !up;
                if (symbol == '|' || symbol == 'F' || symbol == '7')
                    down = !down;
            } else {
                map[i][j] = up && down ? 'I' : 'O';
            }
        }
    }

    uint64_t count = 0;
    for (auto &&line : map) {
        count += std::count_if(line.begin(), line.end(), [](char c) { return c == 'I'; });
    }
    return count;
}

uint64_t internalFloodFill(std::vector<std::string> &map)
{
    auto loopNodes = getLoop(map);

    std::vector<std::string> enlargedMap;
    for (auto &&line : map) {
        std::string top;
        std::string bottom;
        for (auto &&c : line) {
            //    |.  7.  F-  --  L-  J.  ..
            //    |.  |.  |.  ..  ..  ..  ..
            top.push_back(c);
            top.push_back((c == '-' || c == 'L' || c == 'F') ? '-' : '.');
            bottom.push_back((c == '|' || c == '7' || c == 'F') ? '|' : '.');
            bottom.push_back('.');
        }
        enlargedMap.push_back(top);
        enlargedMap.push_back(bottom);
    }

    for (auto &&visit : loopNodes) {
        auto x = visit.first.first * 2;
        auto y = visit.first.second * 2;
        enlargedMap[x][y] = '*';
        enlargedMap[x + 1][y] = enlargedMap[x + 1][y] == '.' ? '.' : '*';
        enlargedMap[x][y + 1] = enlargedMap[x][y + 1] == '.' ? '.' : '*';
        enlargedMap[x + 1][y + 1] = enlargedMap[x + 1][y + 1] == '.' ? '.' : '*';
    }

    const size_t n = map.size();
    const size_t m = map[0].size();
    std::queue<std::pair<size_t, size_t>> flood;
    // Start from the borders of the map
    for (size_t i = 0; i < (n * 2); i++) {
        flood.push(std::make_pair(i, 0));
        flood.push(std::make_pair(i, (m * 2) - 1));
    }
    for (size_t j = 0; j < (m * 2); j++) {
        flood.push(std::make_pair(0, j));
        flood.push(std::make_pair((n * 2) - 1, j));
    }
    while (!flood.empty()) {
        auto curr = flood.front();
        flood.pop();
        if (enlargedMap[curr.first][curr.second] == '*' || enlargedMap[curr.first][curr.second] == 'O') {
            // Already visited or loop node
            continue;
        }
        enlargedMap[curr.first][curr.second] = 'O';
        auto neighbours = matrix::neighbours4(curr.first, curr.second, 2 * n, 2 * m);
        for (auto &neighbour : neighbours) {
            flood.push(neighbour);
        }
    }

    uint64_t count = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            char c = enlargedMap[i * 2][j * 2];
            if (!(c == 'O' || c == '*')) {
                count++;
            }
        }
    }
    return count;
}

std::string day10::process1(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    return std::to_string(distance(map));
}

std::string day10::process2(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    return std::to_string(internalOddEven(map));
    // return std::to_string(internalFloodFill(map));
}