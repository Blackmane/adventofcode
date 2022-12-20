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

struct Node {
    int64_t value;
    bool moved = false;
    Node(int v) : value(v){};

    bool operator==(const Node &b) const
    {
        return value == b.value;
    }
};

void push_back_integer(std::list<Node> *list, std::string part)
{
    list->push_back(Node(std::stoi(part)));
}

void shuffle(std::list<Node> &list)
{
    int n = list.size();
    for (auto it = list.begin(); it != list.end();) {
        if (!it->moved) {
            auto curNode = *it;
            curNode.moved = true;
            auto eresable = it;
            ++it;
            list.erase(eresable);

            auto pos = it;
            int m = 0;
            if (curNode.value >= 0) {
                m = curNode.value % (n - 1);
            } else {
                m = (curNode.value % (n - 1)) + n - 1;
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
            list.insert(pos, curNode);
        } else {
            it++;
        }
    }
}

int64_t calcResult(const std::list<Node> &list)
{
    int i = 0;
    for (auto &&node : list) {
        if (node.value == 0) {
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
            count += node.value;
        }
        i++;
    }
    return count;
}

int64_t getSolution(std::list<Node> &list)
{
    shuffle(list);
    return calcResult(list);
}

void shuffle2(std::list<Node> &list, std::vector<std::_List_iterator<Node>> &order)
{
    int n = list.size();
    for (int j = 0; j < n; j++) {
        auto curNode = *order[j];
        auto eresable = order[j];
        auto pos = ++order[j];
        list.erase(eresable);
        int m = 0;
        if (curNode.value >= 0) {
            m = curNode.value % (n - 1);
        } else {
            m = (curNode.value % (n - 1)) + n - 1;
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

int64_t getSolution2(std::list<Node> &list, int64_t key)
{
    std::vector<std::_List_iterator<Node>> order;
    for (auto it = list.begin(); it != list.end(); it++) {
        it->value *= key;
        order.push_back(it);
    }

    for (int j = 0; j < 10; j++) {
        shuffle2(list, order);
    }

    return calcResult(list);
}

std::string day20::process1(std::string file)
{
    std::list<Node> list;
    parse::read<std::list<Node> *>(file, '\n', push_back_integer, &list);
    auto result = getSolution(list);
    return std::to_string(result);
}

std::string day20::process2(std::string file)
{
    std::list<Node> list;
    parse::read<std::list<Node> *>(file, '\n', push_back_integer, &list);
    auto result = getSolution2(list, 811589153);
    return std::to_string(result);
}