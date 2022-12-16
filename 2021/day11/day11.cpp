/**
 * @file    day11.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    11 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day11.h"

#include "common.h"

#include <deque>

constexpr size_t SIZE = 10;
typedef std::vector<std::array<int, SIZE>> OctopusMap;

void increaseAll(OctopusMap *omap)
{
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            omap->at(i)[j]++;
        }
    }
}

void increase(OctopusMap *omap, int i, int j, std::deque<std::pair<size_t, size_t>> *nexts)
{
    if (i < 0 || j < 0 || i >= (int)SIZE || j >= (int)SIZE) {
        return;
    }
    omap->at(i)[j]++;
    if (omap->at(i)[j] > 9) {
        nexts->push_back(std::make_pair(i, j));
    }
}

void increaseArea(OctopusMap *omap, int i, int j, std::deque<std::pair<size_t, size_t>> *nexts)
{
    increase(omap, ((int)i) - 1, ((int)j) - 1, nexts);
    increase(omap, ((int)i) - 1, ((int)j), nexts);
    increase(omap, ((int)i) - 1, ((int)j) + 1, nexts);
    increase(omap, ((int)i), ((int)j) - 1, nexts);
    increase(omap, ((int)i), ((int)j) + 1, nexts);
    increase(omap, ((int)i) + 1, ((int)j) - 1, nexts);
    increase(omap, ((int)i) + 1, ((int)j), nexts);
    increase(omap, ((int)i) + 1, ((int)j) + 1, nexts);
}

uint64_t flash(OctopusMap *omap)
{
    std::deque<std::pair<size_t, size_t>> nexts;
    std::vector<bool> flashed(SIZE * SIZE, false);
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (omap->at(i)[j] > 9) {
                increaseArea(omap, i, j, &nexts);
                flashed[i * SIZE + j] = true;
            }
        }
    }
    while (!nexts.empty()) {
        auto next = nexts.front();
        int i = next.first;
        int j = next.second;
        if (!flashed[i * SIZE + j] && omap->at(i)[j] > 9) {
            increaseArea(omap, i, j, &nexts);
            flashed[i * SIZE + j] = true;
        }
        nexts.pop_front();
    }
    uint64_t count = 0;
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (omap->at(i)[j] > 9) {
                omap->at(i)[j] = 0;
                count++;
            }
        }
    }
    return count;
}

uint64_t iterate(OctopusMap *omap, uint64_t n)
{
    uint64_t flashes = 0;
    for (uint64_t i = 0; i < n; ++i) {
        increaseAll(omap);
        flashes += flash(omap);
    }
    return flashes;
}

bool isSynchronized(OctopusMap *omap)
{
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (omap->at(i)[j] != 0) {
                return false;
            }
        }
    }
    return true;
}

uint64_t search(OctopusMap *omap)
{
    uint64_t iteractions = 0;
    while (!isSynchronized(omap)) {
        increaseAll(omap);
        flash(omap);
        iteractions++;
    }
    return iteractions;
}

void insert(OctopusMap *omap, std::string line)
{
    std::array<int, SIZE> values;
    for (size_t i = 0; i < SIZE; ++i) {
        values[i] = line[i] - '0';
    }
    omap->emplace_back(values);
}

std::string day11::process1(std::string file)
{
    OctopusMap omap;
    parse::read<OctopusMap *>(file, '\n', insert, &omap);
    return std::to_string(iterate(&omap, 100));
}

std::string day11::process2(std::string file)
{
    OctopusMap omap;
    parse::read<OctopusMap *>(file, '\n', insert, &omap);
    return std::to_string(search(&omap));
}
