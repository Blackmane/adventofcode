/**
 * @file    02.cpp
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

#include "02.h"

#include "common.h"

#include <cmath>

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

uint64_t repeat(uint64_t num, int times)
{
    if (times <= 1) {
        return 0;
    }

    auto digits = op::digits(num);
    uint64_t result = num;
    for (int i = 0; i < times - 1; i++) {
        result = result * std::pow(10, digits) + num;
    }
    return result;
}

uint64_t firstDigits(uint64_t num, int limit)
{
    auto digits = op::digits(num);
    for (; digits > limit; digits--) {
        num = num / 10;
    }
    return num;
}

std::string day02::process2(std::string file)
{
    uint64_t sum = 0;
    parse::read(file, ',', [&](const std::string &line) {
        std::set<uint64_t> found;
        auto parts = parse::split(line, '-');
        auto fromSize = parts[0].size();
        auto toSize = parts[1].size();

        auto from = parse::getInteger(parts[0]);
        auto to = parse::getInteger(parts[1]);

        for (int i = 1, n = toSize / 2; i <= n; i++) {
            auto sub0 = parts[0].substr(0, i);
            auto sub1 = parts[1].substr(0, toSize - fromSize + i);
            auto fromSub = parse::getInteger(sub0);
            auto toSub = parse::getInteger(sub1);

            for (uint64_t cur = fromSub; cur <= toSub; cur++) {
                auto digits = op::digits(cur);
                for (int d = 1; d <= digits; d++) {
                    uint64_t num = repeat(firstDigits(cur, d), toSize / d);
                    if (from <= num && num <= to) {
                        found.insert(num);
                    }
                    num = repeat(firstDigits(cur, d), fromSize / d);
                    if (from <= num && num <= to) {
                        found.insert(num);
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
