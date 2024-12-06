/**
 * @file    day06.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    06 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day06.h"

#include "common.h"

#include <unordered_set>

namespace
{
    typedef int16_t Indx;
    std::vector<std::pair<int, int>> DIRS = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
} // namespace

std::pair<Indx, Indx> getStart(const std::vector<std::string> &map)
{
    Indx n = map.size();
    Indx m = map[0].size();
    for (Indx i = 0; i < n; i++) {
        for (Indx j = 0; j < m; j++) {
            if (map[i][j] == '^') {
                return { i, j };
            }
        }
    }
    return { 0, 0 };
}

std::string day06::process1(std::string file)
{
    auto map = parse::read_all(file);
    int n = map.size();
    int m = map[0].size();
    auto [posi, posj] = getStart(map);

    // Navigate
    map[posi][posj] = '.';
    int64_t count = 0;
    int dir = 0;
    while (posi >= 0 && posi < n && posj >= 0 && posj < m) {
        switch (map[posi][posj]) {
            case '.':
                map[posi][posj] = 'X';
                count++;
                break;
            case '#':
                posi -= DIRS[dir].first;
                posj -= DIRS[dir].second;
                dir = (dir + 1) % 4;
                break;
            default:
                break;
        }
        posi += DIRS[dir].first;
        posj += DIRS[dir].second;
    }

    return std::to_string(count);
}

inline uint32_t Key(Indx i, Indx j, Indx d)
{
    return i * 256 * 4 + j * 4 + d;
}

bool isLoop(const std::vector<std::string> &map, Indx posi, Indx posj, Indx dir)
{
    std::unordered_set<uint32_t> visited;
    visited.reserve(6000);
    Indx n = map.size();
    Indx m = map[0].size();

    while (posi >= 0 && posi < n && posj >= 0 && posj < m) {
        if (map[posi][posj] == '#') {
            posi -= DIRS[dir].first;
            posj -= DIRS[dir].second;
            dir = (dir + 1) % 4;
        } else {
            if (visited.find(Key(posi, posj, dir)) != visited.end()) {
                return true;
            }
        }
        visited.insert(Key(posi, posj, dir));
        posi += DIRS[dir].first;
        posj += DIRS[dir].second;
    }

    return false;
}

std::string day06::process2(std::string file)
{
    auto map = parse::read_all(file);
    Indx n = map.size();
    Indx m = map[0].size();

    auto [posi, posj] = getStart(map);
    auto iposi = posi;
    auto iposj = posj;

    std::vector<std::pair<int, int>> dirs = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
    int dir = 0;

    std::set<std::pair<Indx, Indx>> valid;
    while (posi >= 0 && posi < n && posj >= 0 && posj < m) {
        if (map[posi][posj] == '#') {
            posi -= dirs[dir].first;
            posj -= dirs[dir].second;
            dir = (dir + 1) % 4;
        } else {
            valid.insert({ posi, posj });
        }
        posi += dirs[dir].first;
        posj += dirs[dir].second;
    }

    std::set<std::pair<Indx, Indx>> found;
    for (auto [i, j] : valid) {
        if (map[i][j] == '.') {
            map[i][j] = '#';
            if (isLoop(map, iposi, iposj, 0)) {
                found.insert({ i, j });
            }
            map[i][j] = '.';
        }
    }

    return std::to_string(found.size());
}