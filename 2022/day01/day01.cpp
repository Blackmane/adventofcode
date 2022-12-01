/**
 * @file    day01.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    30 Nov 2022
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
#include <algorithm>

std::string process1(std::string file)
{
    uint64_t max = 0;
    uint64_t current = 0;
    std::ifstream source;
    source.open(file, std::ifstream::in);
    std::string part;
    while (std::getline(source, part, '\n')) {
        if (part.size() > 0) {
            current += std::stoull(part);
        } else {
            if (current > max) {
                max = current;
            }
            current = 0;
        }
    }
    if (current > max) {
        max = current;
    }
    return std::to_string(max);
}

std::string process2(std::string file)
{
    std::vector<uint64_t> list;
    uint64_t current = 0;
    std::ifstream source;
    source.open(file, std::ifstream::in);
    std::string part;
    while (std::getline(source, part, '\n')) {
        if (part.size() > 0) {
            current += std::stoull(part);
        } else {
            std::cout << current << std::endl;
            list.push_back(current);
            current = 0;
        }
    }
    list.push_back(current);
    std::sort(list.begin(), list.end());
    auto n = list.size();
    return std::to_string(list[n - 1] + list[n - 2] + list[n - 3]);
}
