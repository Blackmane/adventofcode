/**
 * @file    day13.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    13 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day13.h"

#include "common.h"

#include <cmath>

struct Data {
    int64_t ax = 0;
    int64_t ay = 0;
    int64_t bx = 0;
    int64_t by = 0;
    int64_t px = 0;
    int64_t py = 0;
};

uint64_t minTokens(std::vector<Data> &datas)
{
    uint64_t sumMinTokens = 0;
    for (auto &data : datas) {
        uint64_t minTokens = 0;
        for (int i = 0; i < 100; i++) {
            uint64_t jx = (data.px - (i * data.ax)) / data.bx;
            uint64_t jy = (data.py - (i * data.ay)) / data.by;
            if (jx != jy) {
                continue;
            }
            int64_t eqx = (i * data.ax) + (jx * data.bx);
            int64_t eqy = (i * data.ay) + (jy * data.by);
            if (eqx == data.px && eqy == data.py) {
                uint64_t tokens = 3 * i + jx;
                if (minTokens == 0 || minTokens < tokens) {
                    minTokens = tokens;
                }
            }
        }
        sumMinTokens += minTokens;
    }
    return sumMinTokens;
}

uint64_t minTokens2(std::vector<Data> &datas)
{
    uint64_t sumMinTokens = 0;
    for (auto &data : datas) {
        uint64_t minTokens = 0;
        double d = data.ax * data.by - data.ay * data.bx;
        int64_t a = (data.px * data.by - data.py * data.bx) / d;
        int64_t b = (data.py * data.ax - data.px * data.ay) / d;
        int64_t eqx = (a * data.ax) + (b * data.bx);
        int64_t eqy = (a * data.ay) + (b * data.by);
        if (eqx == data.px && eqy == data.py) {
            minTokens = 3 * a + b;
        }
        sumMinTokens += minTokens;
    }
    return sumMinTokens;
}

std::vector<Data> parseFile(std::string file, int64_t increment = 0)
{
    std::vector<Data> datas;
    const uint64_t xABpos = std::string{ "Button A: X+" }.length();
    const uint64_t yABpos = std::string{ " Y+" }.length();
    const uint64_t xPpos = std::string{ "Prize: X=" }.length();
    const uint64_t yPpos = std::string{ " Y=" }.length();
    int lineId = 0;
    parse::read<std::vector<Data> &>(
        file, '\n',
        [&](std::vector<Data> &d, const std::string &line) {
            if (lineId != 3) {
                auto parts = parse::split(line, ',');
                int xpos = xABpos;
                int ypos = yABpos;
                if (lineId == 2) {
                    xpos = xPpos;
                    ypos = yPpos;
                }
                int x = stoi(parts[0].substr(xpos, parts[0].length() - xPpos));
                int y = stoi(parts[1].substr(ypos, parts[1].length() - yPpos));
                switch (lineId) {
                    case 0:
                        d.push_back({});
                        d.back().ax = x;
                        d.back().ay = y;
                        break;
                    case 1:
                        d.back().bx = x;
                        d.back().by = y;
                        break;
                    case 2:
                        d.back().px = x + increment;
                        d.back().py = y + increment;
                        break;
                    default:
                        break;
                }
            }
            lineId = (lineId + 1) % 4;
        },
        datas);

    return datas;
}

std::string day13::process1(std::string file)
{
    auto datas = parseFile(file);
    return std::to_string(minTokens(datas));
}

std::string day13::process2(std::string file)
{
    auto datas = parseFile(file, 10000000000000);
    return std::to_string(minTokens2(datas));
}