/**
 * @file    day13.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    13 Dec 2023
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

typedef std::vector<std::string> Map;

void read(const std::string &file, std::vector<Map> &list)
{
    std::ifstream source;
    source.open(file);
    std::string part;

    Map map;
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            map.push_back(part);
        } else {
            // New map
            list.push_back(map);
            map = Map();
        }
    }
    list.push_back(map);
}

bool isSimmetricalHCount(const Map &map, int jx, uint val)
{
    int n = map.size();
    int m = map[0].size();
    uint differBy = 0;
    for (int j = jx; j >= 0; j--) {
        auto sj = 2 * jx - j + 1;
        if (sj >= m) {
            break;
        }
        for (int i = 0; i < n; i++) {
            if (map[i][j] != map[i][sj]) {
                differBy++;
                if (differBy > val) {
                    return false;
                }
            }
        }
    }
    return differBy == val;
}

bool isSimmetricalVCount(const Map &map, int ix, uint val)
{
    int n = map.size();
    int m = map[0].size();
    uint differBy = 0;
    for (int i = ix; i >= 0; i--) {
        auto si = 2 * ix - i + 1;
        if (si >= n) {
            break;
        }
        for (int j = 0; j < m; j++) {
            if (map[i][j] != map[si][j]) {
                differBy++;
                if (differBy > val) {
                    return false;
                }
            }
        }
    }
    return differBy == val;
}

uint64_t getSimmetry(const Map &map, uint differBy = 0)
{
    for (int j = 0, m = map[0].size(); j < m - 1; j++) {
        if (isSimmetricalHCount(map, j, differBy)) {
            return j + 1;
        }
    }
    for (int i = 0, n = map.size(); i < n - 1; i++) {
        if (isSimmetricalVCount(map, i, differBy)) {
            return (i + 1) * 100;
        }
    }
    return 0;
}

std::string day13::process1(std::string file)
{
    std::vector<Map> list;
    read(file, list);
    uint64_t sum = 0;
    for (auto &&map : list) {
        sum += getSimmetry(map);
    }
    return std::to_string(sum);
}

std::string day13::process2(std::string file)
{
    std::vector<Map> list;
    read(file, list);
    uint64_t sum = 0;
    for (auto &&map : list) {
        sum += getSimmetry(map, 1);
    }
    return std::to_string(sum);
}