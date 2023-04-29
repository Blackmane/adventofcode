/**
 * @file    day17.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    17 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day17.h"

#include "common.h"

#include <unordered_set>

constexpr int64_t MAX_LEFT = 0;
constexpr int64_t MAX_RIGHT = 6;

//  Height * 8 + Wide
typedef int64_t Pos;

inline int64_t getPos(int64_t i, int64_t j)
{
    return i * 8 + j;
}

constexpr int64_t MAX_ROCK_ID = 5;

std::vector<std::vector<Pos>> ROCK_LIST = {
    // ####
    { 0, 1, 2, 3 },
    // .#.
    // ###
    // .#.
    { 1, 8, 9, 10, 17 },
    // ..#
    // ..#
    // ###
    { 0, 1, 2, 10, 18 },
    // #
    // #
    // #
    // #
    { 0, 8, 16, 24 },
    // ##
    // ##
    { 0, 1, 8, 9 }
};

std::vector<Pos> getRock(uint64_t number)
{
    auto id = number % MAX_ROCK_ID;
    return ROCK_LIST[id];
}

Pos moveRock(const std::unordered_set<Pos> &map, const std::vector<Pos> &rock, const Pos &from, int64_t dirH,
             int64_t dirW)
{
    int64_t i = (from >> 3) + dirH; // from / 8 + dirH;
    int64_t j = (from & 7) + dirW;  // from % 8 + dirW;
    if (j < MAX_LEFT || i < 0) {
        // Left or bottom border
        return from;
    }

    Pos newFrom = getPos(i, j);
    for (auto &&r : rock) {
        uint64_t rpos = r + newFrom;

        if ((rpos & 7) > MAX_RIGHT) { // rpos % 8 > MAX_RIGHT
            // Right border
            return from;
        }

        if (map.find(rpos) != map.end()) {
            // Collision, not permitted
            return from;
        }
    }
    return newFrom;
}

int64_t updateAndPrune(std::unordered_set<Pos> &map, int64_t maxHeight, std::vector<Pos> &rock, Pos from)
{
    int64_t fromHeight = maxHeight + 3;
    int64_t toHeight = 0;
    // Update map
    for (auto &&r : rock) {
        Pos rpos = from + r;
        map.insert(rpos);
        int64_t rockHeight = rpos / 8;
        maxHeight = std::max(rockHeight + 1, maxHeight);
        toHeight = std::max(rockHeight, toHeight);
        fromHeight = std::min(rockHeight, fromHeight);
    }
    // Prune
    for (int64_t i = toHeight; i >= fromHeight; i--) {
        bool lineIsFull = true;
        int64_t idxV = i * 8;
        for (auto k = MAX_LEFT; k <= MAX_RIGHT; k++) {
            if (map.find(idxV + k) == map.end()) {
                lineIsFull = false;
                break;
            }
        }
        if (lineIsFull) {
            for (auto it = map.begin(); it != map.end();) {
                if ((*it >> 3) < i) { // *it / 8 < i
                    it = map.erase(it);
                } else {
                    it++;
                }
            }
            break;
        }
    }
    // Update maxHeight
    return maxHeight;
}

int64_t run(const std::string &jets, uint64_t rocks)
{
    std::unordered_set<Pos> map;
    int64_t maxHeight = 0;
    int64_t calcHeight = 0;
    Pos from = 0;
    size_t j = 0;
    size_t nj = jets.size();
    std::vector<Pos> rock;

    std::vector<std::pair<uint64_t, uint64_t>> stackStatus;
    stackStatus.push_back(std::make_pair(0, 0));

    for (uint64_t rockIdx = 0; rockIdx < rocks; rockIdx++) {
        from = getPos(maxHeight + 3, 2);
        rock = getRock(rockIdx);

        bool isFalling = true;
        while (isFalling) {
            if (jets[j] == '<') {
                from = moveRock(map, rock, from, 0, -1);
            }
            if (jets[j] == '>') {
                from = moveRock(map, rock, from, 0, 1);
            }
            j = (j + 1) % nj;

            Pos newFrom = moveRock(map, rock, from, -1, 0);
            if (newFrom == from) {
                // Is blocked
                maxHeight = updateAndPrune(map, maxHeight, rock, from);
                isFalling = false;
            } else {
                from = newFrom;
            }
            // Check cycle
            if (j == 0) {
                for (auto &&status : stackStatus) {
                    if (status.first % MAX_ROCK_ID == rockIdx % MAX_ROCK_ID) {
                        int64_t remaningRocks = rocks - rockIdx;
                        int64_t cycleLen = rockIdx - status.first;
                        int64_t cycles = remaningRocks / cycleLen;
                        rockIdx += cycleLen * cycles;
                        calcHeight += (maxHeight - status.second) * cycles;
                    }
                }

                stackStatus.push_back(std::make_pair(rockIdx, maxHeight));
            }
        }
    }
    return calcHeight + maxHeight;
}

std::string day17::process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = run(list[0], 2022);
    return std::to_string(result);
}

std::string day17::process2(std::string file)
{
    // This solution doesn't work for test
    // it's a randomness that works for the input
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = run(list[0], 1000000000000);
    return std::to_string(result);
}