/**
 * @file    day07.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    07 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day07.h"

#include "common.h"

bool test(const std::vector<uint64_t> &numbers, size_t next, uint64_t calc, uint64_t total)
{
    if (next >= numbers.size()) {
        return calc == total;
    }
    if (calc > total) {
        return false;
    }
    return test(numbers, next + 1, calc + numbers[next], total) || test(numbers, next + 1, calc * numbers[next], total);
}

uint64_t concatenate(uint64_t first, uint64_t second)
{
    uint64_t pow = 1;
    uint64_t parz = second;
    while (parz > 0) {
        pow *= 10;
        parz /= 10;
    }
    return first * pow + second;
}

bool test2(const std::vector<uint64_t> &numbers, size_t next, uint64_t calc, const uint64_t total)
{
    if (next >= numbers.size()) {
        return calc == total;
    }
    if (calc > total) {
        return false;
    }
    return test2(numbers, next + 1, calc + numbers[next], total) ||
           test2(numbers, next + 1, calc * numbers[next], total) ||
           test2(numbers, next + 1, concatenate(calc, numbers[next]), total);
}

std::string process(std::string file,
                    std::function<bool(const std::vector<uint64_t> &, size_t, uint64_t, const uint64_t)> tester)
{
    uint64_t sum = 0;
    parse::read<uint64_t &>(
        file, '\n',
        [&](uint64_t &, const std::string &line) {
            auto parts = parse::split(line, ':');
            uint64_t total = std::stoll(parts[0]);
            auto numbers = parse::getIntegers(parts[1]);
            if (tester(numbers, 1, numbers[0], total)) {
                sum += total;
            }
        },
        sum);

    return std::to_string(sum);
}

std::string day07::process1(std::string file)
{
    return process(file, test);
}

std::string day07::process2(std::string file)
{
    return process(file, test2);
}