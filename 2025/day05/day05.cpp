/**
 * @file    day05.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    05 Dec 2025
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
#include <vector>

std::string day05::process1(std::string file)
{
    std::vector<std::pair<uint64_t, uint64_t>> ranges;
    uint64_t count = 0;
    bool first = true;

    auto insert = [&](const std::string &line) {
        auto parts = parse::split(line, '-');
        ranges.push_back({ parse::getInteger(parts[0]), parse::getInteger(parts[1]) });
    };
    auto check = [&](uint64_t id) {
        for (auto &&[left, right] : ranges) {
            if (left <= id && id <= right) {
                count++;
                return;
            }
        }
    };

    parse::read(file, '\n', [&](const std::string &line) {
        if (line.empty()) {
            first = false;
            return;
        }
        if (first) {
            insert(line);
        } else {
            check(parse::getInteger(line));
        }
    });

    return std::to_string(count);
}

std::string day05::process2(std::string file)
{
    std::vector<op::Range> ids;
    bool done = false;

    parse::read(file, '\n', [&](const std::string &line) {
        if (line.empty() || done) {
            done = true;
            return;
        }
        auto parts = parse::split(line, '-');
        auto from = parse::getInteger(parts[0]);
        auto to = parse::getInteger(parts[1]);
        ids.push_back({ from, to - from + 1 });
    });

    uint64_t count = 0;

    while (!ids.empty()) {
        auto range = ids.back();
        ids.pop_back();
        bool expanded = false;

        std::erase_if(ids, [&](op::Range x) {
            auto res = op::merge(x, range);
            if (res.has_value()) {
                range = res.value();
                expanded = true;
                return true;
            }
            return false;
        });

        if (expanded) {
            ids.push_back(range);
        } else {
            count += range.len;
        }
    }

    return std::to_string(count);
}