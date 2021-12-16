/**
 * @file    day12.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2021
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

#include <deque>
#include <map>
#include <set>

typedef std::map<std::string, std::set<std::string>> Graph;

void convertInput(Graph *graph, std::string line)
{
    auto parts = parse::split(line, '-');
    auto it    = graph->find(parts[0]);
    if (it != graph->end()) {
        it->second.insert(parts[1]);
    } else {
        std::set<std::string> connections;
        connections.insert(parts[1]);
        graph->insert(std::make_pair(parts[0], connections));
    }

    it = graph->find(parts[1]);
    if (it != graph->end()) {
        it->second.insert(parts[0]);
    } else {
        std::set<std::string> connections;
        connections.insert(parts[0]);
        graph->insert(std::make_pair(parts[1], connections));
    }
}

uint64_t findSolution1(Graph *graph)
{
    std::deque<std::pair<std::string, std::set<std::string>>> nexts;
    std::set<std::string> emptySet;
    nexts.push_back(std::make_pair("start", emptySet));
    uint64_t count = 0;
    while (!nexts.empty()) {
        auto key     = nexts.front().first;
        auto visited = nexts.front().second;
        nexts.pop_front();

        if (key == "end") {
            count++;
        }

        auto connected = graph->at(key);

        bool curIsVisited = false;
        if (key[0] >= 'a') {
            curIsVisited = true;
        } else {
            // check all connection
            bool allVisited = true;
            for (auto node : connected) {
                if (visited.find(node) == visited.end()) {
                    allVisited = false;
                    break;
                }
            }
            if (allVisited) {
                curIsVisited = true;
            }
        }
        // Copy current
        std::set<std::string> nextVisited;
        for (auto v : visited) {
            nextVisited.insert(v);
        }
        if (curIsVisited) {
            nextVisited.insert(key);
        }

        // Add connections
        for (auto next : connected) {
            if (visited.find(next) != visited.end()) {
                continue;
            }
            nexts.push_front(std::make_pair(next, nextVisited));
        }
    }

    return count;
}

struct Visit {
    std::string cave;
    std::map<std::string, uint64_t> visited;
    bool multiCave = false;
};

uint64_t findSolution2(Graph *graph)
{
    std::deque<Visit> nexts;
    Visit first;
    first.cave = "start";
    nexts.push_back(first);
    uint64_t count = 0;
    while (!nexts.empty()) {
        // Extract current node
        auto cur       = nexts.front();
        auto key       = cur.cave;
        auto visited   = cur.visited;
        auto multiCave = cur.multiCave;
        nexts.pop_front();

        // Is the end of a path
        if (key == "end") {
            count++;
            continue;
        }

        auto it = visited.find(key);
        if (it == visited.end()) {
            // Not visited yet
            visited.insert(std::make_pair(key, 1));
        } else {
            // Is visited
            if (key[0] >= 'a') {
                if (it->second > 2 || multiCave) {
                    // Small cave already visited two time (this the third) or already use multi cave
                    continue;
                }
                // Set as multiple visit
                multiCave = true;
            }
            // Increment visit
            it->second++;
        }

        Visit nextToVisit;
        nextToVisit.multiCave = multiCave;
        for (auto v : visited) {
            nextToVisit.visited.insert(v);
        }
        // Add connections
        auto connected = graph->at(key);
        for (auto next : connected) {
            nextToVisit.cave = next;
            if (next == "start") {
                continue;
            }
            nexts.push_front(nextToVisit);
        }
    }

    return count;
}

std::string process1(std::string file)
{
    Graph graph;
    parse::read<Graph *>(file, '\n', convertInput, &graph);
    auto res = findSolution1(&graph);
    return std::to_string(res);
}

std::string process2(std::string file)
{
    Graph graph;
    parse::read<Graph *>(file, '\n', convertInput, &graph);
    auto res = findSolution2(&graph);
    return std::to_string(res);
}
