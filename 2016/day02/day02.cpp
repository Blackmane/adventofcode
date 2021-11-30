/**
 * @file    day02.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    28 Nov 2021
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
#include <vector>

// ===== Implementation =====

uint64_t analize1(std::string line, int i = 5) {
    /*
        1 2 3
        4 5 6
        7 8 9
    */
    for (auto &c: line) {
        switch (c) {
            case 'U':
                i = i > 3 ? i - 3 : i;
                break;
            case 'D':
                i = i < 7 ? i + 3 : i;
                break;
            case 'L':
                i = i % 3 != 1 ? i - 1 : i;
                break;
            case 'R':
                i = i % 3 != 0 ? i + 1 : i;
                break;
        }
    }

    return i;
}


const std::vector<char> keypad = {
        '0', '0', '1', '0', '0',
        '0', '2', '3', '4', '0',
        '5', '6', '7', '8', '9',
        '0', 'A', 'B', 'C', '0',
        '0', '0', 'D', '0', '0',
};

uint64_t analize2(std::string line, int i) {
    /*
        1
      2 3 4
    5 6 7 8 9
      A B C
        D
    */
    const int n = 5;
    for (auto &c: line) {
        int next = i;
        switch (c) {
            case 'U':
                next = i >= n ? i - n : i;
                break;
            case 'D':
                next = i < n * (n - 1) ? i + n : i;
                break;
            case 'L':
                next = i % n != 0 ? i - 1 : i;
                break;
            case 'R':
                next = i % n != n - 1 ? i + 1 : i;
                break;
        }
        // Check next is changed from i and is not an empty cell
        if (next != i && keypad[next] != '0') {
            // If is good go to it
            i = next;
        }
    }
    return i;
}


std::string findSolution1(std::vector <std::string> *stepsList) {
    std::string solution("");
    int i = 5;
    for (auto &line: *stepsList) {
        i = analize1(line, i);
        solution.push_back('0' + i);
    }
    return solution;
}

std::string findSolution2(std::vector <std::string> *stepsList) {
    std::string solution("");
    int i = 10;
    for (auto &line: *stepsList) {
        i = analize2(line, i);
        solution.push_back(keypad[i]);
    }
    return solution;
}

// ===== Execution =====

std::string process1(std::string file) {

    std::vector <std::string> stepsList;
    parse::read < std::string, std::vector < std::string > * > (file, '\n', parse::push_back, &stepsList);

    std::string result = findSolution1(&stepsList);
    return result;
}


std::string process2(std::string file) {
    std::vector <std::string> stepsList;
    parse::read_all(file, &stepsList);

    std::string result = findSolution2(&stepsList);
    return result;
}
