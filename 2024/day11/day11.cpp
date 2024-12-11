/**
 * @file    day11.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    11 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day11.h"

#include "common.h"

#include <cmath>

void increment(std::unordered_map<uint64_t, uint64_t> &map, uint64_t key, uint64_t value)
{
    auto it = map.find(key);
    if (it == map.end()) {
        map.insert({ key, value });
    } else {
        it->second += value;
    }
}

std::string run(std::string file, int blinks)
{
    auto lines = parse::read_all(file);
    auto intergers = parse::getIntegers(lines[0]);

    std::unordered_map<uint64_t, uint64_t> stones;
    for (auto i : intergers) {
        stones.insert({ i, 1 });
    }
    for (int i = 0; i < blinks; i++) {
        std::unordered_map<uint64_t, uint64_t> newStones;
        newStones.reserve(2 * stones.size());
        for (auto &&stone : stones) {
            if (stone.first == 0) {
                increment(newStones, 1, stone.second);
            } else {
                auto digits = op::digits(stone.first);
                if (digits % 2 == 0) {
                    uint64_t pow = std::pow(10, digits / 2);
                    increment(newStones, stone.first / pow, stone.second);
                    increment(newStones, stone.first % pow, stone.second);
                } else {
                    increment(newStones, stone.first * 2024, stone.second);
                }
            }
        }
        stones.swap(newStones);
    }
    uint64_t count = 0;
    for (auto &&stone : stones) {
        count += stone.second;
    }
    return std::to_string(count);
}

std::string day11::process1(std::string file)
{
    return run(file, 25);
}

std::string day11::process2(std::string file)
{
    return run(file, 75);
}