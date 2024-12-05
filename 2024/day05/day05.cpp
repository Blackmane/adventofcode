/**
 * @file    day05.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    05 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day05.h"

#include "common.h"

#include <unordered_set>

struct Data {
    std::unordered_multimap<int64_t, int64_t> order;
    int64_t sum = 0;
};

std::vector<int64_t> getNumbers(const std::string &line)
{
    auto num = parse::split(line, ',');
    std::vector<int64_t> numbers;
    numbers.reserve(num.size());
    for (auto &n : num) {
        numbers.push_back(std::stoll(n));
    }
    return numbers;
}

int64_t getMid(const std::vector<int64_t> &numbers, const std::unordered_multimap<int64_t, int64_t> &order)
{
    std::unordered_set<int64_t> visited;
    bool valid = true;
    for (auto n : numbers) {
        auto range = order.equal_range(n);
        for (auto i = range.first; i != range.second; i++) {
            if (visited.count(i->second) > 0) {
                valid = false;
                return 0;
            }
        }
        visited.insert(n);
    }
    if (valid) {
        return numbers[numbers.size() / 2];
    }
    return 0;
}

int64_t fixAndGetMid(const std::vector<int64_t> &numbers, const std::unordered_multimap<int64_t, int64_t> &order)
{
    if (getMid(numbers, order) > 0) {
        return 0;
    }

    std::unordered_map<int64_t, int> frequency;
    for (auto n : numbers) {
        frequency.insert({ n, 0 });
    }
    for (auto n : numbers) {
        auto range = order.equal_range(n);
        for (auto i = range.first; i != range.second; i++) {
            auto it = frequency.find(i->second);
            if (it != frequency.end()) {
                it->second++;
            }
        }
    }

    int mid = numbers.size() / 2;
    for (auto n : frequency) {
        if (n.second == mid) {
            return n.first;
            break;
        }
    }
    return 0;
}

std::string day05::process1(std::string file)
{
    Data data;
    bool readOrder = true;
    parse::read<Data &>(
        file, '\n',
        [&](Data &d, const std::string &line) {
            if (readOrder) {
                if (line.empty()) {
                    readOrder = false;
                    return;
                }
                auto numbers = parse::split(line, '|');
                d.order.insert({ std::stoll(numbers[0]), std::stoll(numbers[1]) });
            } else {
                auto numbers = getNumbers(line);
                data.sum += getMid(numbers, d.order);
            }
        },
        data);

    return std::to_string(data.sum);
}

std::string day05::process2(std::string file)
{
    Data data;
    bool readOrder = true;
    parse::read<Data &>(
        file, '\n',
        [&](Data &d, const std::string &line) {
            if (readOrder) {
                if (line.empty()) {
                    readOrder = false;
                    return;
                }
                auto numbers = parse::split(line, '|');
                d.order.insert({ std::stoll(numbers[0]), std::stoll(numbers[1]) });
            } else {
                auto numbers = getNumbers(line);
                data.sum += fixAndGetMid(numbers, d.order);
            }
        },
        data);

    return std::to_string(data.sum);
}