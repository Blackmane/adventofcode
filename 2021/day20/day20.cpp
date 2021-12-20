/**
 * @file    day20.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    20 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day20.h"

#include "common.h"

#include <set>

typedef std::pair<int64_t, int64_t> Pos;
typedef std::set<Pos> Positions;

struct FloorMap {
    std::string enhancement;
    Positions lightPixels;
    bool changed = false;
    int64_t lineCounter = 0;
};

void convertInput(FloorMap *floorMap, std::string line)
{
    if (line.empty()) {
        floorMap->changed = true;
        return;
    }
    if (!floorMap->changed) {
        floorMap->enhancement = line;
    } else {
        for (size_t j = 0, n = line.size(); j < n; j++) {
            if (line[j] == '#') {
                floorMap->lightPixels.insert(std::make_pair(floorMap->lineCounter, (int64_t)j));
            }
        }
        floorMap->lineCounter++;
    }
}

void addNearest(Positions *pixels, Pos pos)
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            pixels->insert(std::make_pair(pos.first + i - 1, pos.second + j - 1));
        }
    }
}

uint64_t getValue(Positions *pixels, Pos pos)
{
    uint64_t value = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            value *= 2;
            if (pixels->find(std::make_pair(pos.first + i - 1, pos.second + j - 1)) != pixels->end()) {
                value++;
            }
        }
    }
    return value;
}

uint64_t findSolution1(FloorMap *floorMap, int64_t n)
{
    int64_t minI = floorMap->lightPixels.begin()->first;
    int64_t maxI = floorMap->lightPixels.begin()->first;
    int64_t minJ = floorMap->lightPixels.begin()->second;
    int64_t maxJ = floorMap->lightPixels.begin()->second;
    for (auto p : floorMap->lightPixels) {
        if (p.first < minI) {
            minI = p.first;
        }
        if (p.first > maxI) {
            maxI = p.first;
        }
        if (p.second < minJ) {
            minJ = p.second;
        }
        if (p.second > maxJ) {
            maxJ = p.second;
        }
    }

    int64_t border = 10;
    for (int64_t step = 0; step < n; step++) {
        Positions newValues;
        for (int64_t i = minI - border; i <= maxI + border; ++i) {
            for (int64_t j = minJ - border; j <= maxJ + border; ++j) {
                if (floorMap->enhancement[getValue(&floorMap->lightPixels, std::make_pair(i, j))] == '#') {
                    newValues.insert(std::make_pair(i, j));
                    // print("(" << i << "," << j << ")")
                    //     floorMap->lightPixels.insert(p);
                    //     print("(" << p.first << "," << p.second << ")")
                    // } else {
                    //     auto it = floorMap->lightPixels.find(p);
                    //     if (it != floorMap->lightPixels.end()) {
                    //         floorMap->lightPixels.erase(it);
                    //     }
                }
            }
        }
        // println("")

        floorMap->lightPixels.clear();
        for (auto p : newValues) {
            floorMap->lightPixels.insert(p);
        }
    }

        //border--;
    uint64_t count = 0;
    for (auto &p : floorMap->lightPixels) {
        if (p.first > minI - border && p.first < maxI + border && p.second > minJ - border &&
            p.second < maxJ + border) {
            count++;
        }
    }

    return count;
}

std::string process1(std::string file)
{
    FloorMap floor;
    parse::read<FloorMap *>(file, '\n', convertInput, &floor);
    auto res = findSolution1(&floor, 2);
    return std::to_string(res);
    // 692 too low
    // 5686 too low
    // 5765
    // 5813 too high
}

std::string process2(std::string file)
{
    return "0";
}
