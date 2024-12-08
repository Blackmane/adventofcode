/**
 * @file    day08.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    08 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day08.h"

#include "common.h"

std::pair<std::pair<int, int>, std::pair<int, int>> tracking(std::pair<int, int> a, std::pair<int, int> b)
{
    int x = b.first - a.first;
    int y = b.second - a.second;

    return { { a.first - x, a.second - y }, { b.first + x, b.second + y } };
}

std::vector<std::pair<int, int>> trackingLine(std::pair<int, int> a, std::pair<int, int> b, int n, int m)
{
    std::vector<std::pair<int, int>> result;
    int x = b.first - a.first;
    int y = b.second - a.second;

    while (a.first >= 0 && a.first < n && a.second >= 0 && a.second < m) {
        result.push_back(a);
        a.first -= x;
        a.second -= y;
    }
    while (b.first >= 0 && b.first < n && b.second >= 0 && b.second < m) {
        result.push_back(b);
        b.first += x;
        b.second += y;
    }

    return result;
}

std::map<char, std::vector<std::pair<int, int>>> readAntennas(const std::vector<std::string> &map, int n, int m)
{
    std::map<char, std::vector<std::pair<int, int>>> antennas;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = map[i][j];
            if (c != '.') {
                auto it = antennas.find(c);
                if (it == antennas.end()) {
                    antennas.insert({ c, { { i, j } } });
                } else {
                    it->second.push_back({ i, j });
                }
            }
        }
    }
    return antennas;
}

std::string day08::process1(std::string file)
{
    auto map = parse::read_all(file);
    int n = map.size();
    int m = map[0].size();

    std::map<char, std::vector<std::pair<int, int>>> antennas = readAntennas(map, n, m);

    std::set<std::pair<int, int>> unique;
    for (auto &&positions : antennas) {
        for (size_t i = 0, np = positions.second.size(); i < np - 1; i++) {
            for (size_t j = i + 1; j < np; j++) {
                auto [a, b] = tracking(positions.second[i], positions.second[j]);
                if (a.first >= 0 && a.first < n && a.second >= 0 && a.second < m)
                    unique.insert(a);
                if (b.first >= 0 && b.first < n && b.second >= 0 && b.second < m)
                    unique.insert(b);
            }
        }
    }

    return std::to_string(unique.size());
}

std::string day08::process2(std::string file)
{
    auto map = parse::read_all(file);
    int n = map.size();
    int m = map[0].size();

    std::map<char, std::vector<std::pair<int, int>>> antennas = readAntennas(map, n, m);

    std::set<std::pair<int, int>> unique;
    for (auto &&positions : antennas) {
        for (size_t i = 0, np = positions.second.size(); i < np - 1; i++) {
            for (size_t j = i + 1; j < np; j++) {
                auto pos = trackingLine(positions.second[i], positions.second[j], n, m);
                for (auto p : pos)
                    unique.insert(p);
            }
        }
    }

    return std::to_string(unique.size());
}