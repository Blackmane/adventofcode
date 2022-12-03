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

uint64_t priorityOf (char item) {
    if (item >= 'a' && item <= 'z') {
        return item - 'a' + 1;
    }
    return item - 'A' + 27;
}

uint64_t getPriority (std::string line) {
    auto n = line.size();
    auto half = n / 2;

    for (size_t i = 0; i < half; ++i) {
        for (size_t j = half; j < n; ++j) {
            if (line[i] == line[j]) {

                return priorityOf(line[i]);
            }
        }
    }
    return 0;
}

bool contains(std::string s, char c) {
    for (int i = 0, n = s.size(); i < n; i++) {
        if (s[i] == c) {
            return true;
        }
        if (s[i] > c) {
            return false;
        }
    }
    return false;
}

char getCommont(std::string& a, std::string& b, std::string& c) {
    for (int i = 0, n = a.size(); i < n; i++) {
        if (contains(b, a[i]) && contains(c, a[i])) {
            return a[i];
        }
    }
    return 'a';
}

uint64_t getBadges (std::vector<std::string> *list) {
    uint64_t count = 0;
    for (int i = 0, n = list->size(); i < n - 2; i = i + 3) {
        auto common = getCommont(list->at(i), list->at(i + 1), list->at(i + 2));
        count += priorityOf(common);
    }
    return count;
}

void add(uint64_t value, uint64_t* sum) {
    *sum += value;
}

std::string process1(std::string file) {
    uint64_t count = 0;
    parse::read<uint64_t, uint64_t*>(file, '\n', &getPriority, &add, &count);
    return std::to_string(count);
}

void insert(std::vector<std::string>* list, std::string line) {
    std::sort(line.begin(), line.end());
    list->push_back(line);
}

std::string process2(std::string file) {
    std::vector<std::string> list;
    parse::read<std::vector<std::string> *>(file, '\n', &insert, &list);
    auto result = getBadges(&list);
    return std::to_string(result);
}
