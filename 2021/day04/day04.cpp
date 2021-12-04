/**
 * @file    day04.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    04 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day04.h"

#include "common.h"

#include <assert.h>

struct board {
    std::array<std::array<uint64_t, 5>, 5> numbers = { { { 0, 0, 0, 0, 0 },
                                                         { 0, 0, 0, 0, 0 },
                                                         { 0, 0, 0, 0, 0 },
                                                         { 0, 0, 0, 0, 0 },
                                                         { 0, 0, 0, 0, 0 } } };
    std::array<std::array<bool, 5>, 5> picked      = { { { 0, 0, 0, 0, 0 },
                                                    { 0, 0, 0, 0, 0 },
                                                    { 0, 0, 0, 0, 0 },
                                                    { 0, 0, 0, 0, 0 },
                                                    { 0, 0, 0, 0, 0 } } };
    bool isSolved()
    {
        for (size_t i = 0; i < 5; i++) {
            bool allLine = true;
            for (size_t j = 0; j < 5; j++) {
                if (!picked[i][j]) {
                    allLine = false;
                    break;
                }
            }
            if (allLine) {
                return true;
            }
            bool allColumn = true;
            for (size_t j = 0; j < 5; j++) {
                if (!picked[j][i]) {
                    allColumn = false;
                    break;
                }
            }
            if (allColumn) {
                return true;
            }
        }
        return false;
    }

    uint64_t sumNotCalled()
    {
        uint64_t sum = 0;
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                if (!picked[i][j]) {
                    sum += numbers[i][j];
                }
            }
        }
        return sum;
    }
};

void populateBoards(std::vector<std::string> *values,
                    std::vector<board> *boards)
{
    auto len          = values->size();
    size_t boardIndex = 0;
    for (size_t i = 2; i < len; i += 6) {
        board b;
        for (size_t j = 0; j < 5; j++) {
            auto numberLine = parse::getIntegers(values->at(i + j));
            for (size_t n = 0; n < 5; n++) {
                b.numbers[j][n] = numberLine[n];
                b.picked[j][n]  = false;
            }
        }
        boardIndex++;
        boards->push_back(b);
    }
}

std::string findSolution1(std::vector<std::string> *numbers,
                          std::vector<board> *boards)
{
    size_t boardIndex = 0;
    for (auto &num : *numbers) {
        uint64_t number = std::stoull(num);
        for (boardIndex = 0; boardIndex < boards->size(); ++boardIndex) {
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    if (boards->at(boardIndex).numbers[i][j] == number) {
                        boards->at(boardIndex).picked[i][j] = true;
                    }
                }
            }
            if (boards->at(boardIndex).isSolved()) {
                return std::to_string(boards->at(boardIndex).sumNotCalled() *
                                      number);
            }
        }
    }

    return std::to_string(0);
}

std::string findSolution2(std::vector<std::string> *numbers,
                          std::vector<board> *boards)
{
    std::set<uint64_t> remaining;
    auto len          = boards->size();
    size_t boardIndex = 0;
    for (boardIndex = 0; boardIndex < len; ++boardIndex) {
        remaining.emplace(boardIndex);
    }
    assert(remaining.size() == len);
    for (auto &num : *numbers) {
        uint64_t number = std::stoull(num);
        for (boardIndex = 0; boardIndex < len; ++boardIndex) {
            for (size_t i = 0; i < 5; i++) {
                for (size_t j = 0; j < 5; j++) {
                    if (boards->at(boardIndex).numbers[i][j] == number) {
                        boards->at(boardIndex).picked[i][j] = true;
                    }
                }
            }
        }
        if (remaining.size() > 1) {
            for (boardIndex = 0; boardIndex < len; ++boardIndex) {
                if (boards->at(boardIndex).isSolved()) {
                    auto it = remaining.find(boardIndex);
                    if (it != remaining.end()) {
                        remaining.erase(it);
                    }
                }
            }
        } else {
            if (boards->at(*remaining.begin()).isSolved()) {
                return std::to_string(
                    boards->at(*remaining.begin()).sumNotCalled() * number);
            }
        }
    }

    return std::to_string(0);
}

std::string process1(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    auto numbers = parse::split(valueList[0], ',');
    std::vector<board> boards;
    populateBoards(&valueList, &boards);

    std::string result = findSolution1(&numbers, &boards);
    return result;
}

std::string process2(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    auto numbers = parse::split(valueList[0], ',');
    std::vector<board> boards;
    populateBoards(&valueList, &boards);

    std::string result = findSolution2(&numbers, &boards);
    return result;
}
