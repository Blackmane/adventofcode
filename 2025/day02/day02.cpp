/**
 * @file    day02.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    02 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day02.h"

#include "common.h"

#include <cmath>
#include <unordered_set>

std::string day02::process1(std::string file)
{
    uint64_t sum = 0;
    parse::read<uint64_t *>(
        file, ',',
        [&](uint64_t *, const std::string &line) {
            auto parts = parse::split(line, '-');
            auto fromSize = parts[0].size();
            auto toSize = parts[1].size();
            if (fromSize % 2 == 1 && toSize == fromSize) {
                return;
            }
            auto sub0 = parts[0].substr(0, fromSize / 2);
            auto sub1 = parts[1].substr(0, toSize - (fromSize / 2));

            auto from = parse::getInteger(parts[0]);
            auto to = parse::getInteger(parts[1]);

            auto fromSub = parse::getInteger(sub0);
            auto toSub = parse::getInteger(sub1);

            for (uint64_t i = fromSub; i <= toSub; i++) {
                auto digits = op::digits(i);
                uint64_t num = i * std::pow(10, digits) + i;
                if (from <= num && num <= to) {
                    sum += num;
                } else if (num > to) {
                    break;
                }
            }
        },
        &sum);
    return std::to_string(sum);
}

// Digits, Times -> multiplier
std::map<std::pair<int, int>, uint64_t> prods = {
    { { 1, 2 }, 11 },          { { 1, 3 }, 111 },     { { 1, 4 }, 1111 },     { { 1, 5 }, 11111 },
    { { 1, 6 }, 111111 },      { { 1, 7 }, 1111111 }, { { 1, 8 }, 11111111 }, { { 1, 9 }, 111111111 },
    { { 1, 10 }, 1111111111 }, { { 2, 2 }, 101 },     { { 2, 3 }, 10101 },    { { 2, 4 }, 1010101 },
    { { 2, 5 }, 101010101 },   { { 3, 2 }, 1001 },    { { 3, 3 }, 1001001 },  { { 4, 2 }, 10001 },
    { { 5, 2 }, 100001 }
};

uint64_t repeat(uint64_t num, int limit, int times)
{
    auto digits = op::digits(num);
    for (; digits > limit; digits--) {
        num = num / 10;
    }

    auto it = prods.find({ digits, times });
    if (it == prods.end()) {
        return 0;
    }
    return num * it->second;
}

std::string day02::process2(std::string file)
{
    uint64_t sum = 0;
    parse::read(file, ',', [&](const std::string &line) {
        auto parts = parse::split(line, '-');
        auto fromSize = parts[0].size();
        auto toSize = parts[1].size();

        auto from = parse::getInteger(parts[0]);
        auto to = parse::getInteger(parts[1]);

        std::unordered_set<uint64_t> found;
        for (int i = 1, n = toSize / 2; i <= n; i++) {
            if (toSize % i != 0 && fromSize % i != 0) {
                continue;
            }

            auto sub0 = parts[0].substr(0, i);
            auto sub1 = parts[1].substr(0, toSize - fromSize + i);
            auto fromSub = parse::getInteger(sub0);
            auto toSub = parse::getInteger(sub1);

            for (int d = 1; d <= i + 1; d++) {
                for (uint64_t cur = fromSub; cur <= toSub; cur++) {
                    uint64_t num = repeat(cur, d, toSize / d);
                    if (from <= num && num <= to) {
                        found.insert(num);
                    }
                    if (toSize != fromSize) {
                        num = repeat(cur, d, fromSize / d);
                        if (from <= num && num <= to) {
                            found.insert(num);
                        }
                    }
                    if (num > to) {
                        break;
                    }
                }
            }
        }

        for (auto &val : found) {
            sum += val;
        }
    });
    return std::to_string(sum);
}
