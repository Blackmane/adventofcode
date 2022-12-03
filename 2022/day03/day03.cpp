/**
 * @file    day03.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    02 Dec 2022
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

#include <algorithm>
#include <bitset>

uint64_t positionOf(char item)
{
    if (item >= 'a' && item <= 'z') {
        return item - 'a';
    }
    return item - 'A' + 26;
}

uint64_t getPriority(const std::string &line)
{
    auto n = line.size();
    auto half = n / 2;

    std::bitset<52> firstPart;
    for (size_t i = 0; i < half; ++i) {
        firstPart.set(positionOf(line[i]));
    }
    std::bitset<52> secondPart;
    for (size_t j = half; j < n; ++j) {
        secondPart.set(positionOf(line[j]));
    }
    auto common = firstPart & secondPart;
    return common._Find_first() + 1;

}

void add(uint64_t value, uint64_t *sum)
{
    *sum += value;
}

std::string process1(std::string file)
{
    uint64_t count = 0;
    parse::read<uint64_t, uint64_t *>(file, '\n', &getPriority, &add, &count);
    return std::to_string(count);
}

std::bitset<52> strToBitset(const std::string &line)
{
    std::bitset<52> contains;
    for (auto c : line) {
        contains.set(positionOf(c));
    }
    return contains;
}

void insertBitset(std::vector<std::bitset<52>> *list, const std::string &line)
{
    list->push_back(strToBitset(line));
}

uint64_t getBadges(std::vector<std::bitset<52>> *list)
{
    uint64_t count = 0;
    for (int i = 0, n = list->size(); i < n - 2; i = i + 3) {
        auto common = list->at(i) & list->at(i + 1) & list->at(i + 2);
        count += common._Find_first() + 1;
    }
    return count;
}

std::string process2(std::string file)
{
    std::vector<std::bitset<52>> list;
    parse::read<std::vector<std::bitset<52>> *>(file, '\n', &insertBitset, &list);
    auto result = getBadges(&list);
    return std::to_string(result);
}
