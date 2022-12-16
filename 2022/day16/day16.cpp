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

#include <cmath>
#include <queue>

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

struct Explore {
    std::string entering;
    std::set<size_t> explored;
    uint64_t time = 30;
    uint64_t pressure = 0;
};

size_t pos(size_t i, size_t j, size_t n)
{
    return i * n + j;
}

uint64_t findSolution(Map &map)
{
    auto n = map.size();
    std::vector<uint64_t> adjacencyMatrix(n * n, UINT64_MAX);
    size_t c = 0;
    std::map<std::string, size_t> convert;
    for (auto &&v : map) {
        convert.insert(std::make_pair(v.first, c));
        c++;
    }

    // floyd-warshall
    for (auto &&v : map) {
        auto i = convert[v.first];
        for (auto &&next : v.second.nexts) {
            auto j = convert[next];
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
    Explore e;
    e.entering = "AA";
    e.time = 30;
    uint64_t maxPressure = 0;
    std::queue<Explore> queue;
    queue.emplace(e);
    while (!queue.empty()) {
        auto cur = queue.front();
        queue.pop();
        uint64_t time = cur.time; //    -1;
        cur.explored.insert(convert[cur.entering]);

        auto curValve = map.find(cur.entering)->second;
        if (curValve.rate > 0) {
            time -= 1;
            cur.pressure += time * curValve.rate;
            if (cur.pressure > maxPressure) {
                maxPressure = cur.pressure;
            }
        }
        if (time > 0) {
            for (auto &&valve : convert) {
                if (valve.first != cur.entering) {
                    if (map[valve.first].rate > 0) {
                        if (cur.explored.find(convert[valve.first]) == cur.explored.end()) {
                            auto cost = adjacencyMatrix[pos(convert[cur.entering], convert[valve.first], n)];
                            if (time > cost && cost < UINT16_MAX) {
                                Explore eNext;
                                eNext.entering = valve.first;
                                eNext.explored = cur.explored;
                                eNext.time = time - cost;
                                eNext.pressure = cur.pressure;
                                queue.emplace(eNext);
                            }
                        }
                    }
                }
            }
        }
    }

    return maxPressure;
}

uint64_t runSolution(Map &map, std::vector<uint64_t> &adjacencyMatrix, size_t n, std::map<std::string, size_t> &convert)
{
    uint64_t maxPressure = 0;
    Explore e;
    e.entering = "AA";
    e.time = 26;
    std::queue<Explore> queue;
    queue.emplace(e);
    while (!queue.empty()) {
        auto cur = queue.front();
        queue.pop();
        uint64_t time = cur.time;
        cur.explored.insert(convert[cur.entering]);

        auto curValve = map.find(cur.entering)->second;
        if (curValve.rate > 0) {
            time -= 1;
            cur.pressure += time * curValve.rate;
            if (cur.pressure > maxPressure) {
                maxPressure = cur.pressure;
            }
        }
        if (time > 0) {
            for (auto &&valve : convert) {
                if (valve.first != cur.entering) {
                    if (map[valve.first].rate > 0) {
                        if (cur.explored.find(convert[valve.first]) == cur.explored.end()) {
                            auto cost = adjacencyMatrix[pos(convert[cur.entering], convert[valve.first], n)];
                            if (time > cost) {
                                Explore eNext;
                                eNext.entering = valve.first;
                                eNext.explored = cur.explored;
                                eNext.time = time - cost;
                                eNext.pressure = cur.pressure;
                                queue.emplace(eNext);
                            }
                        }
                    }
                }
            }
        }
    }
    return maxPressure;
}

uint64_t findSolution2(Map &map)
{
    auto n = map.size();
    std::vector<uint64_t> adjacencyMatrix(n * n, UINT64_MAX);
    size_t kc = 0;
    std::map<std::string, size_t> convert;
    for (auto &&v : map) {
        convert.insert(std::make_pair(v.first, kc));
        kc++;
    }

    // floyd-warshall
    for (auto &&v : map) {
        auto i = convert[v.first];
        for (auto &&next : v.second.nexts) {
            auto j = convert[next];
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

    std::set<size_t> valveOfInterest;
    for (auto &&v : map) {
        if (v.second.rate > 0) {
            valveOfInterest.insert(convert[v.first]);
        }
    }

    uint64_t maxPressure = 0;
    for (int x = 0, nx = std::pow(2, valveOfInterest.size() - 1); x < nx; ++x) {
        std::map<std::string, size_t> splita;
        std::map<std::string, size_t> splitb;
        auto aa = std::make_pair("AA", convert["AA"]);
        splita.insert(aa);
        splitb.insert(aa);
        int k = 0;
        for (auto c : convert) {
            if (valveOfInterest.find(c.second) != valveOfInterest.end()) {
                auto pos = 1 << k;
                if ((x & pos) != 0) {
                    splita.insert(c);
                } else {
                    splitb.insert(c);
                }
                k++;
            }
        }
        auto pressure = runSolution(map, adjacencyMatrix, n, splita) + runSolution(map, adjacencyMatrix, n, splitb);
        if (pressure > maxPressure) {
            maxPressure = pressure;
            std::cout << maxPressure << std::endl;
        }
    }

    return maxPressure;
}
std::string day16::process1(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', insert, &map);
    auto result = findSolution(map);
    return std::to_string(result);
}

std::string day16::process2(std::string file)
{
    Map map;
    parse::read<Map *>(file, '\n', insert, &map);
    auto result = findSolution2(map);
    return std::to_string(result);
}
