/**
 * @file    01.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    01 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "01.h"

#include "common.h"

std::string day01::process1(std::string file)
{
    int64_t sum = 50;
    int count = 0;
    parse::read<int64_t *>(
        file, '\n',
        [&](int64_t *, const std::string &line) {
            auto part = line.substr(1, line.size() - 1);
            auto value = parse::getInteger(part);
            if (line[0] == 'L') {
                sum -= value;
            } else {
                sum += value;
            }
            if (sum % 100 == 0) {
                count++;
            }
        },
        &sum);
    return std::to_string(count);
}

std::string day01::process2(std::string file)
{
    int64_t sum = 50;
    int count = 0;
    parse::read<int64_t *>(
        file, '\n',
        [&](int64_t *, const std::string &line) {
            auto part = line.substr(1, line.size() - 1);
            int64_t value = parse::getInteger(part);
            count += (value / 100);
            value = value % 100;
            if (value > 0) {
                if (line[0] == 'L') {
                    if (sum != 0 && sum <= value) {
                        count++;
                    }
                    sum -= value;
                } else {
                    sum += value;
                    if (sum >= 100) {
                        count++;
                    }
                }
            }
            sum = (sum + 100) % 100;
        },
        &sum);
    return std::to_string(count);
}