/**
 * @file    day23.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    23 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day23.h"

#include "common.h"

#include <unordered_set>

std::string day23::process1(std::string file)
{
    std::unordered_map<std::string, std::unordered_set<std::string>> nodes;
    parse::read(file, '\n', [&](const std::string &line) {
        auto parts = parse::split(line, '-');
        nodes[parts[0]].insert(parts[1]);
        nodes[parts[1]].insert(parts[0]);
    });

    std::set<std::string> founds;
    for (auto &[it, list] : nodes) {
        if (it[0] != 't') {
            continue;
        }
        for (auto i = list.begin(), ni = list.end(); i != ni; i++) {
            auto j = i;
            j++;
            for (; j != ni; j++) {
                // For each two nodes connected to `it`
                // Check if they are connected to each other
                if (nodes[*i].count(*j) > 0) {
                    std::vector<std::string> l = { it, *i, *j };
                    std::sort(l.begin(), l.end());
                    founds.insert(l[0] + l[1] + l[2]);
                }
            }
        }
    }

    return std::to_string(founds.size());
}

std::string day23::process2(std::string file)
{
    std::unordered_map<std::string, std::set<std::string>> nodes;
    parse::read(file, '\n', [&](const std::string &line) {
        auto parts = parse::split(line, '-');
        if (parts[0] < parts[1]) {
            nodes[parts[0]].insert(parts[1]);
        } else {
            nodes[parts[1]].insert(parts[0]);
        }
    });

    std::set<std::string> largest;
    for (auto &[node, list] : nodes) {
        // A clique must be contained in the nodes of a node
        if (list.size() < largest.size()) {
            continue;
        }

        // Check for the subset
        std::set<std::string> connected = list;
        for (auto i = list.begin(), ni = list.end(); i != ni; i++) {
            if (connected.count(*i) == 0) {
                continue;
            }
            auto j = i;
            j++;
            for (; j != ni; j++) {
                if (nodes[*i].count(*j) == 0) {
                    connected.erase(*j);
                }
            }
        }

        connected.insert(node);
        if (connected.size() > largest.size()) {
            std::swap(largest, connected);
        }
    }

    std::string password;
    for (auto &node : largest) {
        password += node + ',';
    }
    password.pop_back();
    return password;
}