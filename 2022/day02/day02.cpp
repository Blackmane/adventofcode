/**
 * @file    day02.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    01 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day02.h"
#include "common.h"

uint64_t converter1 (std::string line) {
    uint64_t value = 0;
    std::vector<std::string> splitted = parse::split(line, ' ');
    value += splitted[1][0] - 'X' + 1;
    splitted[1][0] = 'A' + value - 1;

    int diff = splitted[0][0] - splitted[1][0];
    if (diff == 0) {
        value += 3;
    }
    if (diff == -1 || diff == 2) {
        value += 6;
    }
    return value;
}

uint64_t converter2 (std::string line) {
    uint64_t value = 0;
    std::vector<std::string> splitted = parse::split(line, ' ');

    int choose = splitted[0][0] - 'A';
    if (splitted[1][0] == 'X') {
        value += (choose - 1 + 3) % 3 + 1;
    }
    if (splitted[1][0] == 'Y') {
        value += 3;
        value += choose + 1;
    }
    if (splitted[1][0] == 'Z') {
        value += 6;
        value += (choose + 1) % 3 + 1;
    }

    return value;
}

void insert(uint64_t value, uint64_t* sum) {
    *sum += value;
}

std::string process1(std::string file) {
    uint64_t count = 0;
    parse::read<uint64_t, uint64_t*>(file, '\n', &converter1, &insert, &count);
    return std::to_string(count);
}


std::string process2(std::string file) {
    uint64_t count = 0;
    parse::read<uint64_t, uint64_t*>(file, '\n', &converter2, &insert, &count);
    return std::to_string(count);
}

