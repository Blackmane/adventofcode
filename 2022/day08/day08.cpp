/**
 * @file    day08.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    08 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day08.h"

#include "common.h"

void insert(std::vector<std::string> *forest, const std::string &line)
{
    forest->push_back(line);
}

uint64_t countVisible(std::vector<std::string> &forest)
{
    int n = forest.size();
    int m = forest[0].size();
    std::vector<std::vector<bool>> visibility;
    for (int i = 0; i < n; ++i) {
        std::vector<bool> empty(m, false);
        visibility.push_back(empty);
    }

    for (int i = 0; i < n; ++i) {
        char max_top = '0' - 1;
        char max_left = '0' - 1;
        char max_bottom = '0' - 1;
        char max_right = '0' - 1;
        for (int j = 0; j < m; ++j) {
            if (max_left < forest[i][j]) {
                visibility[i][j] = true;
                max_left = forest[i][j];
            }
            if (max_top < forest[j][i]) {
                visibility[j][i] = true;
                max_top = forest[j][i];
            }
            if (max_right < forest[i][m - j - 1]) {
                visibility[i][m - j - 1] = true;
                max_right = forest[i][m - j - 1];
            }
            if (max_bottom < forest[m - j - 1][i]) {
                visibility[m - j - 1][i] = true;
                max_bottom = forest[m - j - 1][i];
            }
        }
    }

    uint64_t count = 0;
    for (auto line : visibility) {
        for (auto visible : line) {
            if (visible) {
                count++;
            }
        }
    }
    return count;
}

uint64_t maxScenic(std::vector<std::string> &forest)
{
    uint64_t max = 0;
    int n = forest.size();
    int m = forest[0].size();

    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < m - 1; ++j) {
            uint64_t scenic = 1;
            uint64_t count = 0;
            for (int k = i - 1; k >= 0; --k) {
                count++;
                if (forest[k][j] >= forest[i][j]) {
                    break;
                }
            }
            scenic *= count;

            count = 0;
            for (int k = j - 1; k >= 0; --k) {
                count++;
                if (forest[i][k] >= forest[i][j]) {
                    break;
                }
            }
            scenic *= count;

            count = 0;
            for (int k = i + 1; k < n; ++k) {
                count++;
                if (forest[k][j] >= forest[i][j]) {
                    break;
                }
            }
            scenic *= count;

            count = 0;
            for (int k = j + 1; k < m; ++k) {
                count++;
                if (forest[i][k] >= forest[i][j]) {
                    break;
                }
            }
            scenic *= count;
            if (scenic > max) {
                max = scenic;
            }
        }
    }

    return max;
}

std::string day08::process1(std::string file)
{
    std::vector<std::string> forest;
    parse::read<std::vector<std::string> *>(file, '\n', &insert, &forest);
    auto result = countVisible(forest);
    return std::to_string(result);
}

std::string day08::process2(std::string file)
{
    std::vector<std::string> forest;
    parse::read<std::vector<std::string> *>(file, '\n', &insert, &forest);
    auto result = maxScenic(forest);
    return std::to_string(result);
}
