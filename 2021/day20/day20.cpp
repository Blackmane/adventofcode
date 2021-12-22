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

uint64_t findSolution(FloorMap *floorMap, int64_t n)
{
    for (int64_t step = 1; step <= n; step++) {
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

        Positions newValues;
        for (int64_t i = minI - 1; i <= maxI + 1; ++i) {
            for (int64_t j = minJ - 1; j <= maxJ + 1; ++j) {
                size_t index = 0;
                for (int nearI = i - 1; nearI <= i + 1; nearI++) {
                    for (int nearJ = j - 1; nearJ <= j + 1; nearJ++) {
                        index *= 2;
                        bool isBorder = nearI < minI || nearI > maxI || nearJ < minJ || nearJ > maxJ;
                        if (isBorder && step % 2 == 0 && floorMap->enhancement[0] == '#') {
                            index++;
                        }
                        if (!isBorder &&
                            floorMap->lightPixels.find(std::make_pair(nearI, nearJ)) != floorMap->lightPixels.end()) {
                            index++;
                        }
                    }
                }
                if (floorMap->enhancement[index] == '#') {
                    newValues.insert(std::make_pair(i, j));
                }
            }
        }
        floorMap->lightPixels = newValues;
    }

    return floorMap->lightPixels.size();
}

std::string process1(std::string file)
{
    FloorMap floor;
    parse::read<FloorMap *>(file, '\n', convertInput, &floor);
    auto res = findSolution(&floor, 2);
    return std::to_string(res);
}

std::string process2(std::string file)
{
    FloorMap floor;
    parse::read<FloorMap *>(file, '\n', convertInput, &floor);
    auto res = findSolution(&floor, 50);
    return std::to_string(res);
}
