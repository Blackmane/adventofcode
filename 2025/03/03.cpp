/**
 * @file    03.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    03 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "03.h"

#include "common.h"

std::string day03::process1(std::string file)
{
    uint64_t sum = 0;
    parse::read(file, '\n', [&](const std::string &line) {
        auto first = '0';
        auto second = '0';
        for (int i = 0, n = line.size(); i < n; i++) {
            auto c = line[i];
            if (i < n - 1 && c > first) {
                first = c;
                second = '0';
            } else if (c > second) {
                second = c;
            }
        }
        std::string num = { first, second };
        sum += parse::getInteger(num);
    });
    return std::to_string(sum);
}

std::string day03::process2(std::string file)
{
    uint64_t sum = 0;
    parse::read(file, '\n', [&](const std::string &line) {
        std::string num('0', 12);
        int len = line.size();
        int window = len - 12;
        int pos = 0;
        for (int i = 0; i < 12; i++) {
            int maxSub = '0';
            int posSub = pos;
            int last = pos + window + (i - pos);
            for (int s = posSub; s <= last; s++) {
                auto c = line[s];
                if (c > maxSub) {
                    maxSub = c;
                    posSub = s;
                }
            }
            num[i] = maxSub;
            pos = posSub + 1;
        }
        sum += parse::getInteger(num);
    });
    return std::to_string(sum);
}