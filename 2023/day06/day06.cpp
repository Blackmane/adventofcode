/**
 * @file    day06.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    06 Dec 2023
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

uint64_t countWinning(uint64_t time, uint64_t recordDistance)
{
    uint64_t firstTime = 0;
    for (uint64_t timePressed = 0; timePressed <= time; timePressed++) {
        uint64_t distance = timePressed * (time - timePressed);

        if (distance > recordDistance) {
            firstTime = timePressed;
            break;
        }
    }
    return (time + 1) - 2 * (firstTime);
}

uint64_t countWinningBinarySearch(uint64_t time, uint64_t recordDistance)
{
    auto calcDistance = [time](uint64_t timePress) { return timePress * (time - timePress); };
    uint64_t firstTime = 0;

    uint64_t timePressedFrom = 0;
    uint64_t timePressedTo = time;
    while (firstTime == 0) {
        auto mid = (timePressedFrom + timePressedTo) / 2;

        if (calcDistance(mid) > recordDistance) {
            timePressedTo = mid;
        } else {
            if (calcDistance(mid + 1) > recordDistance) {
                // Found
                firstTime = mid + 1;
            } else {
                timePressedFrom = mid;
            }
        }
    }

    return (time + 1) - 2 * (firstTime);
}

std::string day06::process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);

    std::vector<uint64_t> times = parse::getIntegers(list[0]);
    std::vector<uint64_t> distance = parse::getIntegers(list[1]);

    uint64_t result = 1;
    for (int i = 0, n = times.size(); i < n; i++) {
        result *= countWinning(times[i], distance[i]);
    }

    return std::to_string(result);
}

std::string day06::process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);

    list[0].erase(std::remove_if(list[0].begin(), list[0].end(), isspace), list[0].end());
    list[1].erase(std::remove_if(list[1].begin(), list[1].end(), isspace), list[1].end());

    auto time = parse::getInteger(list[0]);
    auto distance = parse::getInteger(list[1]);

    return std::to_string(countWinningBinarySearch(time, distance));
}
