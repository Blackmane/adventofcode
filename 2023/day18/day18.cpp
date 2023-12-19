/**
 * @file    day18.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    18 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day18.h"

#include "common.h"

struct Lagoon {
    int64_t area = 0;
    int64_t perimeter = 0;
    int64_t i = 0;
    int64_t PicksTheorem()
    {
        return area + perimeter / 2 + 1;
    }
};

std::pair<char, int> convert1(const std::string &line)
{
    auto parts = parse::split(line, ' ');
    return { parts[0][0], stoi(parts[1]) };
}

const std::string DIRS("RDLU");

std::pair<char, int> convert2(const std::string &line)
{
    auto parts = parse::split(line, ' ');
    size_t idx = 0;
    return { DIRS[parts[2][7] - '0'], stoll(parts[2].substr(2, 5), &idx, 16) };
}

void insert(std::pair<char, int> op, Lagoon *lagoon)
{
    auto dist = op.second;
    lagoon->perimeter += dist;
    switch (op.first) {
        case 'D':
            lagoon->i += dist;
            break;
        case 'U':
            lagoon->i -= dist;
            break;
        case 'L':
            lagoon->area += lagoon->i * dist;
            break;
        case 'R':
            lagoon->area -= lagoon->i * dist;
            break;
    }
}

std::string day18::process1(std::string file)
{
    Lagoon lagoon;
    parse::read<std::pair<char, int>, Lagoon *>(file, '\n', convert1, insert, &lagoon);
    return std::to_string(lagoon.PicksTheorem());
}

std::string day18::process2(std::string file)
{
    Lagoon lagoon;
    parse::read<std::pair<char, int>, Lagoon *>(file, '\n', convert2, insert, &lagoon);
    return std::to_string(lagoon.PicksTheorem());
}
