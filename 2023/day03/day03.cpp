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

bool isConnected(std::vector<std::string> &scheme, std::vector<std::pair<size_t, size_t>> &neighborhood)
{
    for (auto &&neighbour : neighborhood) {
        char curr = scheme[neighbour.first][neighbour.second];
        if (!(('0' <= curr && curr <= '9') || curr == '.')) {
            return true;
        }
    }
    return false;
}

void parseScheme(
    std::vector<std::string> &scheme,
    std::function<void(std::vector<std::string> &, size_t, size_t, size_t, size_t, size_t, size_t, const std::string &)>
        elaborate)
{
    size_t from_i = 0;
    size_t from_j = 0;
    size_t to_i = 0;
    size_t to_j = 0;
    std::string number;
    size_t n = scheme.size();
    size_t m = scheme[1].size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            char curr = scheme[i][j];
            if ('0' <= curr && curr <= '9') {
                if (number.empty()) {
                    // Is a new number, save FROM
                    from_i = i;
                    from_j = j;
                }
                number.push_back(curr);
            } else {
                // The number is terminated
                if (number.size() > 0) {
                    elaborate(scheme, from_i, from_j, to_i, to_j, n, m, number);
                    number = "";
                }
            }

            // TO is always the previous pos, TO is valid only if number is not empty
            to_i = i;
            to_j = j;

            if (j == m - 1 && number.size() > 0) {
                // The last char of the line could be a number
                elaborate(scheme, from_i, from_j, to_i, to_j, n, m, number);
                number = "";
            }
        }
    }
}

std::string day03::process1(std::string file)
{
    std::vector<std::string> scheme;
    parse::read_all(file, &scheme);

    int64_t connectedSum = 0;

    parseScheme(scheme, [&connectedSum](std::vector<std::string> &locScheme, size_t from_i, size_t from_j, size_t to_i,
                                        size_t to_j, size_t n, size_t m, const std::string &number) {
        std::vector<std::pair<size_t, size_t>> res = matrix::neighboursArea(from_i, from_j, to_i, to_j, n, m);
        if (isConnected(locScheme, res)) {
            connectedSum += std::stoi(number);
        }
    });

    return std::to_string(connectedSum);
}

std::vector<std::pair<size_t, size_t>> nearGears(std::vector<std::string> &scheme,
                                                 std::vector<std::pair<size_t, size_t>> &neighbours)
{
    std::vector<std::pair<size_t, size_t>> res;
    for (auto &&n : neighbours) {
        if (scheme[n.first][n.second] == '*') {
            res.push_back(n);
        }
    }
    return res;
}

void checkGear(size_t from_i, size_t from_j, size_t to_i, size_t to_j, size_t height, size_t width,
               const std::string &number, std::map<std::pair<size_t, size_t>, std::vector<uint64_t>> &connectedGears,
               std::vector<std::string> &scheme)
{
    std::vector<std::pair<size_t, size_t>> res = matrix::neighboursArea(from_i, from_j, to_i, to_j, height, width);
    auto gears = nearGears(scheme, res);
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
    std::vector<std::string> scheme;
    parse::read_all(file, &scheme);

    std::map<std::pair<size_t, size_t>, std::vector<uint64_t>> connectedGears;

    parseScheme(scheme, [&connectedGears](std::vector<std::string> &locScheme, size_t from_i, size_t from_j,
                                          size_t to_i, size_t to_j, size_t n, size_t m, const std::string &number) {
        checkGear(from_i, from_j, to_i, to_j, n, m, number, connectedGears, locScheme);
    });

    int64_t connectedGearsSum = 0;
    for (auto &&gear : connectedGears) {
        if (gear.second.size() == 2) {
            uint64_t power = gear.second[0] * gear.second[1];
            connectedGearsSum += power;
        }
    }
    return std::to_string(connectedGearsSum);
}