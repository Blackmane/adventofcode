/**
 * @file    day25.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    25 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day25.h"

#include "common.h"

std::string day25::process1(std::string file)
{
    std::vector<uint64_t> locks;
    std::vector<uint64_t> keys;

    uint64_t cur = 0;
    parse::read(file, '\n', [&](const std::string &line) {
        if (line.empty()) {
            if ((cur & 1) == 1) {
                keys.push_back(cur);
            } else {
                locks.push_back(cur);
            }
            cur = 0;
            return;
        }
        for (auto c : line) {
            cur = cur << 1;
            if (c == '#') {
                cur += 1;
            }
        }
    });
    if ((cur & 1) == 1) {
        keys.push_back(cur);
    } else {
        locks.push_back(cur);
    }

    uint64_t count = 0;
    for (auto lock : locks) {
        for (auto key : keys) {
            if ((lock & key) == 0) {
                count++;
            }
        }
    }
    return std::to_string(count);
}

std::string day25::process2(std::string file)
{
    return "0";
}