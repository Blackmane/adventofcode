/**
 * @file    day09.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    09 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day09.h"

#include "common.h"

typedef std::pair<int64_t, int64_t> Pos;

uint64_t execute(std::vector<std::string> &list, int64_t len)
{
    Pos zero(0, 0);
    std::vector<Pos> rope(len, zero);
    std::set<Pos> tailVisited;
    tailVisited.insert(rope[len - 1]);

    for (auto &&instruction : list) {
        auto move = std::stoll(instruction.substr(2, instruction.size() - 2));
        int i = 0, j = 0;
        switch (instruction[0]) {
            case 'U':
                i = 1;
                break;
            case 'D':
                i = -1;
                break;
            case 'R':
                j = 1;
                break;
            case 'L':
                j = -1;
                break;
        }
        for (int m = 0; m < move; ++m) {
            rope[0] = Pos(rope[0].first + i, rope[0].second + j);
            for (int r = 1, n = rope.size(); r < n; ++r) {
                int dj = rope[r - 1].second - rope[r].second;
                int di = rope[r - 1].first - rope[r].first;
                if (std::max(std::abs(di), std::abs(dj)) <= 1) {
                    continue;
                }

                int ki = op::normalizeDirection(di);
                int kj = op::normalizeDirection(dj);
                rope[r] = Pos(rope[r].first + ki, rope[r].second + kj);
            }
            tailVisited.insert(rope[len - 1]);
        }
    }
    return tailVisited.size();
}

std::string day09::process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = execute(list, 2);
    return std::to_string(result);
}

std::string day09::process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = execute(list, 10);
    return std::to_string(result);
}
