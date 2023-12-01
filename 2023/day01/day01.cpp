/**
 * @file    day01.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    01 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day01.h"

#include "common.h"

std::string day01::process1(std::string file)
{
    uint64_t result = 0;
    parse::read<uint64_t *>(
        file, '\n',
        [](uint64_t *sum, const std::string &line) {
            auto parsed = parse::filterDecimal(line);
            int value = 10 * (parsed[0] - '0') + (parsed[parsed.size() - 1] - '0');
            (*sum) += value;
        },
        &result);

    return std::to_string(result);
}

std::string day01::process2(std::string file)
{
    uint64_t result = 0;
    parse::read<uint64_t *>(
        file, '\n',
        [](uint64_t *sum, const std::string &line) {
            auto parsed = convert::literalsToNumber(line, true);
            int value = 10 * (parsed[0] - '0') + (parsed[parsed.size() - 1] - '0');
            (*sum) += value;
        },
        &result);

    return std::to_string(result);
}