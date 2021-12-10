/**
 * @file    day10.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    10 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day10.h"

#include "common.h"

#include <algorithm>
#include <deque>

uint64_t convertInput1(std::string line)
{
    uint64_t res = 0;
    std::deque<char> stack;
    for (auto c : line) {
        switch (c) {
            case '(':
            case '[':
            case '{':
            case '<':
                stack.push_back(c);
                break;
            case '>':
                if (stack.back() == '<') {
                    stack.pop_back();
                } else {
                    return 25137;
                }
                break;
            case '}':
                if (stack.back() == '{') {
                    stack.pop_back();
                } else {
                    return 1197;
                }
                break;
            case ']':
                if (stack.back() == '[') {
                    stack.pop_back();
                } else {
                    return 57;
                }
                break;
            case ')':
                if (stack.back() == '(') {
                    stack.pop_back();
                } else {
                    return 3;
                }
                break;
        }
    }
    return res;
}

uint64_t convertInput2(std::string line)
{
    std::deque<char> stack;
    for (auto c : line) {
        switch (c) {
            case '(':
            case '[':
            case '{':
            case '<':
                stack.push_back(c);
                break;
            case '>':
                if (stack.back() == '<') {
                    stack.pop_back();
                } else {
                    return 0;
                }
                break;
            case '}':
                if (stack.back() == '{') {
                    stack.pop_back();
                } else {
                    return 0;
                }
                break;
            case ']':
                if (stack.back() == '[') {
                    stack.pop_back();
                } else {
                    return 0;
                }
                break;
            case ')':
                if (stack.back() == '(') {
                    stack.pop_back();
                } else {
                    return 0;
                }
                break;
        }
    }

    uint64_t res = 0;
    while (!stack.empty()) {
        res *= 5;
        switch (stack.back()) {
            case '(':
                res += 1;
                break;
            case '[':
                res += 2;
                break;
            case '{':
                res += 3;
                break;
            case '<':
                res += 4;
                break;
        }
        stack.pop_back();
    }

    return res;
}

void sum(uint64_t value, uint64_t *total)
{
    *total = value + *total;
}

void insert(uint64_t value, std::vector<uint64_t> *valueList)
{
    if (value != 0) {
        valueList->emplace_back(value);
    }
}

std::string process1(std::string file)
{
    uint64_t value = 0;
    parse::read<uint64_t, uint64_t *>(file, '\n', convertInput1, sum, &value);
    return std::to_string(value);
}

std::string process2(std::string file)
{
    std::vector<uint64_t> valueList;
    parse::read<uint64_t, std::vector<uint64_t> *>(file, '\n', convertInput2, insert, &valueList);
    std::sort(valueList.begin(), valueList.end());
    return std::to_string(valueList[valueList.size()/2]);
}
