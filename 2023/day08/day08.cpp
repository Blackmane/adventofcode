/**
 * @file    day08.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    08 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day08.h"

#include "common.h"

struct Node {
    std::string left;
    std::string right;
};

struct Map {
    std::string instructions;
    std::unordered_map<std::string, Node> nodes;
    std::vector<std::string> startNodes;
    Map(const std::string &file);
    int64_t followInstructions(const std::string &from, const std::string &to);
    int64_t followInstructionsMultipath();
};

Map::Map(const std::string &file)
{
    std::ifstream source;
    source.open(file);
    std::string part;

    bool firstLine = true;
    while (std::getline(source, part, '\n')) {
        if (firstLine) {
            instructions = part;
            firstLine = false;
        } else {
            if (part != "") {
                Node node;
                auto key = part.substr(0, 3);
                node.left = part.substr(7, 3);
                node.right = part.substr(12, 3);
                nodes.insert(std::make_pair(key, std::move(node)));
                if (key[2] == 'A') {
                    startNodes.push_back(key);
                }
            }
        }
    }
}

int64_t Map::followInstructions(const std::string &from, const std::string &to)
{
    Node current = nodes[from];
    bool found = false;
    int steps = 0;
    for (int i = 0, n = instructions.size(); !found; i = (i + 1) % n) {
        std::string next = instructions[i] == 'L' ? current.left : current.right;
        found = next == to;
        current = nodes[next];
        steps++;
    }
    return steps;
}

struct Repetition {
    int64_t from = 0;
    int64_t step = 0;
    bool isMultiple(int64_t val)
    {
        return ((val - from) % step) == 0;
    }
};

int64_t Map::followInstructionsMultipath()
{
    std::vector<uint64_t> repetitions(startNodes.size(), 0);
    auto currentNodes = startNodes;
    int steps = 0;
    bool found = false;
    for (int i = 0, n = instructions.size(); !found; i = (i + 1) % n) {
        steps++;
        std::vector<std::string> nextNodes;

        for (int j = 0, m = currentNodes.size(); j < m; j++) {
            if (repetitions[j] == 0) {
                auto currentKey = currentNodes[j];
                auto currentNode = nodes[currentKey];
                std::string next = instructions[i] == 'L' ? currentNode.left : currentNode.right;

                if (next[2] == 'Z') {
                    repetitions[j] = steps;
                }
                nextNodes.push_back(next);
            } else {
                nextNodes.push_back("");
            }
        }
        found = std::all_of(repetitions.begin(), repetitions.end(), [](uint64_t val) { return val != 0; });
        currentNodes = nextNodes;
    }
    return op::leastCommonMultiple(repetitions);
}

std::string day08::process1(std::string file)
{
    Map map(file);
    return std::to_string(map.followInstructions("AAA", "ZZZ"));
}

std::string day08::process2(std::string file)
{
    Map map(file);
    return std::to_string(map.followInstructionsMultipath());
}
