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

uint64_t execute(std::vector<std::string> &list)
{
    Pos head(0, 0);
    Pos tail(0, 0);
    std::set<Pos> tailVisited;
    tailVisited.insert(tail);

    for (auto &&instruction : list) {
        auto move = std::stoll(instruction.substr(2, instruction.size() - 2));
        int i = 0, j = 0, ki = 0, kj = 0;
        switch (instruction[0]) {
            case 'U':
                i = 1;
                kj = head.second - tail.second;
                break;
            case 'D':
                i = -1;
                kj = head.second - tail.second;
                break;
            case 'R':
                j = 1;
                ki = head.first - tail.first;
                break;
            case 'L':
                j = -1;
                ki = head.first - tail.first;
                break;
        }
        for (int m = 0; m < move; ++m) {
            Pos newHead(head.first + i, head.second + j);
            if (tail != head) {
                if (std::max(std::abs(newHead.first - tail.first), std::abs(newHead.second - tail.second)) > 1) {
                    // Follow
                    Pos newTail(tail.first + i + ki, tail.second + j + kj);
                    ki = 0;
                    kj = 0;
                    tail = newTail;
                }
                // else still near
            }
            // else do nothing
            head = newHead;
            tailVisited.insert(tail);
        }
    }
    return tailVisited.size();
}

uint64_t executeTen(std::vector<std::string> &list)
{
    Pos zero(0, 0);
    std::vector<Pos> rope(10, zero);
    std::set<Pos> tailVisited;
    tailVisited.insert(rope[9]);

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

                int ki = 0;
                int kj = 0;
                kj = op::normalizeDirection(dj);
                ki = op::normalizeDirection(di);
                rope[r] = Pos(rope[r].first + ki, rope[r].second + kj);
            }
            tailVisited.insert(rope[9]);
        }
    }
    return tailVisited.size();
}

std::string process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = execute(list);
    return std::to_string(result);
}

std::string process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = executeTen(list);
    return std::to_string(result);
}
