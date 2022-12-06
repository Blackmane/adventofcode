/**
 * @file    day06.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    06 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day06.h"

#include "common.h"

#include <unordered_set>

bool check(const std::string &letters)
{
    return letters[0] != letters[1] && letters[0] != letters[2] && letters[0] != letters[3] &&
           letters[1] != letters[2] && letters[1] != letters[3] && letters[2] != letters[3];
}

bool check2(const std::string &letters)
{
    std::unordered_set<char> presence;
    for (auto c : letters) {
        if (presence.find(c) != presence.end()) {
            return false;
        }
        presence.insert(c);
    }
    return true;
}

std::string process1(std::string file)
{
    std::ifstream source;
    source.open(file, std::ifstream::in);
    std::string letters;
    char c;
    int i = 0;
    while (i < 4) {
        source.get(c);
        letters.push_back(c);
        i++;
    }
    if (check(letters)) {
        return std::to_string(i);
    }
    while (source.get(c)) {
        letters[i % 4] = c;
        i++;
        if (check(letters)) {
            return std::to_string(i);
        }
    }
    return "0";
}

std::string process2(std::string file)
{
    std::ifstream source;
    source.open(file, std::ifstream::in);
    std::string letters;
    char c;
    int i = 0;
    while (i < 14) {
        source.get(c);
        letters.push_back(c);
        i++;
    }
    if (check2(letters)) {
        return std::to_string(i);
    }
    while (source.get(c)) {
        letters[i % 14] = c;
        i++;
        if (check2(letters)) {
            return std::to_string(i);
        }
    }
    return "0";
}
