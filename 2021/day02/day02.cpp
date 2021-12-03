/**
 * @file    day02.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    02 Dec 2021
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
#include <iostream>

std::string findSolution1(std::vector<std::string> *values)
{
    uint64_t horizontal = 0;
    uint64_t depth      = 0;
    for (auto &value : *values) {
        uint64_t move = parse::getInteger(value);
        switch (value[0]) {
            case 'f':
                horizontal += move;
                break;
            case 'd':
                depth += move;
                break;
            case 'u':
                depth -= move;
                break;
            default:
                break;
        }
    }
    return std::to_string(horizontal * depth);
}

std::string findSolution2(std::vector<std::string> *values)
{
    uint64_t horizontal = 0;
    uint64_t depth      = 0;
    uint64_t aim        = 0;
    for (auto &value : *values) {
        uint64_t move = parse::getInteger(value);
        switch (value[0]) {
            case 'f':
                horizontal += move;
                depth += (aim * move);
                break;
            case 'd':
                aim += move;
                break;
            case 'u':
                aim -= move;
                break;
            default:
                break;
        }
    }
    return std::to_string(horizontal * depth);
}

std::string process1(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);

    std::string result = findSolution1(&valueList);
    return result;
}

std::string process2(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);

    std::string result = findSolution2(&valueList);
    return result;
}
