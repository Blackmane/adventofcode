/**
 * @file    day25.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    25 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day25.h"
#include "common.h"

uint64_t findSolution(std::vector<std::string> *map)
{
    uint64_t count = 1;
    size_t vlen = map->size();
    size_t hlen = map->at(0).size();
    bool move = true;
    while (move) {
        move = false;
        // Move east
        std::set<std::pair<size_t, size_t>> moveableEast;
        for (size_t i = 0; i < vlen; ++i) {
            for (size_t j = 0; j < hlen; ++j) {
                if (map->at(i)[j] == '>' && map->at(i)[(j + 1) % hlen] == '.') {
                    moveableEast.insert(std::make_pair(i, j));
                }
            }
        }
        for (auto &p : moveableEast) {
            map->at(p.first)[p.second] = '.';
            map->at(p.first)[(p.second + 1) % hlen] = '>';
            move = true;
        }

        // Move south
        std::set<std::pair<size_t, size_t>> moveableSouth;
        for (size_t j = 0; j < hlen; ++j) {
            for (size_t i = 0; i < vlen; ++i) {
                if (map->at(i)[j] == 'v' && map->at((i + 1) % vlen)[j] == '.') {
                    moveableSouth.insert(std::make_pair(i, j));
                }
            }
        }
        for (auto &p : moveableSouth) {
            map->at(p.first)[p.second] = '.';
            map->at((p.first + 1) % vlen)[p.second] = 'v';
            move = true;
        }
        if (move) {
            count++;
        }
    }
    return count;
}

std::string day25::process1(std::string file)
{
    std::vector<std::string> map;
    parse::read_all(file, &map);
    auto res = findSolution(&map);
    return std::to_string(res);
}

std::string day25::process2(std::string file)
{
    return "0";
}
