/**
 * @file    day17.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    17 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day17.h"

#include "common.h"

struct TargetArea {
    int64_t xMin;
    int64_t xMax;
    int64_t yMin;
    int64_t yMax;
    bool isInside(int64_t x, int64_t y)
    {
        return xMin <= x && x <= xMax && yMin <= y && y <= yMax;
    }
    bool beOver(int64_t x, int64_t y)
    {
        return y < yMin || x > xMax;
    }
};

struct Probe {
    int64_t x = 0;
    int64_t y = 0;
    int64_t velX;
    int64_t velY;
    Probe(int64_t vx, int64_t vy) : velX(vx), velY(vy) {}
    void move()
    {
        x += velX;
        y += velY;
        if (velX != 0) {
            velX = velX < 0 ? velX + 1 : velX - 1;
        }
        velY--;
    }
};

void convertLine(TargetArea *area, std::string line)
{
    auto values = parse::split(line, '=');
    auto dotPos = values[1].find('.');
    area->xMin = std::stoll(values[1].substr(0, dotPos));
    area->xMax = std::stoll(values[1].substr(dotPos + 2, values[1].find(',')));

    dotPos = values[2].find('.');
    area->yMin = std::stoll(values[2].substr(0, dotPos));
    area->yMax = std::stoll(values[2].substr(dotPos + 2, values[2].size() - 1));
}

int64_t track(int64_t velX, int64_t velY, TargetArea *area)
{
    int64_t max = 0;
    bool reach = false;
    Probe probe(velX, velY);
    while (!area->beOver(probe.x, probe.y) && !reach) {
        probe.move();
        if (probe.y > max) {
            max = probe.y;
        }
        reach = area->isInside(probe.x, probe.y);
    }
    return reach ? max : 0;
}

int64_t findSolution1(TargetArea *area)
{
    int64_t maxHeight = 0;
    for (int64_t velX = 0; velX <= area->xMax + 1; velX++) {
        for (int64_t velY = 0; velY <= velX; velY++) {
            auto max = track(velX - velY, velY, area);
            if (max > maxHeight) {
                maxHeight = max;
            }
        }
    }
    return maxHeight;
}

int64_t reachable(int64_t velX, int64_t velY, TargetArea *area)
{
    bool reach = false;
    Probe probe(velX, velY);
    while (!area->beOver(probe.x, probe.y) && !reach) {
        probe.move();
        reach = area->isInside(probe.x, probe.y);
    }
    return reach;
}

int64_t findSolution2(TargetArea *area)
{
    int64_t count = 0;

    int64_t bound =
        std::max(std::abs(area->xMax), std::abs(area->xMin)) + std::max(std::abs(area->yMax), std::abs(area->yMin));
    for (int64_t velX = 0; velX <= bound; velX++) {
        for (int64_t velY = 0; velY <= velX; velY++) {
            if (reachable(velX - velY, velY, area)) {
                count++;
            }
            if (velY != 0 && reachable(velX - velY, -1 * velY, area)) {
                count++;
            }
        }
    }
    return count;
}

std::string process1(std::string file)
{
    TargetArea area;
    parse::read<TargetArea *>(file, '\n', convertLine, &area);
    auto res = findSolution1(&area);
    return std::to_string(res);
}

std::string process2(std::string file)
{
    TargetArea area;
    parse::read<TargetArea *>(file, '\n', convertLine, &area);
    auto res = findSolution2(&area);
    return std::to_string(res);
}
