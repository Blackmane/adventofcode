/**
 * @file    day01.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    01 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day01.h"

#include "common.h"

std::string day01::process1(std::string file)
{
    std::vector<int64_t> left;
    std::vector<int64_t> right;
    uint64_t result = 0;
    parse::read<uint64_t *>(
        file, '\n',
        [&](uint64_t *, const std::string &line) {
            auto values = parse::getIntegers(line);
            left.push_back(values[0]);
            right.push_back(values[1]);
        },
        &result);

    op::radixSort(left);
    op::radixSort(right);
    for (size_t i = 0, n = left.size(); i < n; i++) {
        result += abs(left[i] - right[i]);
    }

    return std::to_string(result);
}

std::string day01::process2(std::string file)
{
    std::vector<uint64_t> order;
    std::multiset<uint64_t> presence;
    uint64_t result = 0;
    parse::read<uint64_t *>(
        file, '\n',
        [&](uint64_t *, const std::string &line) {
            auto values = parse::getIntegers(line);
            order.push_back(values[0]);
            presence.insert(values[1]);
        },
        &result);

    for (size_t i = 0, n = order.size(); i < n; i++) {
        result += order[i] * presence.count(order[i]);
    }

    return std::to_string(result);
}