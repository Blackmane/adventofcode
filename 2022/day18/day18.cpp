/**
 * @file    day18.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    18 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day18.h"

#include "common.h"

typedef std::pair<uint8_t, uint8_t> Pos;
typedef std::vector<std::set<Pos>> Droplets;

uint64_t countFaces(const Droplets &droplets)
{
    uint64_t count = 0;

    for (int i = 0, n = droplets.size(); i < n; ++i) {
        count += 6 * droplets[i].size();

        // Nearby
        for (auto &&droplet : droplets[i]) {
            Pos near = droplet;
            near.first = droplet.first + 1;
            if (droplets[i].find(near) != droplets[i].end()) {
                count -= 1;
            }
            near.first = droplet.first - 1;
            if (droplets[i].find(near) != droplets[i].end()) {
                count -= 1;
            }
            near.first = droplet.first;
            near.second = droplet.second + 1;
            if (droplets[i].find(near) != droplets[i].end()) {
                count -= 1;
            }
            near.second = droplet.second - 1;
            if (droplets[i].find(near) != droplets[i].end()) {
                count -= 1;
            }
        }

        // Under
        if (i > 0) {
            for (auto &&droplet : droplets[i]) {
                if (droplets[i - 1].find(droplet) != droplets[i - 1].end()) {
                    // Exists under
                    count -= 2;
                }
            }
        }
    }

    return count;
}

const uint8_t IS_INT_AIR = 1;
const uint8_t IS_DROPLET = 2;
const uint8_t IS_EXT_AIR = 3;

Droplets getAirPockets(const Droplets &droplets)
{
    size_t maxZ = droplets.size() - 1;
    uint8_t maxX = 0;
    uint8_t maxY = 0;
    for (auto &&droplet : droplets) {
        for (auto &&pos : droplet) {
            if (pos.first > maxX) {
                maxX = pos.first;
            }
            if (pos.second > maxY) {
                maxY = pos.second;
            }
        }
    }

    Droplets internalAir;
    for (size_t i = 0; i < maxZ + 1; ++i) {
        std::set<Pos> empty;
        internalAir.push_back(empty);
    }

    std::vector<std::vector<std::vector<uint8_t>>> cube;
    for (size_t z = 0; z <= maxZ; z++) {
        std::vector<std::vector<uint8_t>> emptyZ;
        cube.push_back(emptyZ);
        for (uint8_t x = 0; x <= maxX; x++) {
            std::vector<uint8_t> emptyX;
            cube[z].push_back(emptyX);
            for (uint8_t y = 0; y <= maxY; y++) {
                cube[z][x].push_back(0);
                if (z == 0 || z == maxZ || x == 0 || x == maxX || y == 0 || y == maxY) {
                    cube[z][x][y] = IS_EXT_AIR;
                }
            }
        }
    }
    for (size_t z = 0; z <= maxZ; z++) {
        for (auto &&pos : droplets[z]) {
            // Droplets
            cube[z][pos.first][pos.second] = IS_DROPLET;
        }
    }

    Pos pos;
    for (size_t z = 0; z <= maxZ; z++) {
        for (uint8_t x = 0; x <= maxX; x++) {
            for (uint8_t y = 0; y <= maxY; y++) {
                if (cube[z][x][y] != 0) {
                    // Already calculated
                    continue;
                }
                bool ext_air = cube[z + 1][x][y] == IS_EXT_AIR || cube[z - 1][x][y] == IS_EXT_AIR ||
                               cube[z][x + 1][y] == IS_EXT_AIR || cube[z][x - 1][y] == IS_EXT_AIR ||
                               cube[z][x][y + 1] == IS_EXT_AIR || cube[z][x][y - 1] == IS_EXT_AIR;
                if (ext_air) {
                    cube[z][x][y] = IS_EXT_AIR;
                } else {
                    pos.first = x;
                    pos.second = y;
                    internalAir[z].insert(pos);
                }
            }
        }
    }

    bool almostOne = true;
    while (almostOne) {
        almostOne = false;
        for (size_t z = 0; z <= maxZ; z++) {
            for (auto it = internalAir[z].begin(); it != internalAir[z].end();) {
                uint8_t x = it->first;
                uint8_t y = it->second;
                bool ext_air = cube[z + 1][x][y] == IS_EXT_AIR || cube[z - 1][x][y] == IS_EXT_AIR ||
                               cube[z][x + 1][y] == IS_EXT_AIR || cube[z][x - 1][y] == IS_EXT_AIR ||
                               cube[z][x][y + 1] == IS_EXT_AIR || cube[z][x][y - 1] == IS_EXT_AIR;
                if (ext_air) {
                    auto eresable = it;
                    it++;
                    internalAir[z].erase(eresable);
                    cube[z][x][y] = IS_EXT_AIR;
                    // Propagate
                    almostOne = true;
                } else {
                    it++;
                }
            }
        }
    }

    return internalAir;
}

void insert(Droplets *lines, std::string line)
{
    auto parts = parse::split(line, ',');
    uint8_t value = std::stoi(parts[0]);
    for (int i = lines->size(); i < value + 1; ++i) {
        std::set<Pos> empty;
        lines->push_back(empty);
    }
    Pos pos(std::stoi(parts[1]), std::stoi(parts[2]));
    lines->at(value).insert(pos);
}

std::string day18::process1(std::string file)
{
    Droplets lines;
    parse::read<Droplets *>(file, '\n', &insert, &lines);
    auto result = countFaces(lines);
    return std::to_string(result);
}

std::string day18::process2(std::string file)
{
    Droplets droplets;
    parse::read<Droplets *>(file, '\n', &insert, &droplets);
    auto lavaFaces = countFaces(droplets);
    auto air = getAirPockets(droplets);
    auto airFaces = countFaces(air);
    return std::to_string(lavaFaces - airFaces);
}