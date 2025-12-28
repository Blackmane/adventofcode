/**
 * @file    day12.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day12.h"

#include "common.h"

struct Shape {
    Shape(const std::string &area)
    {
        for (char c : area) {
            if (c == '#') {
                count++;
            }
        }
    }
    int count = 0;
};

struct Region {
    int n = 0;
    int m = 0;
    std::vector<uint64_t> count;
    Region(std::string line)
    {
        auto parts = parse::split(line, ':');
        std::replace(parts[0].begin(), parts[0].end(), 'x', ' ');
        auto values = parse::getIntegers(parts[0]);
        n = values[0];
        m = values[1];
        count = parse::getIntegers(parts[1]);
    }
};

std::string day12::process1(std::string file)
{
    std::vector<Shape> shapes;
    std::vector<Region> regions;
    bool firstPart = true;
    std::string cur;

    parse::read(file, '\n', [&](const std::string &line) {
        if (line.empty()) {
            return;
        }
        if (firstPart) {
            if ('0' <= line[0] && line[0] <= '9') {
                if (line[1] == ':') {
                    if (!cur.empty()) {
                        shapes.emplace_back(cur);
                    }
                    cur = {};
                } else {
                    shapes.emplace_back(cur);

                    firstPart = false;
                    regions.emplace_back(line);
                }
            } else {
                cur.insert(cur.end(), line.begin(), line.end());
            }
        } else {
            regions.emplace_back(line);
        }
    });

    uint64_t count = 0;
    for (auto &region : regions) {
        uint64_t prod = region.n * region.m;
        uint64_t sum = 0;
        for (int i = 0, n = region.count.size(); i < n; i++) {
            sum += region.count[i] * shapes[i].count;
        }
        if (sum <= prod) {
            count++;
        }
    }
    return std::to_string(count);
}

std::string day12::process2(std::string file)
{
    return "0";
}