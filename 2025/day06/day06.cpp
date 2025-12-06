/**
 * @file    day06.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    06 Dec 2025
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

enum operation { sum, prod };

std::string day06::process1(std::string file)
{
    auto data = parse::read_all(file);
    std::vector<operation> ops;
    std::vector<uint64_t> results;
    auto list = data.back();
    data.pop_back();
    for (char c : list) {
        if (c == '+') {
            ops.push_back(sum);
            results.push_back(0);
        }
        if (c == '*') {
            ops.push_back(prod);
            results.push_back(1);
        }
    }
    for (auto line : data) {
        auto values = parse::getIntegers(line);
        for (int i = 0, n = values.size(); i < n; i++) {
            if (ops[i] == operation::prod) {
                results[i] *= values[i];
            }
            if (ops[i] == operation::sum) {
                results[i] += values[i];
            }
        }
    }
    uint64_t sum = 0;
    for (auto value : results) {
        sum += value;
    }

    return std::to_string(sum);
}

uint64_t getVertical(int i, const std::vector<std::string> &data)
{
    uint64_t value = 0;
    for (auto line : data) {
        if (line[i] == ' ') {
            if (value > 0) {
                return value;
            }
        } else {
            value *= 10;
            value += line[i] - '0';
        }
    }
    return value;
}

std::string day06::process2(std::string file)
{
    auto data = parse::read_all(file);
    auto list = data.back();
    data.pop_back();
    uint64_t result = 0;
    operation op = operation::prod;
    uint64_t sum = 0;
    for (int i = 0, n = data[0].size(), m = list.size(); i < n; i++) {
        char c = i < m ? list[i] : ' ';
        if (c == ' ') {
            auto value = getVertical(i, data);
            if (value != 0) {
                if (op == operation::prod) {
                    result *= value;
                }
                if (op == operation::sum) {
                    result += value;
                }
            }
        } else {
            sum += result;
            if (c == '+') {
                op = operation::sum;
            }
            if (c == '*') {
                op = operation::prod;
            }
            result = getVertical(i, data);
        }
    }
    sum += result;

    return std::to_string(sum);
}