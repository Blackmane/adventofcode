/**
 * @file    day12.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2023
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

#include <queue>

std::map<std::tuple<std::string, uint, std::queue<uint>>, uint64_t> memoization;

uint64_t resolve(const std::string &springs, uint curr, std::queue<uint> numbers)
{
    auto it = memoization.find({ springs, curr, numbers });
    if (it != memoization.end()) {
        return it->second;
    }

    if (springs.empty()) {
        // Can't continue
        if (numbers.empty()) {
            return 1;
        }
        if (numbers.size() == 1 && curr == numbers.front()) {
            // End with the current number
            return 1;
        }
        return 0;
    }
    // Some char in springs
    if (numbers.empty()) {
        // !springs.empty
        for (auto c : springs) {
            if (c == '#') {
                return 0;
            }
        }
        return 1;
    }
    if (curr == numbers.front()) {
        if (springs[0] == '#') {
            // After '###' must be a `.` or `?`
            return 0;
        }
        auto oldNumbers = numbers;
        numbers.pop();
        auto val = resolve(springs.substr(1, springs.size() - 1), 0, numbers);
        memoization.insert({ { springs, curr, std::move(oldNumbers) }, val });
        return val;
    }
    // curr != numbers.front()
    if (curr == 0) {
        uint64_t count = 0;
        if (springs[0] == '#' || springs[0] == '?') {
            count += resolve(springs.substr(1, springs.size() - 1), 1, numbers);
        }
        if (springs[0] == '.' || springs[0] == '?') {
            count += resolve(springs.substr(1, springs.size() - 1), 0, numbers);
        }
        memoization.insert({ { springs, curr, numbers }, count });
        return count;
    }
    // curr != numbers.front() && curr >0
    if (springs[0] == '.') {
        return 0;
    }

    auto val = resolve(springs.substr(1, springs.size() - 1), curr + 1, numbers);
    memoization.insert({ { springs, curr, numbers }, val });
    return val;
}

std::string day12::process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    uint64_t count = 0;
    for (auto &&line : list) {
        auto parts = parse::split(line, ' ');
        auto numbers = parse::getIntegers(op::replaceAll(parts[1], ',', ' '));
        std::queue<uint> numbersQueue;
        for (auto num : numbers) {
            numbersQueue.push(num);
        }
        count += resolve(parts[0], 0, numbersQueue);
    }
    return std::to_string(count);
}

std::queue<uint> repeatAsQueue(std::vector<uint64_t> &list, uint n)
{
    std::queue<uint> result;
    size_t size = list.size();
    for (uint i = 0; i < n; i++) {
        for (uint j = 0; j < size; j++) {
            result.push(list[j]);
        }
    }
    return result;
}

std::string repeat(const std::string &list, uint n)
{
    auto result = list;
    size_t size = list.size();
    result.reserve((size + 1) * n);
    for (uint i = 1; i < n; i++) {
        result.push_back('?');
        for (uint j = 0; j < size; j++) {
            result.push_back(list[j]);
        }
    }
    return result;
}

std::string day12::process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    uint64_t count = 0;
    for (auto &&line : list) {
        auto parts = parse::split(line, ' ');
        auto numbers = parse::getIntegers(op::replaceAll(parts[1], ',', ' '));
        count += resolve(repeat(parts[0], 5), 0, repeatAsQueue(numbers, 5));
    }
    return std::to_string(count);
}
