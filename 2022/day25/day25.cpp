/**
 * @file    day25.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    25 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day25.h"

#include "common.h"

void add(int64_t *sum, const std::string line)
{
    int64_t value = 0;
    int64_t posValue = 1;
    for (int i = line.size(); i > 0; i--) {
        switch (line[i - 1]) {
            case '=':
                value -= 2 * posValue;
                break;
            case '-':
                value -= posValue;
                break;
            case '0':
                value += 0;
                break;
            case '1':
                value += posValue;
                break;
            case '2':
                value += 2 * posValue;
                break;
        }
        posValue *= 5;
    }
    println(value);
    *sum += value;
}

std::string convertNum(int64_t num)
{
    std::string result;
    int64_t part = num;
    while (part > 0) {
        int cur = part % 5;
        part = part / 5;
        switch (cur) {
            case 0:
                result.push_back('0');
                break;
            case 1:
                result.push_back('1');
                break;
            case 2:
                result.push_back('2');
                break;
            case 3:
                result.push_back('=');
                part += 1;
                break;
            case 4:
                result.push_back('-');
                part += 1;
                break;
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string day25::process1(std::string file)
{
    int64_t sum = 0;
    parse::read<int64_t *>(file, '\n', &add, &sum);
    auto result = convertNum(sum);
    return result;
}

std::string day25::process2(std::string file)
{
    return "0";
}