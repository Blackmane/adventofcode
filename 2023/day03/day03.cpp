/**
 * @file    day03.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    03 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day03.h"

#include "common.h"

std::vector<std::pair<size_t, size_t>> neighbours(size_t from_i, size_t from_j, size_t to_i, size_t to_j, size_t height,
                                                  size_t width)
{
    std::set<std::pair<size_t, size_t>> found;
    for (size_t i = std::min(from_i, to_i), n = std::max(from_i, to_i); i <= n; i++) {
        for (size_t j = std::min(from_j, to_j), m = std::max(from_j, to_j); j <= m; j++) {
            if (i > 0) {
                found.insert(std::make_pair(i - 1, j));
            }
            if (i < height - 1) {
                found.insert(std::make_pair(i + 1, j));
            }
            if (j > 0) {
                found.insert(std::make_pair(i, j - 1));
            }
            if (j < width - 1) {
                found.insert(std::make_pair(i, j + 1));
            }
            // Diagonals
            if (i > 0 && j > 0) {
                found.insert(std::make_pair(i - 1, j - 1));
            }
            if (i > 0 && j < width - 1) {
                found.insert(std::make_pair(i - 1, j + 1));
            }
            if (i < width - 1 && j > 0) {
                found.insert(std::make_pair(i + 1, j - 1));
            }
            if (i < width - 1 && j < width - 1) {
                found.insert(std::make_pair(i + 1, j + 1));
            }
        }
    }
    for (size_t i = std::min(from_i, to_i), n = std::max(from_i, to_i); i <= n; i++) {
        for (size_t j = std::min(from_j, to_j), m = std::max(from_j, to_j); j <= m; j++) {
            found.erase(std::make_pair(i, j));
        }
    }
    std::vector<std::pair<size_t, size_t>> neighborhood;
    for (auto &&neighbour : found) {
        neighborhood.push_back(neighbour);
    }

    return neighborhood;
}

bool isConnected(std::vector<std::string> &list, std::vector<std::pair<size_t, size_t>> &neighborhood)
{
    for (auto &&neighbour : neighborhood) {
        char curr = list[neighbour.first][neighbour.second];
        if (!(('0' <= curr && curr <= '9') || curr == '.')) {
            return true;
        }
    }
    return false;
}

std::string day03::process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);

    int64_t connectedSum = 0;
    size_t from_i = 0;
    size_t from_j = 0;
    size_t to_i = 0;
    size_t to_j = 0;
    std::string number;
    size_t n = list.size();
    size_t m = list[1].size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            char curr = list[i][j];
            if ('0' <= curr && curr <= '9') {
                if (number.empty()) {
                    // Is a new number, save FROM
                    from_i = i;
                    from_j = j;
                }
                number.push_back(curr);
            } else {
                if (number.size() > 0) {
                    std::vector<std::pair<size_t, size_t>> res = neighbours(from_i, from_j, to_i, to_j, n, m);
                    if (isConnected(list, res)) {
                        connectedSum += std::stoi(number);
                    }
                    number = "";
                }
            }

            // TO is always the previous pos
            to_i = i;
            to_j = j;
            if (j == m - 1 && number.size() > 0) {
                std::vector<std::pair<size_t, size_t>> res = neighbours(from_i, from_j, to_i, to_j, n, m);
                if (isConnected(list, res)) {
                    connectedSum += std::stoi(number);
                }
                number = "";
            }
        }
        if (i == n - 1 && number.size() > 0) {
            std::vector<std::pair<size_t, size_t>> res = neighbours(from_i, from_j, to_i, to_j, n, m);
            if (isConnected(list, res)) {
                connectedSum += std::stoi(number);
            }
        }
        number = "";
    }

    return std::to_string(connectedSum);
}

std::vector<std::pair<size_t, size_t>> nearGear(std::vector<std::string> &list,
                                                std::vector<std::pair<size_t, size_t>> &neighbours)
{
    std::vector<std::pair<size_t, size_t>> res;
    for (auto &&n : neighbours) {
        if (list[n.first][n.second] == '*') {
            res.push_back(n);
        }
    }
    return res;
}

void checkGear(size_t from_i, size_t from_j, size_t to_i, size_t to_j, size_t height, size_t width,
               const std::string &number, std::map<std::pair<size_t, size_t>, std::vector<uint64_t>> &connectedGears,
               std::vector<std::string> &list)
{
    std::vector<std::pair<size_t, size_t>> res = neighbours(from_i, from_j, to_i, to_j, height, width);
    auto gears = nearGear(list, res);
    for (auto &&gear : gears) {
        auto it = connectedGears.find(gear);
        if (it == connectedGears.end()) {
            std::vector<uint64_t> connected;
            connected.push_back(std::stoi(number));
            connectedGears.insert(std::make_pair(gear, connected));
        } else {
            it->second.push_back(std::stoi(number));
        }
    }
}

std::string day03::process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);

    std::map<std::pair<size_t, size_t>, std::vector<uint64_t>> connectedGears;

    size_t from_i = 0;
    size_t from_j = 0;
    size_t to_i = 0;
    size_t to_j = 0;
    std::string number;
    size_t n = list.size();
    size_t m = list[1].size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            char curr = list[i][j];
            if ('0' <= curr && curr <= '9') {
                if (number.empty()) {
                    // Is a new number, save FROM
                    from_i = i;
                    from_j = j;
                }
                number.push_back(curr);
            } else {
                if (number.size() > 0) {
                    checkGear(from_i, from_j, to_i, to_j, n, m, number, connectedGears, list);
                    number = "";
                }
            }

            // TO is always the previous pos
            to_i = i;
            to_j = j;
            if (j == m - 1 && number.size() > 0) {
                checkGear(from_i, from_j, to_i, to_j, n, m, number, connectedGears, list);
                number = "";
            }
        }
        if (i == n - 1 && number.size() > 0) {
            checkGear(from_i, from_j, to_i, to_j, n, m, number, connectedGears, list);
        }
        number = "";
    }

    int64_t connectedGearsSum = 0;
    for (auto &&gear : connectedGears) {
        if (gear.second.size() == 2) {
            uint64_t power = gear.second[0] * gear.second[1];
            connectedGearsSum += power;
        }
    }
    return std::to_string(connectedGearsSum);
}