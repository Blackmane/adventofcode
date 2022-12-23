/**
 * @file    day14.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    14 Dec 2022
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

#include <unordered_set>

typedef std::set<std::pair<uint64_t, uint64_t>> Rocks;

void insert(Rocks *rocks, std::string line)
{
    std::vector<std::pair<uint64_t, uint64_t>> rock;
    auto parts = parse::split(line, ' ');
    for (auto &&part : parts) {
        if (part != "->") {
            auto pos = parse::split(part, ',');
            rock.push_back(std::make_pair(std::stoull(pos[0]), std::stoull(pos[1])));
        }
    }
    auto from = rock[0];
    rocks->insert(from);
    for (auto &&r : rock) {
        if (from.first == r.first) {
            auto pos = from;
            auto inc = op::normalizeDirection(r.second - pos.second);
            for (; pos.second != r.second; pos.second += inc) {
                rocks->insert(pos);
            }
            rocks->insert(pos);
        }
        if (from.second == r.second) {
            auto pos = from;
            auto inc = op::normalizeDirection(r.first - pos.first);
            for (; pos.first != r.first; pos.first += inc) {
                rocks->insert(pos);
            }
            rocks->insert(pos);
        }
        from = r;
    }
}

uint64_t flowSand(Rocks &rocks)
{
    uint64_t maxDeep = 0;
    for (auto &rock : rocks) {
        if (rock.second > maxDeep) {
            maxDeep = rock.second;
        }
    }

    uint64_t count = 0;

    std::pair<uint64_t, uint64_t> sand(500, 0);
    bool falling = true;
    while (falling) {
        falling = sand.second < maxDeep;

        std::pair<uint64_t, uint64_t> next(sand.first, sand.second + 1);
        if (rocks.find(next) == rocks.end()) {
            sand = next;
            continue;
        }
        next.first = sand.first - 1;
        next.second = sand.second + 1;
        if (rocks.find(next) == rocks.end()) {
            sand = next;
            continue;
        }
        next.first = sand.first + 1;
        next.second = sand.second + 1;
        if (rocks.find(next) == rocks.end()) {
            sand = next;
            continue;
        }
        rocks.insert(sand);
        count++;
        sand.first = 500;
        sand.second = 0;
    }

    return count;
}

uint64_t flowSand2(Rocks &rocks)
{
    uint64_t maxDeep = 0;
    for (auto &rock : rocks) {
        if (rock.second > maxDeep) {
            maxDeep = rock.second;
        }
    }
    maxDeep += 2;

    uint64_t count = 0;

    std::pair<uint64_t, uint64_t> sand(500, 0);
    bool falling = true;
    std::vector<std::pair<uint64_t, uint64_t>> nexts(3, std::make_pair(0, 0));
    while (falling) {
        std::pair<uint64_t, uint64_t> next(sand.first, sand.second + 1);
        if (rocks.find(next) == rocks.end() && next.second < maxDeep) {
            sand = next;
            continue;
        }
        next.first = sand.first - 1;
        next.second = sand.second + 1;
        if (rocks.find(next) == rocks.end() && next.second < maxDeep) {
            sand = next;
            continue;
        }
        next.first = sand.first + 1;
        next.second = sand.second + 1;
        if (rocks.find(next) == rocks.end() && next.second < maxDeep) {
            sand = next;
            continue;
        }
        rocks.insert(sand);
        count++;
        falling = !(sand.first == 500 && sand.second == 0);
        sand.first = 500;
        sand.second = 0;
    }

    return count;
}

std::string day14::process1(std::string file)
{
    Rocks rocks;
    parse::read<Rocks *>(file, '\n', &insert, &rocks);
    auto result = flowSand(rocks);
    return std::to_string(result);
}

std::string day14::process2(std::string file)
{
    Rocks rocks;
    parse::read<Rocks *>(file, '\n', &insert, &rocks);
    auto result = flowSand2(rocks);
    return std::to_string(result);
}
