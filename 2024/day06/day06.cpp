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

std::pair<int, int> getStart(const std::vector<std::string> &map)
{
    int n = map.size();
    int m = map[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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
    std::vector<std::pair<int, int>> dirs = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
    int dir = 0;
    while (posi >= 0 && posi < n && posj >= 0 && posj < m) {
        switch (map[posi][posj]) {
            case '.':
                map[posi][posj] = 'X';
                count++;
                break;
            case '#':
                posi -= dirs[dir].first;
                posj -= dirs[dir].second;
                dir = (dir + 1) % 4;
                break;
            case 'X':
            default:
                break;
        }
        posi += dirs[dir].first;
        posj += dirs[dir].second;
    }

    return std::to_string(count);
}

bool isLoop(std::vector<std::string> map, int posi, int posj, int dir, std::unordered_map<int64_t, char> visited)
{
    auto insert = [&](int i, int j, char d) {
        int64_t key = i * 1024 + j % 1024;
        visited.insert(std::make_pair(key, d));
    };
    auto contain = [&](int i, int j, char d) -> bool {
        int64_t key = i * 1024 + j % 1024;
        auto range = visited.equal_range(key);
        for (auto it = range.first; it != range.second; it++) {
            if (it->second == d) {
                return true;
            }
        }
        return false;
    };

    int n = map.size();
    int m = map[0].size();
    std::vector<std::pair<int, int>> dirs = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
    std::string dirsC = "^>v<";

    while (posi >= 0 && posi < n && posj >= 0 && posj < m) {
        switch (map[posi][posj]) {
            case '.':
                map[posi][posj] = 'X';
                break;
            case '#':
                posi -= dirs[dir].first;
                posj -= dirs[dir].second;
                dir = (dir + 1) % 4;
                break;
            default:
                if (contain(posi, posj, dirsC[dir])) {
                    return true;
                }
                break;
        }
        insert(posi, posj, dirsC[dir]);
        posi += dirs[dir].first;
        posj += dirs[dir].second;
    }

    return false;
}

std::string day06::process2(std::string file)
{
    std::set<std::pair<int, int>> found;
    auto map = parse::read_all(file);
    int n = map.size();
    int m = map[0].size();

    auto [posi, posj] = getStart(map);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == '.') {
                map[i][j] = '#';
                if (isLoop(map, posi, posj, 0, {})) {
                    found.insert({ i, j });
                }
                map[i][j] = '.';
            }
        }
    }

    return std::to_string(found.size());
}