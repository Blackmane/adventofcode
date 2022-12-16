/**
 * @file    day16.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    15 Dec 2022
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

#include <algorithm>
#include <cmath>

struct Valve {
    std::string name;
    uint64_t rate;
    std::vector<std::string> nexts;
};

typedef std::map<std::string, Valve> Map;

void insert(Map *map, std::string line)
{
    Valve valve;
    auto parts = parse::split(line, ';');
    valve.name = parts[0].substr(6, 2);
    auto end = parts[0].find(';');
    valve.rate = std::stoull(parts[0].substr(23, end - 23));
    std::string ways;
    if (parts[1][22] == 's') {
        ways = parts[1].substr(24, parts[1].size() - 24);
    } else {
        ways = parts[1].substr(23, parts[1].size() - 23);
    }
    auto nexts = parse::split(ways, ' ');
    for (auto &&next : nexts) {
        valve.nexts.push_back(next.substr(0, 2));
    }
    map->insert(std::make_pair(valve.name, valve));
}

struct ValveC {
    size_t name;
    uint64_t rate;
    std::vector<size_t> nexts;
};

typedef std::vector<ValveC> MapC;

MapC convertMap(Map &map)
{
    std::map<std::string, size_t> convert;
    std::string initial = "AA";
    convert.insert(std::make_pair(initial, 0));
    size_t i = 1;
    for (auto &&v : map) {
        if (v.first != initial) {
            convert.insert(std::make_pair(v.first, i));
            i++;
        }
    }
    MapC mapc;
    mapc.reserve(i);
    for (auto &&v : map) {
        ValveC valve;
        valve.name = convert[v.first];
        valve.rate = v.second.rate;
        for (auto &&next : v.second.nexts) {
            valve.nexts.push_back(convert[next]);
        }
        mapc.push_back(valve);
    }
    return mapc;
}

struct Explore {
    size_t entering;
    std::bitset<64> explored; // Affirm that number of valves is less than 64
    uint8_t time = 30;
    uint64_t pressure = 0;
};

size_t pos(size_t i, size_t j, size_t n)
{
    if (i < j) {
        return i * n + j;
    }
    return j * n + i;
}

uint64_t findSolution(MapC &map)
{
    auto n = map.size();
    std::vector<uint8_t> adjacencyMatrix(n * n, UINT8_MAX);

    // floyd-warshall
    for (auto &&v : map) {
        auto i = v.name;
        for (auto &&next : v.nexts) {
            auto j = next;
            adjacencyMatrix[pos(i, j, n)] = 1;
            adjacencyMatrix[pos(j, i, n)] = 1;
        }
    }
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                auto through_k = adjacencyMatrix[pos(i, k, n)] + adjacencyMatrix[pos(k, j, n)];
                if (through_k < adjacencyMatrix[pos(i, j, n)]) {
                    adjacencyMatrix[pos(i, j, n)] = through_k;
                    adjacencyMatrix[pos(j, i, n)] = through_k;
                }
            }
        }
    }
    // Remove from to same node
    for (size_t j = 0; j < n; ++j) {
        // adjacencyMatrix[pos(i, j, n)] = 0;
        adjacencyMatrix[pos(j, j, n)] = UINT8_MAX;
    }

    std::vector<size_t> costOrder;
    costOrder.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        if (map[i].rate > 0) {
            costOrder.push_back(i);
        }
    }
    std::sort(costOrder.begin(), costOrder.end(), [&map](size_t l, size_t r) { return map[l].rate > map[r].rate; });

    Explore eNext;
    eNext.entering = 0;
    eNext.time = 30;
    uint64_t maxPressure = 0;
    std::vector<Explore> queue;
    queue.reserve(n);
    queue.push_back(eNext);
    while (!queue.empty()) {
        auto cur = queue.back();
        queue.pop_back();
        uint8_t time = cur.time;
        cur.explored.set(cur.entering);

        auto curValve = map[cur.entering];
        if (curValve.rate > 0) {
            time -= 1;
            cur.pressure += time * curValve.rate;
            if (cur.pressure > maxPressure) {
                maxPressure = cur.pressure;
            }
        }

        if (time > 0) {
            for (auto idx : costOrder) {
                auto &valve = map[idx];
                if (valve.name != cur.entering) {
                    if (!cur.explored.test(valve.name)) {
                        auto cost = adjacencyMatrix[pos(cur.entering, valve.name, n)];
                        if (cost < UINT8_MAX && time > cost) {
                            eNext.entering = valve.name;
                            eNext.explored = cur.explored;
                            eNext.time = time - cost;
                            eNext.pressure = cur.pressure;
                            queue.push_back(eNext);
                        }
                    }
                }
            }
        }
    }

    return maxPressure;
}

uint64_t runSolution(MapC &map, std::vector<uint8_t> &adjacencyMatrix, size_t n, std::set<size_t> &valves)
{
    uint64_t maxPressure = 0;
    Explore eNext;
    eNext.entering = 0;
    eNext.time = 26;
    std::vector<Explore> queue;
    queue.reserve(n);
    queue.push_back(eNext);
    while (!queue.empty()) {
        auto cur = queue.back();
        queue.pop_back();
        uint8_t time = cur.time;
        cur.explored.set(cur.entering);

        auto curValve = map[cur.entering];
        if (curValve.rate > 0) {
            time -= 1;
            cur.pressure += time * curValve.rate;
            if (cur.pressure > maxPressure) {
                maxPressure = cur.pressure;
            }
        }
        if (time > 0) {
            for (auto idx : valves) {
                auto &valve = map[idx];
                if (valve.name != cur.entering) {
                    if (!cur.explored.test(valve.name)) {
                        auto cost = adjacencyMatrix[pos(cur.entering, valve.name, n)];
                        if (cost < UINT8_MAX && time > cost) {
                            eNext.entering = valve.name;
                            eNext.explored = cur.explored;
                            eNext.time = time - cost;
                            eNext.pressure = cur.pressure;
                            queue.push_back(eNext);
                        }
                    }
                }
            }
        }
    }
    return maxPressure;
}

uint64_t findSolution2(MapC &map)
{
    auto n = map.size();
    std::vector<uint8_t> adjacencyMatrix(n * n, UINT8_MAX);

    // floyd-warshall
    for (auto &&v : map) {
        auto i = v.name;
        for (auto &&next : v.nexts) {
            auto j = next;
            adjacencyMatrix[pos(i, j, n)] = 1;
        }
    }
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                auto through_k = adjacencyMatrix[pos(i, k, n)] + adjacencyMatrix[pos(k, j, n)];
                if (through_k < adjacencyMatrix[pos(i, j, n)]) {
                    adjacencyMatrix[pos(i, j, n)] = through_k;
                }
            }
        }
    }

    std::set<size_t> valveOfInterest;
    for (auto &&v : map) {
        if (v.rate > 0) {
            valveOfInterest.insert(v.name);
        }
    }

    uint64_t maxPressure = 0;
    for (int x = 0, nx = std::pow(2, valveOfInterest.size() - 1); x < nx; ++x) {
        std::set<size_t> splita;
        std::set<size_t> splitb;
        splita.insert(0);
        splitb.insert(0);
        int k = 0;
        for (auto c : valveOfInterest) {
            auto pos = 1 << k;
            if ((x & pos) != 0) {
                splita.insert(c);
            } else {
                splitb.insert(c);
            }
            k++;
        }
        auto pressure = runSolution(map, adjacencyMatrix, n, splita) + runSolution(map, adjacencyMatrix, n, splitb);
        if (pressure > maxPressure) {
            maxPressure = pressure;
        }
    }

    return maxPressure;
}

std::string day16::process1(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', insert, &map);
    auto mapc = convertMap(map);
    auto result = findSolution(mapc);
    return std::to_string(result);
}

std::string day16::process2(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', insert, &map);
    auto mapc = convertMap(map);
    auto result = findSolution2(mapc);
    return std::to_string(result);
}
