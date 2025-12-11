/**
 * @file    day11.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    11 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day11.h"

#include "common.h"

#include <queue>

// via topological Sort
uint64_t countPaths(std::set<std::string> &nodes, std::map<std::string, std::vector<std::string>> &connections,
                    const std::string &source, const std::string &destination)
{
    std::map<std::string, int> indegree;
    std::map<std::string, uint64_t> ways;
    for (auto &node : nodes) {
        indegree[node] = 0;
        ways[node] = 0;
    }

    for (auto &con : connections) {
        for (auto &output : con.second) {
            indegree[output]++;
        }
    }

    // Topological sort using Kahn's algorithm
    std::queue<std::string> queue;
    for (auto &[key, value] : indegree) {
        if (value == 0) {
            queue.push(key);
        }
    }

    std::vector<std::string> topoOrder;
    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();
        topoOrder.push_back(node);

        for (auto &neighbor : connections[node]) {
            auto value = --indegree[neighbor];
            if (value == 0) {
                queue.push(neighbor);
            }
        }
    }

    ways[source] = 1;
    for (auto &node : topoOrder) {
        for (auto &neighbor : connections[node]) {
            ways[neighbor] += ways[node];
        }
    }

    return ways[destination];
}

std::string day11::process1(std::string file)
{
    std::string start{ "you" };
    std::string end{ "out" };
    std::map<std::string, std::vector<std::string>> connections;
    std::set<std::string> nodes;
    parse::read(file, '\n', [&](const std::string &line) {
        auto parts = parse::split(line, ':');
        auto cons = parse::split(parts[1], ' ');
        cons.erase(cons.begin());
        connections.insert({ parts[0], cons });
        nodes.insert(parts[0]);
        for (auto &&c : cons) {
            nodes.insert(c);
        }
    });

    auto count = countPaths(nodes, connections, start, end);
    return std::to_string(count);
}

std::string day11::process2(std::string file)
{
    std::string start{ "svr" };
    std::string end{ "out" };
    std::map<std::string, std::vector<std::string>> connections;
    std::set<std::string> nodes;
    parse::read(file, '\n', [&](const std::string &line) {
        auto parts = parse::split(line, ':');
        auto cons = parse::split(parts[1], ' ');
        cons.erase(cons.begin());
        connections.insert({ parts[0], cons });
        nodes.insert(parts[0]);
        for (auto &&c : cons) {
            nodes.insert(c);
        }
    });

    auto consNoFFT = connections;
    consNoFFT.erase("fft");
    auto consNoDAC = connections;
    consNoDAC.erase("dac");

    auto p1_s = countPaths(nodes, consNoFFT, start, "dac");
    auto p1_c = countPaths(nodes, connections, "dac", "fft");
    auto p1_e = countPaths(nodes, consNoDAC, "fft", end);

    auto p2_s = countPaths(nodes, consNoDAC, start, "fft");
    auto p2_c = countPaths(nodes, connections, "fft", "dac");
    auto p2_e = countPaths(nodes, consNoFFT, "dac", end);

    uint64_t count = p1_s * p1_c * p1_e + p2_s * p2_c * p2_e;

    return std::to_string(count);
}
