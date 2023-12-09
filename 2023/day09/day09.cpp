/**
 * @file    day09.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    09 Dec 2023
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

void parser(std::vector<std::vector<int64_t>> *s, const std::string &line)
{
    s->push_back(parse::getGenericIntegers<int64_t>(line));
}

std::vector<std::vector<int64_t>> explode(std::vector<int64_t> &numbers)
{
    std::vector<std::vector<int64_t>> list;
    list.push_back(numbers);
    bool lastZeros = false;
    while (!lastZeros) {
        std::vector<int64_t> nextLine;
        for (int i = 0, n = list.back().size(); i < n - 1; i++) {
            auto diff = list.back()[i + 1] - list.back()[i];
            nextLine.push_back(diff);
        }
        list.push_back(nextLine);
        lastZeros = std::all_of(nextLine.begin(), nextLine.end(), [](int64_t val) { return val == 0; });
    }
    return list;
}

int64_t getNext(std::vector<int64_t> &numbers)
{
    std::vector<std::vector<int64_t>> list = explode(numbers);
    int64_t value = 0;
    for (int i = list.size() - 1; i >= 0; i--) {
        value += list[i].back();
    }
    return value;
}

int64_t getPrec(std::vector<int64_t> &numbers)
{
    std::vector<std::vector<int64_t>> list = explode(numbers);
    int64_t value = 0;
    for (int i = list.size() - 1; i >= 0; i--) {
        value = list[i][0] - value;
    }
    return value;
}

int64_t resolver(std::vector<std::vector<int64_t>> &list, std::function<int64_t(std::vector<int64_t> &)> calc)
{
    int64_t sum = 0;
    for (auto &&numbers : list) {
        sum += calc(numbers);
    }
    return sum;
}

std::string day09::process1(std::string file)
{
    std::vector<std::vector<int64_t>> list;
    parse::read<std::vector<std::vector<int64_t>> *>(file, '\n', parser, &list);
    return std::to_string(resolver(list, getNext));
}

std::string day09::process2(std::string file)
{
    std::vector<std::vector<int64_t>> list;
    parse::read<std::vector<std::vector<int64_t>> *>(file, '\n', parser, &list);
    return std::to_string(resolver(list, getPrec));
}