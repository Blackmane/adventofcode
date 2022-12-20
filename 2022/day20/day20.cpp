/**
 * @file    day20.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    20 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day20.h"

#include "common.h"

#include <list>

void push_back_integer(std::list<int64_t> *list, std::string part)
{
    list->push_back(std::stoi(part));
}

void shuffle(std::list<int64_t> &list, std::vector<std::_List_iterator<int64_t>> &order)
{
    int n = list.size();
    for (int j = 0; j < n; j++) {
        auto curNode = *order[j];
        auto eresable = order[j];
        auto pos = ++order[j];
        list.erase(eresable);
        int m = curNode % (n - 1);
        if (m < 0) {
            m = m + n - 1;
        }
        for (int i = 0; i < m; i++) {
            if (pos == list.end()) {
                pos = list.begin();
            }
            pos++;
        }
        if (pos == list.end()) {
            pos = list.begin();
        }
        order[j] = list.insert(pos, curNode);
    }
}

int64_t calcResult(const std::list<int64_t> &list)
{
    int i = 0;
    for (auto &&node : list) {
        if (node == 0) {
            break;
        }
        i++;
    }
    int n = list.size();
    int thresholdA = (1000 + i) % n;
    int thresholdB = (2000 + i) % n;
    int thresholdC = (3000 + i) % n;
    int64_t count = 0;
    i = 0;
    for (auto &&node : list) {
        if (i == thresholdA || i == thresholdB || i == thresholdC) {
            count += node;
        }
        i++;
    }
    return count;
}

int64_t getSolution(std::list<int64_t> &list, int64_t key, int steps)
{
    std::vector<std::_List_iterator<int64_t>> order;
    for (auto it = list.begin(); it != list.end(); it++) {
        *it *= key;
        order.push_back(it);
    }

    for (int j = 0; j < steps; j++) {
        shuffle(list, order);
    }

    return calcResult(list);
}

std::string day20::process1(std::string file)
{
    std::list<int64_t> list;
    parse::read<std::list<int64_t> *>(file, '\n', push_back_integer, &list);
    auto result = getSolution(list, 1, 1);
    return std::to_string(result);
}

std::string day20::process2(std::string file)
{
    std::list<int64_t> list;
    parse::read<std::list<int64_t> *>(file, '\n', push_back_integer, &list);
    auto result = getSolution(list, 811589153, 10);
    return std::to_string(result);
}