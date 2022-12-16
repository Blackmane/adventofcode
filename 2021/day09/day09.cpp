/**
 * @file    day09.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    08 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day09.h"

#include "common.h"

#include <deque>
#include <algorithm>

void insert(std::vector<std::vector<int>> *list, std::string line)
{
    std::vector<int> values;
    for (auto &c : line) {
        values.emplace_back(c - '0');
    }
    list->emplace_back(values);
}

std::string findSolution1(std::vector<std::vector<int>> *list)
{
    uint64_t res = 0;
    size_t m = list->at(0).size();
    size_t n = list->size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            auto cur = list->at(i)[j];
            if (i > 0 && list->at(i - 1)[j] <= cur) {
                continue;
            }
            if (j > 0 && list->at(i)[j - 1] <= cur) {
                continue;
            }
            if (i < n - 1 && list->at(i + 1)[j] <= cur) {
                continue;
            }
            if (j < m - 1 && list->at(i)[j + 1] <= cur) {
                continue;
            }
            res += cur + 1;
        }
    }
    return std::to_string(res);
}

uint64_t basinSize(std::vector<std::vector<int>> *list, size_t i, size_t j)
{
    uint64_t count = 1;
    size_t m = list->at(0).size();
    size_t n = list->size();

    std::vector<bool> visited(n * m, false);
    visited[i * m + j] = true;

    std::deque<std::pair<size_t, size_t>> queue;
    queue.push_back(std::make_pair(i, j));

    auto visit = [&](int cur, size_t ix, size_t jx) {
        auto value = list->at(ix)[jx];
        if (!visited[ix * m + jx] && value != 9 && value > cur) {
            queue.push_back(std::make_pair(ix, jx));
            visited[ix * m + jx] = true;
            count++;
        }
    };

    while (!queue.empty()) {
        auto indexes = queue.front();
        queue.pop_front();
        auto cur = list->at(indexes.first)[indexes.second];

        if (indexes.first > 0) {
            visit(cur, indexes.first - 1, indexes.second);
        } 
        if (indexes.second > 0) {
            visit(cur, indexes.first, indexes.second - 1);

        } 
        if (indexes.first < n - 1) {
            visit(cur, indexes.first + 1, indexes.second);
        }
        if (indexes.second < m - 1) {
            visit(cur, indexes.first, indexes.second + 1);
        }
    }

    return count;
}

std::string findSolution2(std::vector<std::vector<int>> *list)
{
    size_t m = list->at(0).size();
    size_t n = list->size();
    std::vector<uint64_t> basinSizes;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            auto cur = list->at(i)[j];
            if (i > 0 && list->at(i - 1)[j] <= cur) {
                continue;
            }
            if (j > 0 && list->at(i)[j - 1] <= cur) {
                continue;
            }
            if (i < n - 1 && list->at(i + 1)[j] <= cur) {
                continue;
            }
            if (j < m - 1 && list->at(i)[j + 1] <= cur) {
                continue;
            }
            basinSizes.emplace_back(basinSize(list, i, j));
        }
    }
    std::sort(basinSizes.begin(), basinSizes.end(),  std::greater<uint64_t>());
    return std::to_string(basinSizes[0] * basinSizes[1] * basinSizes[2]);
}

std::string day09::process1(std::string file)
{
    std::vector<std::vector<int>> list;
    parse::read<std::vector<std::vector<int>> *>(file, '\n', insert, &list);
    return findSolution1(&list);
}

std::string day09::process2(std::string file)
{
    std::vector<std::vector<int>> list;
    parse::read<std::vector<std::vector<int>> *>(file, '\n', insert, &list);
    return findSolution2(&list);
}
