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

constexpr int8_t MAX_LEFT = 0;
constexpr int8_t MAX_RIGHT = 6;

// Height, Wide
typedef std::pair<int64_t, int8_t> Pos;

std::vector<Pos> getRock(uint64_t number)
{
    Pos from(0, 0);
    std::vector<Pos> result;
    result.reserve(5);
    auto id = number % 5;
    switch (id) {
        case 0:
            // ####
            result.push_back(from);
            from.second++;
            result.push_back(from);
            from.second++;
            result.push_back(from);
            from.second++;
            result.push_back(from);
            break;
        case 1:
            // .#.
            // ###
            // .#.
            from.second++;
            result.push_back(from);
            from.first++;
            result.push_back(from);
            from.first++;
            result.push_back(from);
            from.first--;
            from.second--;
            result.push_back(from);
            from.second += 2;
            result.push_back(from);
            break;
        case 2:
            // ..#
            // ..#
            // ###
            result.push_back(from);
            from.second++;
            result.push_back(from);
            from.second++;
            result.push_back(from);
            from.first++;
            result.push_back(from);
            from.first++;
            result.push_back(from);
            break;
        case 3:
            // #
            // #
            // #
            // #
            result.push_back(from);
            from.first++;
            result.push_back(from);
            from.first++;
            result.push_back(from);
            from.first++;
            result.push_back(from);
            break;
        case 4:
            // ##
            // ##
            result.push_back(from);
            from.second++;
            result.push_back(from);
            from.first++;
            result.push_back(from);
            from.second--;
            result.push_back(from);
            break;
        default:
            break;
    }
    return result;
}

bool isBlocked(const std::set<Pos> &map, const std::vector<Pos> &rock, const Pos &from)
{
    if (from.first == 0) {
        return true;
    }
    for (auto &&r : rock) {
        Pos rpos(r.first + from.first - 1, r.second + from.second);
        if (map.find(rpos) != map.end()) {
            // Collision, so blocked
            return true;
        }
    }
    return false;
}

Pos moveRock(const std::set<Pos> &map, const std::vector<Pos> &rock, const Pos &from, const Pos &dir)
{
    if (from.second + dir.second < MAX_LEFT || from.first + dir.first < 0) {
        // Left or bottom border
        return from;
    }

    Pos newFrom(from.first + dir.first, from.second + dir.second);
    Pos rpos;
    for (auto &&r : rock) {
        rpos.first = r.first + newFrom.first;
        rpos.second = r.second + newFrom.second;

        if (rpos.second > MAX_RIGHT) {
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


int64_t run(const std::string &jets, uint64_t rocks)
{
    std::set<Pos> map;
    int64_t maxHeight = 0;
    Pos from(0, 0);
    size_t j = 0;
    size_t nj = jets.size();

    for (uint64_t rockIdx = 0; rockIdx < rocks; rockIdx++) {
        from.second = 2;
        from.first = maxHeight + 3;
        auto rock = getRock(rockIdx);

        bool isFalling = true;
        while (isFalling) {
            if (jets[j] == '<') {
                from = moveRock(map, rock, from, std::make_pair(0, -1));
            }
            if (jets[j] == '>') {
                from = moveRock(map, rock, from, std::make_pair(0, 1));
            }
            j = (j + 1) % nj;

            auto newFrom = moveRock(map, rock, from, std::make_pair(-1, 0));
            if (newFrom.first == from.first) {
                int64_t fromHeight = maxHeight + 3;
                int64_t toHeight = 0;
                for (auto &&r : rock) {
                    Pos rpos(r.first + from.first, r.second + from.second);
                    map.insert(rpos);
                    if (rpos.first + 1 > maxHeight) {
                        maxHeight = rpos.first + 1;
                    }
                    if (rpos.first > toHeight) {
                        toHeight = rpos.first;
                    }
                    if (rpos.first < fromHeight) {
                        fromHeight = rpos.first;
                    }
                }
                for (int64_t i = toHeight; i >= fromHeight; i--) {
                    bool all = true;
                    for (auto k = MAX_LEFT; k <= MAX_RIGHT; k++) {
                        if (map.find(std::make_pair(i, k)) == map.end()) {
                            all = false;
                            break;
                        }
                    }
                    if (all) {
                        for (auto it = map.begin(); it != map.end();) {
                            if (it->first < i) {
                                auto eresable = it;
                                it++;
                                map.erase(eresable);
                            } else {
                                it++;
                            }
                        }
                    }
                }
                isFalling = false;
            } else {
                from = newFrom;
            }
        }
    }
    return maxHeight;
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

    return "0";
}