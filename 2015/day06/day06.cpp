/**
 * @file    day06.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    05 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day06.h"

#include "common.h"

#include <array>

enum Type { turn_on, turn_off, toggle };

struct Action {
    Type type;
    std::pair<uint64_t, uint64_t> from;
    std::pair<uint64_t, uint64_t> to;
};

Action process(const std::string &line)
{
    Action action;
    if (line[1] == 'o') {
        action.type = Type::toggle;
    } else {
        if (line[6] == 'n') {
            action.type = Type::turn_on;
        } else {
            action.type = Type::turn_off;
        }
    }
    auto numbers = parse::getIntegers(line);
    action.from = { numbers[0], numbers[1] };
    action.to = { numbers[2], numbers[3] };

    return action;
}

void insert(Action action, std::vector<Action> *actions)
{
    actions->push_back(std::move(action));
}

std::string day06::process1(std::string file)
{
    std::vector<Action> actions;
    parse::read<Action, std::vector<Action> *>(file, '\n', process, insert, &actions);

    std::array<std::bitset<1000>, 1000> matrix;
    for (auto &&action : actions) {
        for (uint64_t i = action.from.first; i <= action.to.first; i++) {
            for (uint64_t j = action.from.second; j <= action.to.second; j++) {
                switch (action.type) {
                    case Type::turn_on:
                        matrix[i][j] = true;
                        break;
                    case Type::turn_off:
                        matrix[i][j] = false;
                        break;
                    case Type::toggle:
                        matrix[i][j] = !matrix[i][j];
                        break;
                }
            }
        }
    }
    uint64_t result = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (matrix[i][j]) {
                result++;
            }
        }
    }
    return std::to_string(result);
}

std::string day06::process2(std::string file)
{
    std::vector<Action> actions;
    parse::read<Action, std::vector<Action> *>(file, '\n', process, insert, &actions);

    std::array<std::array<uint8_t, 1000>, 1000> matrix = { 0 };
    for (auto &&action : actions) {
        for (uint64_t i = action.from.first; i <= action.to.first; i++) {
            for (uint64_t j = action.from.second; j <= action.to.second; j++) {
                switch (action.type) {
                    case Type::turn_on:
                        matrix[i][j]++;
                        break;
                    case Type::turn_off:
                        if (matrix[i][j] > 0) {
                            matrix[i][j]--;
                        }
                        break;
                    case Type::toggle:
                        matrix[i][j] += 2;
                        break;
                }
            }
        }
    }
    uint64_t result = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            result += matrix[i][j];
        }
    }
    return std::to_string(result);
}