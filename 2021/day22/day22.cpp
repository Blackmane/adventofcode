/**
 * @file    day22.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    22 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day22.h"

#include "common.h"

struct Cube {
    int64_t min_x;
    int64_t max_x;
    int64_t min_y;
    int64_t max_y;
    int64_t min_z;
    int64_t max_z;
    bool add;

    Cube intersect(Cube& c) {
        Cube result;
        result.add = !c.add;
        result.min_x = std::max(min_x, c.min_x);
        result.max_x = std::min(max_x, c.max_x);
        result.min_y = std::max(min_y, c.min_y);
        result.max_y = std::min(max_y, c.max_y);
        result.min_z = std::max(min_z, c.min_z);
        result.max_z = std::min(max_z, c.max_z);
        return result;
    }

    bool isEmpty() {
        return min_x > max_x || min_y > max_y || min_z > max_z;
    }

    uint64_t cardinality () {
        return (max_x - min_x + 1) * (max_y - min_y + 1) * (max_z - min_z + 1);
    }
};

void convertLine1(std::vector<Cube> *cubes, std::string line)
{
    Cube cube;
    auto parts = parse::split(line, '=');
    cube.add = parts[0][1] == 'n';
    cube.min_x = std::stoll(parts[1].substr(0, parts[1].find('.')));
    cube.max_x = std::stoll(parts[1].substr(parts[1].find('.') + 2, parts[1].find(',')));
    cube.min_y = std::stoll(parts[2].substr(0, parts[2].find('.')));
    cube.max_y = std::stoll(parts[2].substr(parts[2].find('.') + 2, parts[2].find(',')));
    cube.min_z = std::stoll(parts[3].substr(0, parts[3].find('.')));
    cube.max_z = std::stoll(parts[3].substr(parts[3].find('.') + 2, parts[3].size()));

    if (cube.min_x >= -50 && cube.min_x <= 50 && cube.min_y >= -50 && cube.min_y <= 50 && cube.min_z >= -50 &&
        cube.min_z <= 50 && cube.max_x >= -50 && cube.max_x <= 50 && cube.max_y >= -50 && cube.max_y <= 50 &&
        cube.max_z >= -50 && cube.max_z <= 50) {
        cubes->push_back(cube);
    }
}

void convertLine2(std::vector<Cube> *cubes, std::string line)
{
    Cube cube;
    auto parts = parse::split(line, '=');
    cube.add = parts[0][1] == 'n';
    cube.min_x = std::stoll(parts[1].substr(0, parts[1].find('.')));
    cube.max_x = std::stoll(parts[1].substr(parts[1].find('.') + 2, parts[1].find(',')));
    cube.min_y = std::stoll(parts[2].substr(0, parts[2].find('.')));
    cube.max_y = std::stoll(parts[2].substr(parts[2].find('.') + 2, parts[2].find(',')));
    cube.min_z = std::stoll(parts[3].substr(0, parts[3].find('.')));
    cube.max_z = std::stoll(parts[3].substr(parts[3].find('.') + 2, parts[3].size()));

    std::vector<Cube> toAdd;
    for (auto &&c : *cubes) {
        auto intersection = cube.intersect(c);
        if (!intersection.isEmpty()) {
            toAdd.push_back(intersection);
        }
    }
    cubes->insert(cubes->end(), toAdd.begin(), toAdd.end());

    if (cube.add) {
        cubes->push_back(cube);
    }
}

uint64_t findSolution1(std::vector<Cube> *cubes)
{
    uint64_t count = 0;
    int64_t min_x = cubes->at(0).min_x;
    int64_t max_x = cubes->at(0).max_x;
    int64_t min_y = cubes->at(0).min_y;
    int64_t max_y = cubes->at(0).max_y;
    int64_t min_z = cubes->at(0).min_z;
    int64_t max_z = cubes->at(0).max_z;
    for (auto &c : *cubes) {
        min_x = c.min_x < min_x ? c.min_x : min_x;
        max_x = c.max_x > max_x ? c.max_x : max_x;
        min_y = c.min_y < min_y ? c.min_y : min_y;
        max_y = c.max_y > max_y ? c.max_y : max_y;
        min_z = c.min_z < min_z ? c.min_z : min_z;
        max_z = c.max_z > max_z ? c.max_z : max_z;
    }
    for (auto x = min_x; x <= max_x; x++) {
        for (auto y = min_y; y <= max_y; y++) {
            for (auto z = min_z; z <= max_z; z++) {
                bool isOn = false;
                for (auto &c : *cubes) {
                    if (isOn != c.add) {
                        if (c.min_x <= x && x <= c.max_x && c.min_y <= y && y <= c.max_y && c.min_z <= z &&
                            z <= c.max_z) {
                            isOn = c.add;
                        }
                    }
                }
                if (isOn) {
                    count++;
                }
            }
        }
    }

    return count;
}

uint64_t findSolution2(std::vector<Cube> *cubes)
{
    uint64_t count = 0;
    for (auto&&cube : *cubes) {
        if (cube.add) {
            count += cube.cardinality();
        } else {
            count -= cube.cardinality();
        }
    }
    return count;
}

std::string day22::process1(std::string file)
{
    std::vector<Cube> cubes;
    parse::read<std::vector<Cube> *>(file, '\n', convertLine1, &cubes);
    return std::to_string(findSolution1(&cubes));
}

std::string day22::process2(std::string file)
{
    std::vector<Cube> cubes;
    parse::read<std::vector<Cube> *>(file, '\n', convertLine2, &cubes);
    return std::to_string(findSolution2(&cubes));
}