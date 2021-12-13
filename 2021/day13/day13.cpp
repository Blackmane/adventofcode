/**
 * @file    day13.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    13 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day13.h"

#include "common.h"

#include <set>

struct Input {
    std::set<std::pair<uint64_t, uint64_t>> dots;
    std::vector<std::pair<uint64_t, uint64_t>> instructions;
    bool changed = false;
};

void convertInput(Input *input, std::string line)
{
    if (line.empty()) {
        input->changed = true;
        return;
    }
    if (!input->changed) {
        auto values = parse::split(line, ',');
        input->dots.insert(std::make_pair(std::stoull(values[0]), std::stoull(values[1])));
    } else {
        auto parts = parse::split(line, '=');
        if (parts[0][11] == 'y') {
            input->instructions.push_back(std::make_pair(0, std::stoull(parts[1])));
        } else {
            input->instructions.push_back(std::make_pair(std::stoull(parts[1]), 0));
        }
    }
}

uint64_t findSolution1(Input *input)
{
    for (auto instr : input->instructions) {
        std::set<std::pair<uint64_t, uint64_t>> toChange;
        std::set<std::pair<uint64_t, uint64_t>> toDelete;
        if (instr.first > 0) {
            for (auto dot : input->dots) {
                if (dot.first > instr.first) {
                    toChange.insert(dot);
                } else if (dot.first == instr.first) {
                    toDelete.insert(dot);
                }
            }
        } else {
            for (auto dot : input->dots) {
                if (dot.second > instr.second) {
                    toChange.insert(dot);
                } else if (dot.second == instr.second) {
                    toDelete.insert(dot);
                }
            }
        }
        for (auto del : toChange) {
            auto it = input->dots.find(del);
            input->dots.erase(it);
            if (instr.first > 0) {
                input->dots.insert(std::make_pair(instr.first - (del.first - instr.first), del.second));
            } else {
                input->dots.insert(std::make_pair(del.first, instr.second - (del.second - instr.second)));
            }
        }
        break;
    }
    return input->dots.size();
}

void printDots(Input *input, const uint64_t xMax, const uint64_t yMax)
{
    std::vector<char> matrix(xMax * yMax, ' ');
    for (auto dot : input->dots) {
        matrix[dot.second * xMax + dot.first] = '#';
    }
    for (size_t j = 0; j < yMax; ++j) {
        for (size_t i = 0; i < xMax; ++i) {
            if (matrix[j * xMax + i] == '#') {
                print("█");
            } else {
                print(" ");
            }
        }
        println("");
    }
}

std::string findSolution2(Input *input)
{
    for (auto instr : input->instructions) {
        std::set<std::pair<uint64_t, uint64_t>> toChange;
        std::set<std::pair<uint64_t, uint64_t>> toDelete;
        if (instr.first > 0) {
            for (auto dot : input->dots) {
                if (dot.first > instr.first) {
                    toChange.insert(dot);
                } else if (dot.first == instr.first) {
                    toDelete.insert(dot);
                }
            }
        } else {
            for (auto dot : input->dots) {
                if (dot.second > instr.second) {
                    toChange.insert(dot);
                } else if (dot.second == instr.second) {
                    toDelete.insert(dot);
                }
            }
        }
        for (auto del : toChange) {
            auto it = input->dots.find(del);
            input->dots.erase(it);
            if (instr.first > 0) {
                input->dots.insert(std::make_pair(instr.first - (del.first - instr.first), del.second));
            } else {
                input->dots.insert(std::make_pair(del.first, instr.second - (del.second - instr.second)));
            }
        }
    }
    uint64_t xMax = 0;
    uint64_t yMax = 0;
    for (auto dot : input->dots) {
        if (dot.first > xMax) {
            xMax = dot.first;
        }
        if (dot.second > yMax) {
            yMax = dot.second;
        }
    }

    printDots(input, xMax + 1, yMax + 1);

    return "";
}

std::string process1(std::string file)
{
    Input input;
    parse::read<Input *>(file, '\n', convertInput, &input);
    auto res = findSolution1(&input);
    return std::to_string(res);
}

std::string process2(std::string file)
{
    Input input;
    parse::read<Input *>(file, '\n', convertInput, &input);
    return findSolution2(&input);
}
