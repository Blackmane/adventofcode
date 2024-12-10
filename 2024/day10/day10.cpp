/**
 * @file    day10.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    10 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day10.h"

#include "common.h"

struct Path {
    Path(int ni, int nj) : i(ni), j(nj), starti(i), startj(j) {}
    Path(int ni, int nj, int si, int sj) : i(ni), j(nj), starti(si), startj(sj) {}
    int i = 0;
    int j = 0;

    int starti = 0;
    int startj = 0;
};

void hiking(std::string file, std::function<void(Path &)> condition)
{
    auto map = parse::read_all(file);
    int n = map.size();
    int m = map[0].size();
    std::vector<Path> paths;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == '0') {
                paths.push_back({ i, j });
            }
        }
    }

    while (!paths.empty()) {
        auto path = paths.back();
        paths.pop_back();
        char cur = map[path.i][path.j];
        if (cur == '9') {
            condition(path);
        }

        for (auto &&near : matrix::neighbours4(path.i, path.j, n, m)) {
            if (map[near.first][near.second] == cur + 1) {
                paths.push_back({ int(near.first), int(near.second), path.starti, path.startj });
            }
        }
    }
}

std::string day10::process1(std::string file)
{
    std::set<std::tuple<int, int, int, int>> trailheadPaths;
    hiking(file, [&](Path &path) { trailheadPaths.insert({ path.starti, path.startj, path.i, path.j }); });
    return std::to_string(trailheadPaths.size());
}

std::string day10::process2(std::string file)
{
    uint64_t count = 0;
    hiking(file, [&](Path &path) { count++; });
    return std::to_string(count);
}