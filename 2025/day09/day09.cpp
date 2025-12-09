/**
 * @file    day09.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    09 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day09.h"

#include "common.h"

std::string day09::process1(std::string file)
{
    std::vector<std::pair<int, int>> points;
    parse::read(file, '\n', [&](const std::string &line) {
        auto parts = parse::split(line, ',');
        points.push_back({ std::stoul(parts[0]), std::stoul(parts[1]) });
    });

    int64_t max = 0;
    for (int i = 0, n = points.size(); i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int64_t x = std::abs(points[i].first - points[j].first) + 1;
            int64_t y = std::abs(points[i].second - points[j].second) + 1;
            int64_t area = x * y;
            if (area > max) {
                max = area;
            }
        }
    }

    return std::to_string(max);
}

bool isGood(const std::vector<std::vector<bool>> &map, int left, int right, int top, int bottom)
{
    for (int i = left; i <= right; i++) {
        if (!map[i][top]) {
            return false;
        }
        if (!map[i][bottom]) {
            return false;
        }
    }
    for (int j = top; j <= bottom; j++) {
        if (!map[left][j]) {
            return false;
        }
        if (!map[right][j]) {
            return false;
        }
    }

    return true;
}

std::string day09::process2(std::string file)
{
    uint64_t maxX = 0;
    uint64_t maxY = 0;
    std::vector<std::pair<int, int>> points;
    parse::read(file, '\n', [&](const std::string &line) {
        auto parts = parse::split(line, ',');
        auto x = std::stoul(parts[0]);
        auto y = std::stoul(parts[1]);
        points.push_back({ x, y });
        maxX = std::max(x, maxX);
        maxY = std::max(y, maxY);
    });

    std::vector<bool> line(maxY + 1, false);
    std::vector<std::vector<bool>> map(maxX + 1, line);
    // Init without right borders
    for (int i = 0, n = points.size(); i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (points[i].first == points[j].first) {
                auto min = std::min(points[i].second, points[j].second);
                auto max = std::max(points[i].second, points[j].second);
                for (int y = min; y < max; y++) {
                    map[points[i].first][y] = true;
                }
            }
        }
    }

    // Fill
    line = map[0];
    for (uint64_t x = 1; x <= maxX; x++) {
        for (uint64_t y = 0; y <= maxY; y++) {
            auto cur = map[x][y];
            map[x][y] = line[y] != cur;
        }
        line = map[x];
    }
    // Add borders
    for (int i = 0, n = points.size(); i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (points[i].first == points[j].first) {
                auto min = std::min(points[i].second, points[j].second);
                auto max = std::max(points[i].second, points[j].second);
                for (int y = min; y < max; y++) {
                    map[points[i].first][y] = true;
                }
            } else {
                auto min = std::min(points[i].first, points[j].first);
                auto max = std::max(points[i].first, points[j].first);
                for (int x = min; x <= max; x++) {
                    map[x][points[i].second] = true;
                }
            }
        }
    }

    int64_t max = 0;
    for (int i = 0, n = points.size(); i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) { // +2
            int64_t x = std::abs(points[i].first - points[j].first) + 1;
            int64_t y = std::abs(points[i].second - points[j].second) + 1;
            int64_t area = x * y;
            if (area > max) {
                if (isGood(map, std::min(points[i].first, points[j].first), std::max(points[i].first, points[j].first),
                           std::min(points[i].second, points[j].second),
                           std::max(points[i].second, points[j].second))) {
                    max = area;
                }
            }
        }
    }

    return std::to_string(max);
}
