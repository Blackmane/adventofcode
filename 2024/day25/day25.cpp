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

#include <optional>

std::string day25::process1(std::string file)
{
    std::vector<std::vector<int>> locks;
    std::vector<std::vector<int>> keys;

    std::vector<int> cur;
    std::optional<bool> isKey;

    parse::read(file, '\n', [&](const std::string &line) {
        if (line.empty()) {
            if (isKey.value()) {
                keys.push_back(cur);
            } else {
                locks.push_back(cur);
            }
            isKey = {};
            return;
        }

        if (!isKey.has_value()) {
            isKey = line[0] == '.';
            cur.resize(line.size());
            for (auto &c : cur) {
                if (isKey.value()) {
                    c = 6;
                } else {
                    c = -1;
                }
            }
        }

        for (int i = 0, n = line.size(); i < n; i++) {
            if (isKey.value() && line[i] == '.') {
                cur[i]--;
            }
            if (!isKey.value() && line[i] == '#') {
                cur[i]++;
            }
        }
    });
    if (isKey.value()) {
        keys.push_back(cur);
    } else {
        locks.push_back(cur);
    }

    uint64_t count = 0;
    for (auto &lock : locks) {
        for (auto &key : keys) {
            bool fit = true;
            for (int i = 0, n = lock.size(); i < n; i++) {
                if (lock[i] + key[i] > 5) {
                    fit = false;
                    break;
                }
            }
            if (fit) {
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