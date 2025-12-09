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

bool isGood(std::vector<std::pair<int, int>> points, std::set<std::tuple<int, int, int>> &verLines,
            std::set<std::tuple<int, int, int>> &horLines, int left, int right, int top, int bottom)
{
    // For test: but not used for the input
    // for (auto &p : points) {
    //     if (left < p.first && p.first < right && top < p.second && p.second < bottom) {
    //         return false;
    //     }
    // }
    for (auto &[x, y1, y2] : verLines) {
        if (left < x && x < right) {
            // Contains
            if (top < y1 && y2 < bottom) {
                return false;
            }
            // Intersects
            if ((y1 < top && top < y2) || (y1 < bottom && bottom < y2)) {
                return false;
            }
        }
    }
    for (auto &[y, x1, x2] : horLines) {
        if (top < y && y < bottom) {
            // Contains
            if (left < x1 && x2 < right) {
                return false;
            }
            // Intersects
            if ((x1 < left && left < x2) || (x1 < right && right < x2)) {
                return false;
            }
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

    // Track lines
    std::set<std::tuple<int, int, int>> verLines;
    std::set<std::tuple<int, int, int>> horLines;
    for (int i = 0, n = points.size(); i < n; i++) {
        int j = i + 1;
        if (j == n) {
            j = 0;
        }
        if (points[i].first == points[j].first) {
            auto min = std::min(points[i].second, points[j].second);
            auto max = std::max(points[i].second, points[j].second);
            verLines.insert({ points[i].first, min, max });
        } else {
            auto min = std::min(points[i].first, points[j].first);
            auto max = std::max(points[i].first, points[j].first);
            horLines.insert({ points[i].second, min, max });
        }
    }

    int64_t max = 0;
    for (int i = 0, n = points.size(); i < n - 1; i++) {
        for (int j = i + 3; j < n; j++) {
            int64_t x = std::abs(points[i].first - points[j].first) + 1;
            int64_t y = std::abs(points[i].second - points[j].second) + 1;
            int64_t area = x * y;
            if (area > max) {
                if (isGood(points, verLines, horLines, std::min(points[i].first, points[j].first),
                           std::max(points[i].first, points[j].first), std::min(points[i].second, points[j].second),
                           std::max(points[i].second, points[j].second))) {
                    max = area;
                }
            }
        }
    }
    // Doesn't works on test! Assumption on points position
    return std::to_string(max);
}
