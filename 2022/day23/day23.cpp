/**
 * @file    day23.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    23 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day23.h"

#include "common.h"

#include <set>

typedef std::pair<int64_t, int64_t> Pos;
typedef std::set<Pos> Positions;

void convertInput(Positions *elves, const std::string &line, const uint64_t count)
{
    for (size_t j = 0, n = line.size(); j < n; j++) {
        if (line[j] == '#') {
            elves->insert(std::make_pair((int64_t)count, (int64_t)j));
        }
    }
}

uint64_t findSolution(Positions &elves, int64_t steps)
{
    std::vector<Pos> checker({ Pos(-1, -1), Pos(-1, 0), Pos(-1, 1), // North
                               Pos(1, -1), Pos(1, 0), Pos(1, 1),    // South
                               Pos(-1, -1), Pos(0, -1), Pos(1, -1), // West
                               Pos(-1, 1), Pos(0, 1), Pos(1, 1) }); // East
    size_t direction = 0;
    bool noLimit = steps == 0; // Part2 stop by `movements.empty`
    for (int64_t step = 0; step < steps || noLimit; step++) {
        std::multimap<Pos, Pos> movements; // To - From

        for (auto &&elf : elves) {
            Pos pos;

            // Check do nothing
            bool doNothing = true;
            for (auto &&check : checker) {
                pos.first = elf.first + check.first;
                pos.second = elf.second + check.second;
                if (elves.count(pos) > 0) {
                    doNothing = false;
                    break;
                }
            }
            if (doNothing) {
                continue;
            }

            // Check movement
            size_t curDirection = direction;
            for (int j = 0; j < 4; ++j) {
                bool isOk = true;
                for (int i = 0; i < 3; i++) {
                    const Pos &check = checker[curDirection + i];
                    pos.first = elf.first + check.first;
                    pos.second = elf.second + check.second;
                    if (elves.count(pos) > 0) {
                        isOk = false;
                        break;
                    }
                }
                if (isOk) {
                    const Pos &check = checker[curDirection + 1];
                    pos.first = elf.first + check.first;
                    pos.second = elf.second + check.second;
                    movements.emplace(std::make_pair(pos, elf));
                    break;
                }
                curDirection = (curDirection + 3) % 12;
            }
        }

        if (movements.empty()) {
            // Part 2 solution
            return step + 1;
        }
        // Move
        for (auto &&mov : movements) {
            if (movements.count(mov.first) > 1) {
                continue;
            }
            elves.erase(mov.second);
            elves.insert(mov.first);
        }
        direction = (direction + 3) % 12;
    }

    auto anElf = elves.begin();

    int64_t maxy = anElf->first;
    int64_t miny = anElf->first;
    int64_t maxx = anElf->second;
    int64_t minx = anElf->second;
    for (auto &&elf : elves) {
        if (elf.first > maxy) {
            maxy = elf.first;
        }
        if (elf.first < miny) {
            miny = elf.first;
        }
        if (elf.second < minx) {
            minx = elf.second;
        }
        if (elf.second > maxx) {
            maxx = elf.second;
        }
    }

    uint64_t bboxSize = (maxx - minx + 1) * (maxy - miny + 1);
    return bboxSize - elves.size();
}

std::string day23::process1(std::string file)
{
    Positions elves;
    parse::read_lineof<Positions *>(file, '\n', convertInput, &elves);
    auto res = findSolution(elves, 10);
    return std::to_string(res);
}

std::string day23::process2(std::string file)
{
    Positions elves;
    parse::read_lineof<Positions *>(file, '\n', convertInput, &elves);
    auto res = findSolution(elves, 0);
    return std::to_string(res);
}
