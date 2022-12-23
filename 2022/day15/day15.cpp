/**
 * @file    day15.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    15 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day15.h"

#include "common.h"

struct Sensor {
    int64_t x;
    int64_t y;

    int64_t distance;
};

typedef std::pair<int64_t, int64_t> Pos;

typedef std::map<Pos, char> Map;

struct Data {
    std::vector<Sensor> sensors;
    Map map;
};

void insert(Data *data, std::string line)
{
    Sensor sensor;
    auto parts = parse::split(line, '=');
    auto pos = parts[1].find(',');
    sensor.x = std::stoll(parts[1].substr(0, pos));
    pos = parts[2].find(':');
    sensor.y = std::stoll(parts[2].substr(0, pos));
    data->map.insert(std::make_pair(std::make_pair(sensor.x, sensor.y), 'S'));
    pos = parts[3].find(',');
    int64_t x = std::stoll(parts[3].substr(0, pos));
    int64_t y = std::stoll(parts[4]);
    data->map.insert(std::make_pair(std::make_pair(x, y), 'B'));
    sensor.distance = std::abs(sensor.x - x) + std::abs(sensor.y - y);
    data->sensors.push_back(sensor);
}

uint64_t findSolution(Data &data, int64_t y)
{
    int64_t minx = 0;
    int64_t maxx = 0;

    for (auto &&p : data.map) {
        if (p.first.first < minx) {
            minx = p.first.first;
        }
        if (p.first.first > maxx) {
            maxx = p.first.first;
        }
    }
    int64_t maxDistance = 0;
    for (auto &&s : data.sensors) {
        if (s.distance > maxDistance) {
            maxDistance = s.distance;
        }
    }
    minx -= maxDistance;
    maxx += maxDistance;
    uint64_t count = 0;
    for (int x = minx; x <= maxx; ++x) {
        if (data.map.find(std::make_pair(x, y)) == data.map.end()) {
            for (auto &&s : data.sensors) {
                int64_t distance = std::abs(s.x - x) + std::abs(s.y - y);
                if (distance <= s.distance) {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}
uint64_t findSolution2(Data &data, int64_t size)
{
    for (int64_t y = 0; y <= size; y++) {
        for (int64_t x = 0; x <= size; x++) {
            if (data.map.find(std::make_pair(x, y)) != data.map.end()) {
                continue;
            }

            bool checked = false;
            for (auto &&s : data.sensors) {
                int64_t distance = std::abs(s.x - x) + std::abs(s.y - y);
                if (distance <= s.distance) {
                    if (s.x > x) {
                        x = s.x + (s.x - x);
                    } else {
                        if (s.x < x) {
                            x += s.distance - distance;
                        }
                    }
                    checked = true;
                    break;
                }
            }
            if (!checked) {
                return x * 4000000 + y;
            }
        }
    }
    return 0;
}

std::string execute1(std::string file, uint64_t size)
{
    Data data;
    parse::read<Data *>(file, '\n', insert, &data);
    auto result = findSolution(data, size);
    return std::to_string(result);
}

std::string day15::test1(std::string file)
{
    return execute1(file, 10);
}

std::string day15::process1(std::string file)
{
    return execute1(file, 2000000);
}

std::string execute2(std::string file, uint64_t size)
{
    Data data;
    parse::read<Data *>(file, '\n', insert, &data);
    auto result = findSolution2(data, size);
    return std::to_string(result);
}

std::string day15::test2(std::string file)
{
    return execute2(file, 20);
}

std::string day15::process2(std::string file)
{
    return execute2(file, 4000000);
}
