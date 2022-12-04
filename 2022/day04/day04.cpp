/**
 * @file    day04.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    03 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day04.h"

#include "common.h"

uint64_t checkRange1(const std::string &line)
{
    auto parts = parse::split(line, ',');

    auto min_a = std::stoll(parts[0].substr(0, parts[0].find('-')));
    auto max_a = std::stoll(parts[0].substr(parts[0].find('-') + 1, parts[0].size()));
    auto min_b = std::stoll(parts[1].substr(0, parts[1].find('-')));
    auto max_b = std::stoll(parts[1].substr(parts[1].find('-') + 1, parts[1].size()));

    if ((min_a <= min_b && max_a >= max_b) || (min_b <= min_a && max_b >= max_a)) {
        return 1;
    }
    return 0;
}

uint64_t checkRange2(const std::string &line)
{
    auto parts = parse::split(line, ',');

    auto min_a = std::stoll(parts[0].substr(0, parts[0].find('-')));
    auto max_a = std::stoll(parts[0].substr(parts[0].find('-') + 1, parts[0].size()));
    auto min_b = std::stoll(parts[1].substr(0, parts[1].find('-')));
    auto max_b = std::stoll(parts[1].substr(parts[1].find('-') + 1, parts[1].size()));

    if ((min_a <= min_b && max_a >= min_b) || (min_b <= min_a && max_b >= min_a)) {
        return 1;
    }
    return 0;
}

void add(uint64_t value, uint64_t *sum)
{
    *sum += value;
}

std::string process1(std::string file)
{
    uint64_t count = 0;
    parse::read<uint64_t, uint64_t *>(file, '\n', &checkRange1, &add, &count);
    return std::to_string(count);
}

std::string process2(std::string file)
{
    uint64_t count = 0;
    parse::read<uint64_t, uint64_t *>(file, '\n', &checkRange2, &add, &count);
    return std::to_string(count);
}
