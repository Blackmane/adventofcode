/**
 * @file    day17.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    17 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day17.h"

#include "common.h"

std::string runProgram(const std::vector<int> program, int64_t registerA, int64_t registerB, int64_t registerC)
{
    auto getOperand = [&](int op) -> int64_t {
        if (op <= 3) {
            return op;
        }
        if (op == 4) {
            return registerA;
        }
        if (op == 5) {
            return registerB;
        }
        if (op == 6) {
            return registerC;
        }
        return 0;
    };

    std::string output;
    for (int i = 0, n = program.size(); i < n;) {
        int op = program[i];
        switch (op) {
            case 0:
                registerA = registerA >> getOperand(program[i + 1]);
                break;
            case 1:
                registerB = registerB ^ program[i + 1];
                break;
            case 2:
                registerB = 7 & getOperand(program[i + 1]);
                break;
            case 3:
                if (registerA == 0) {
                    i += 2;
                } else {
                    i = program[i + 1];
                }
                break;
            case 4:
                registerB = registerB ^ registerC;
                break;
            case 5:
                output.push_back('0' + getOperand(program[i + 1]) % 8);
                output.push_back(',');
                break;
            case 6:
                registerB = registerA >> getOperand(program[i + 1]);
                break;
            case 7:
                registerC = registerA >> getOperand(program[i + 1]);
                break;
            default:
                break;
        }

        if (op != 3) {
            i += 2;
        }
    }

    output.pop_back();
    return output;
}

std::string day17::process1(std::string file)
{
    auto input = parse::read_all(file);
    int registerPos = std::string{ "Register X: " }.length();
    int instructPos = std::string{ "Program: " }.length();
    int registerA = std::stoi(input[0].substr(registerPos, input[0].length() - registerPos));
    int registerB = std::stoi(input[1].substr(registerPos, input[1].length() - registerPos));
    int registerC = std::stoi(input[2].substr(registerPos, input[2].length() - registerPos));

    auto parts = parse::split(input[4].substr(instructPos, input[4].length() - instructPos), ',');
    std::vector<int> program;
    for (auto p : parts) {
        program.push_back(std::stoi(p));
    }

    return runProgram(program, registerA, registerB, registerC);
}

std::string day17::process2(std::string file)
{
    // Sorry, found by hand
    return "0";
}