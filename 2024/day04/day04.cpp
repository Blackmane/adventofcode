/**
 * @file    day04.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    04 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day04.h"

#include "common.h"

std::string day04::process1(std::string file)
{
    auto lines = parse::read_all(file);
    int64_t count = 0;

    for (size_t i = 0, n = lines.size(); i < n; i++) {
        for (size_t j = 0, m = lines[i].size(); j < m; j++) {
            if (lines[i][j] == 'X') {
                if (j + 3 < m && lines[i][j + 1] == 'M' && lines[i][j + 2] == 'A' && lines[i][j + 3] == 'S') {
                    count++;
                }
                if (i + 3 < n && lines[i + 1][j] == 'M' && lines[i + 2][j] == 'A' && lines[i + 3][j] == 'S') {
                    count++;
                }
                if (i + 3 < n) {
                    if (j + 3 < m && lines[i + 1][j + 1] == 'M' && lines[i + 2][j + 2] == 'A' &&
                        lines[i + 3][j + 3] == 'S') {
                        count++;
                    }
                    if (j >= 3 && lines[i + 1][j - 1] == 'M' && lines[i + 2][j - 2] == 'A' &&
                        lines[i + 3][j - 3] == 'S') {
                        count++;
                    }
                }
            }

            if (lines[i][j] == 'S') {
                if (j + 3 < m && lines[i][j + 1] == 'A' && lines[i][j + 2] == 'M' && lines[i][j + 3] == 'X') {
                    count++;
                }
                if (i + 3 < n && lines[i + 1][j] == 'A' && lines[i + 2][j] == 'M' && lines[i + 3][j] == 'X') {
                    count++;
                }
                if (i + 3 < n) {
                    if (j + 3 < m && lines[i + 1][j + 1] == 'A' && lines[i + 2][j + 2] == 'M' &&
                        lines[i + 3][j + 3] == 'X') {
                        count++;
                    }
                    if (j >= 3 && lines[i + 1][j - 1] == 'A' && lines[i + 2][j - 2] == 'M' &&
                        lines[i + 3][j - 3] == 'X') {
                        count++;
                    }
                }
            }
        }
    }

    return std::to_string(count);
}

std::string day04::process2(std::string file)
{
    auto lines = parse::read_all(file);
    int64_t count = 0;

    for (size_t i = 0, n = lines.size(); i + 2 < n; i++) {
        for (size_t j = 0, m = lines[i].size(); j + 2 < m; j++) {
            if (lines[i][j] == 'M') {
                if (lines[i][j + 2] == 'S' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'M' &&
                    lines[i + 2][j + 2] == 'S') {
                    count++;
                }
                if (lines[i][j + 2] == 'M' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'S' &&
                    lines[i + 2][j + 2] == 'S') {
                    count++;
                }
            }

            if (lines[i][j] == 'S') {
                if (lines[i][j + 2] == 'M' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'S' &&
                    lines[i + 2][j + 2] == 'M') {
                    count++;
                }
                if (lines[i][j + 2] == 'S' && lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'M' &&
                    lines[i + 2][j + 2] == 'M') {
                    count++;
                }
            }
        }
    }

    return std::to_string(count);
}