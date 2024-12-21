/**
 * @file    day21.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    21 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day21.h"

#include "common.h"

namespace
{
    typedef std::unordered_map<char, int> PadPos;

    const PadPos NumRowPos{ { '0', 3 }, { '1', 2 }, { '2', 2 }, { '3', 2 }, { '4', 1 }, { '5', 1 },
                            { '6', 1 }, { '7', 0 }, { '8', 0 }, { '9', 0 }, { 'A', 3 } };
    const PadPos NumColPos{ { '0', 1 }, { '1', 0 }, { '2', 1 }, { '3', 2 }, { '4', 0 }, { '5', 1 },
                            { '6', 2 }, { '7', 0 }, { '8', 1 }, { '9', 2 }, { 'A', 2 } };

    const PadPos DirectionalRowPos{ { '^', 0 }, { 'A', 0 }, { '<', 1 }, { 'v', 1 }, { '>', 1 } };
    const PadPos DirectionalColPos{ { '^', 1 }, { 'A', 2 }, { '<', 0 }, { 'v', 1 }, { '>', 2 } };

    std::map<std::pair<std::string, int>, uint64_t> CacheMin;
} // namespace

std::string getPart(int from, int to, char a, char b)
{
    int dir = to - from;
    if (dir > 0) {
        return std::string(dir, a);
    }
    if (dir < 0) {
        return std::string(-dir, b);
    }
    return {}; // d == 0
}

std::set<std::string> getPaths(const std::string line, const PadPos &rowPos, const PadPos &colPos, int i, int j,
                               int blank_i, int blank_j)
{
    std::set<std::string> paths;
    paths.insert("");
    for (auto c : line) {
        // The minimal path is combined pressing only two buttons
        // The one for the vertical movement, the other for horizontal movement
        int dest_i = rowPos.at(c);
        int dest_j = colPos.at(c);
        auto mov_i_vert = getPart(i, dest_i, 'v', '^');
        auto mov_j_hor = getPart(j, dest_j, '>', '<');
        std::set<std::string> newpaths;
        for (auto path : paths) {
            if ((i == blank_i || dest_i == blank_i) && (j == blank_j || dest_j == blank_j)) {
                if (i == blank_i && dest_j == blank_j) {
                    newpaths.insert(path + mov_i_vert + mov_j_hor + "A");
                }
                if (dest_i == blank_i && j == blank_j) {
                    newpaths.insert(path + mov_j_hor + mov_i_vert + "A");
                }
            } else {
                newpaths.insert(path + mov_i_vert + mov_j_hor + "A");
                newpaths.insert(path + mov_j_hor + mov_i_vert + "A");
            }
        }
        std::swap(paths, newpaths);
        i = dest_i;
        j = dest_j;
    }
    return paths;
}

uint64_t pressRobot(const std::string &line, int steps)
{
    if (steps == 0) {
        return line.size();
    }

    auto it = CacheMin.find({ line, steps });
    if (it != CacheMin.end()) {
        return it->second;
    }

    uint64_t count = 0;
    auto parts = parse::split(line, 'A');
    if (parts.size() > 1) {
        for (auto &part : parts) {
            count += pressRobot(part + "A", steps);
        }
    } else {
        count = UINT64_MAX;
        auto subPaths = getPaths(line, DirectionalRowPos, DirectionalColPos, 0, 2, 0, 0);
        for (auto &path : subPaths) {
            uint64_t s = pressRobot(path, steps - 1);
            if (s < count) {
                count = s;
            }
        }
    }

    CacheMin.insert({ { line, steps }, count });
    return count;
}

uint64_t pressNumeric(const std::string &line, int steps)
{
    std::set<std::string> paths = getPaths(line, NumRowPos, NumColPos, 3, 2, 3, 0);

    uint64_t minSize = UINT64_MAX;
    std::string minPath = "";
    for (auto &path : paths) {
        auto s = pressRobot(path, steps);
        if (s < minSize) {
            minSize = s;
            minPath = path;
        }
    }
    return minSize;
}

uint64_t resolve(std::string &file, int steps)
{
    auto list = parse::read_all(file);
    uint64_t count = 0;
    for (auto &line : list) {
        uint64_t num = std::stoi(line.substr(0, line.size() - 1));
        count += pressNumeric(line, steps) * num;
    }
    return count;
}

std::string day21::process1(std::string file)
{
    auto count = resolve(file, 2);
    return std::to_string(count);
}

std::string day21::process2(std::string file)
{
    auto count = resolve(file, 25);
    return std::to_string(count);
}
