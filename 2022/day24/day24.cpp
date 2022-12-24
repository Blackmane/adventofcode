/**
 * @file    day24.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    24 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day24.h"

#include "common.h"

#include <queue>

typedef std::vector<std::vector<char>> Map;
size_t SIDE = 0;

void insert(Map *map, const std::string &line)
{
    if (line[2] == '#') {
        // First or last, skip
        return;
    } else {
        // Center
        SIDE = line.size();
        for (size_t i = 1; i < SIDE - 1; ++i) {
            std::vector<char> cur;
            cur.push_back(line[i]);
            map->push_back(std::move(cur));
        }
    }
}

Map moveMap(const Map &map)
{
    auto mapSize = map.size();
    std::vector<char> empty;
    Map result(mapSize, empty);

    size_t i = 0;
    for (auto &&cell : map) {
        for (auto c : cell) {
            size_t j = 0;
            switch (c) {
                case '<':
                    j = i - 1;
                    if (i % SIDE == 0) {
                        j += SIDE;
                    }
                    result[j].push_back(c);
                    break;
                case '>':
                    j = i + 1;
                    if (i % SIDE == SIDE - 1) {
                        j -= SIDE;
                    }
                    result[j].push_back(c);
                    break;
                case 'v':
                    j = i + SIDE;
                    if (j >= mapSize) {
                        j = i % SIDE;
                    }
                    result[j].push_back(c);
                    break;
                case '^':
                    j = i - SIDE;
                    if (i < SIDE) {
                        j = mapSize - SIDE + i;
                    }
                    result[j].push_back(c);
                    break;
            }
            // Skip '.' and '#'
        }
        i++;
    }
    return result;
}

uint64_t getPath(Map &map, bool backward = false)
{
    auto mapSize = map.size();

    size_t start = 0;
    size_t end = map.size() - 1;
    if (backward) {
        std::swap(start, end);
    }

    auto curMap = moveMap(map);
    std::set<size_t> possibilePositions;
    possibilePositions.insert(start);
    bool found = false;
    int time = 1;
    while (!found) {
        std::set<size_t> nextPosition;
        for (auto posIdx : possibilePositions) {
            size_t pos = posIdx;
            if (pos == end) {
                // Part 2 setup
                map = std::move(curMap);
                return time;
            }
            for (auto &near : matrix::neighbours4(pos, SIDE, mapSize)) {
                if (curMap[near].size() == 0) {
                    nextPosition.insert(near);
                }
            }
            // Wait
            if (curMap[pos].size() == 0) {
                nextPosition.insert(pos);
            }
        }
        if (curMap[start].size() == 0) {
            nextPosition.insert(start);
        }
        possibilePositions = nextPosition;
        curMap = moveMap(curMap);
        time++;
    }
    return 0;
}

std::string day24::process1(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', &insert, &map);
    SIDE -= 2; // Don't count first and last '#'
    auto result = getPath(map);
    return std::to_string(result);
}

std::string day24::process2(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', &insert, &map);
    SIDE -= 2; // Don't count first and last '#'
    auto result = getPath(map);
    result += getPath(map, true);
    result += getPath(map);
    return std::to_string(result);
}