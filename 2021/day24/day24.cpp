/**
 * @file    day24.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    24 Dec 2021
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

#include <deque>

bool check(uint64_t modelNumber, std::vector<std::string> *instructions)
{
    auto inpArray = std::to_string(modelNumber);
    size_t inpIndex = 0;
    for (auto c : inpArray) {
        if (c == '0') {
            return false;
        }
    }

    int64_t w = 0;
    int64_t x = 0;
    int64_t y = 0;
    int64_t z = 0;
    for (auto &i : *instructions) {
        auto parts = parse::split(i, ' ');

        auto dest = [&]() {
            switch (parts[1][0]) {
                case 'w':
                    return &w;
                case 'x':
                    return &x;
                case 'y':
                    return &y;
                case 'z':
                    return &z;
                default:
                    return &x;
            }
        }();
        if (parts[0] == "inp") { // inp
            *dest = inpArray[inpIndex++] - '0';
        } else {
            auto value = [&]() -> int64_t {
                switch (parts[2][0]) {
                    case 'w':
                        return w;
                    case 'x':
                        return x;
                    case 'y':
                        return y;
                    case 'z':
                        return z;
                    default:
                        return std::stoll(parts[2]);
                }
            }();
            switch (parts[0][0]) {
                case 'a': // add
                    *dest += value;
                    break;
                case 'm':
                    if (parts[0] == "mul") { // mul
                        *dest *= value;
                    } else { // mod
                        *dest = *dest % value;
                    }
                    break;
                case 'd': // div
                    *dest /= value;
                    break;
                case 'e': // eql
                    *dest = (*dest == value) ? 1 : 0;
                    break;
            }
        }
    }
    return z == 0;
}

struct State {
    size_t index;
    int offset;
};

uint64_t toUint(std::vector<int> *values)
{
    uint64_t res = 0;
    for (auto v : *values) {
        res *= 10;
        res += v;
    }
    return res;
}

uint64_t findSolution(std::vector<std::string> *instructions, bool max)
{
    std::vector<int> solution(14, 0);
    std::deque<State> stack;
    for (int i = 0; i < 14; ++i) {
        auto parts = parse::split(instructions->at(i * 18 + 4), ' ');
        if (parts[2][0] == '1') {
            // Push
            State state;
            state.index = i;
            parts = parse::split(instructions->at(i * 18 + 15), ' ');
            state.offset = std::stoi(parts[2]);
            stack.push_back(state);
        } else {
            // Pop
            auto state = stack.back();
            stack.pop_back();
            parts = parse::split(instructions->at(i * 18 + 5), ' ');
            auto diff = state.offset + std::stoi(parts[2]);
            int x;
            if (max) {
                for (x = 9; x > 0; --x) {
                    if (diff + x > 0 && diff + x <= 9) {
                        break;
                    }
                }
            } else {
                for (x = 1; x <= 9; ++x) {
                    if (diff + x > 0 && diff + x <= 9) {
                        break;
                    }
                }
            }
            solution[state.index] = x;
            solution[i] = diff + x;
        }
    }
    return toUint(&solution);
}

std::string day24::process1(std::string file)
{
    std::vector<std::string> instructions;
    parse::read_all(file, &instructions);
    auto solution = findSolution(&instructions, true);
    if (check(solution, &instructions)) {
        return std::to_string(solution);
    }
    return "0";
}

std::string day24::process2(std::string file)
{
    std::vector<std::string> instructions;
    parse::read_all(file, &instructions);
    auto solution = findSolution(&instructions, false);
    if (check(solution, &instructions)) {
        return std::to_string(solution);
    }
    return "0";
}