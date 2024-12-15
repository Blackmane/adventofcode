/**
 * @file    day14.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    14 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day14.h"

#include "common.h"

struct Robot {
    Robot(int a, int b, int c, int d) : px(a), py(b), vx(c), vy(d) {};
    int px = 0;
    int py = 0;
    int vx = 0;
    int vy = 0;
};

uint64_t moveRobots(std::vector<Robot> &robots, int steps, int wide, int tall)
{
    std::multiset<std::pair<int, int>> positions;
    for (auto robot : robots) {
        int x = (robot.px + robot.vx * steps) % wide;
        int y = (robot.py + robot.vy * steps) % tall;
        while (x < 0) {
            x += wide;
        }
        while (y < 0) {
            y += tall;
        }
        positions.insert({ x, y });
    }

    uint64_t tl = 0;
    uint64_t tr = 0;
    uint64_t bl = 0;
    uint64_t br = 0;

    int midT = tall / 2;
    int midW = wide / 2;
    for (auto pos : positions) {
        if (pos.first < midW && pos.second < midT) {
            tl++;
        } else if (pos.first > midW && pos.second < midT) {
            tr++;
        } else if (pos.first < midW && pos.second > midT) {
            bl++;
        } else if (pos.first > midW && pos.second > midT) {
            br++;
        } else {
        }
    }
    return tl * tr * bl * br;
}

std::vector<Robot> parseFile(std::string file, int64_t increment = 0)
{
    std::vector<Robot> robots;
    parse::read<std::vector<Robot> &>(
        file, '\n',
        [&](std::vector<Robot> &d, const std::string &line) {
            auto parts = parse::split(line, ' ');
            auto ps = parse::split(parts[0], ',');
            int px = stoi(ps[0].substr(2, ps[0].size() - 2));
            int py = stoi(ps[1]);
            auto vs = parse::split(parts[1], ',');
            int vx = stoi(vs[0].substr(2, vs[0].size() - 2));
            int vy = stoi(vs[1]);
            robots.emplace_back(px, py, vx, vy);
        },
        robots);

    return robots;
}

std::string day14::process1(std::string file, uint64_t steps, uint64_t wide, uint64_t tall)
{
    auto robots = parseFile(file);
    return std::to_string(moveRobots(robots, steps, wide, tall));
}

std::string day14::process2(std::string file)
{
    // I'm sorry! Done by "hand"
    return "0";
}