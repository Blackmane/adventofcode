/**
 * @file    day24.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    24 Dec 2024
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

#include <algorithm>

struct Wire {
    std::string from1;
    std::string from2;
    std::string op;
    std::string to;
};

void parseData(std::string &file, std::vector<Wire> &wires, std::unordered_map<std::string, int> &state)
{
    bool readWires = false;
    parse::read(file, '\n', [&](const std::string &line) {
        if (line.empty()) {
            readWires = true;
            return;
        }

        if (!readWires) {
            auto parts = parse::split(line, ':');
            state[parts[0]] = std::stoi(parts[1].substr(1, parts[1].size() - 1));
        } else {
            auto parts = parse::split(line, ' ');
            wires.push_back({ parts[0], parts[2], parts[1], parts[4] });
        }
    });
}

void connect(std::vector<Wire> wires, std::unordered_map<std::string, int> &state)
{
    while (!wires.empty()) {
        int n = wires.size();
        for (int i = 0; i < n; i++) {
            if (state.count(wires[i].from1) > 0 && state.count(wires[i].from2) > 0) {
                int res = 0;
                int from1 = state[wires[i].from1];
                int from2 = state[wires[i].from2];
                if (wires[i].op == "OR") {
                    res = from1 | from2;
                } else if (wires[i].op == "AND") {
                    res = from1 & from2;
                } else if (wires[i].op == "XOR") {
                    res = from1 ^ from2;
                }
                state[wires[i].to] = res;
                std::swap(wires[i], wires[n - 1]);
                n--;
            }
        }
        wires.erase(wires.begin() + n, wires.end());
    }
}

std::string day24::process1(std::string file)
{
    std::unordered_map<std::string, int> state;
    std::vector<Wire> wires;
    parseData(file, wires, state);

    connect(wires, state);

    uint64_t res = 0;
    for (auto &[name, val] : state) {
        if (val == 1 && name[0] == 'z') {
            uint64_t pos = std::stoi(name.substr(1, name.size() - 1));
            res |= uint64_t(1) << pos;
        }
    }

    return std::to_string(res);
}

std::string day24::process2(std::string file)
{
    // Sorry, by hand, again
    return "";
}