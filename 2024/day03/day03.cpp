/**
 * @file    day03.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    03 Dec 2024
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

#include <regex>

std::string day03::process1(std::string file)
{
    std::vector<std::string> lines;
    parse::read_all(file, &lines);

    std::regex exp("mul\\(\\d+,\\d+\\)");
    std::smatch match;

    int64_t result = 0;
    for (auto &&line : lines) {
        std::string::const_iterator searchStart(line.cbegin());
        while (std::regex_search(searchStart, line.cend(), match, exp)) {
            auto part = std::string(match[0]).substr(4, match[0].length() - 4 - 1);
            auto numbers = parse::split(part, ',');
            auto values = parse::getIntegers(match[0]);
            result += std::stoi(numbers[0]) * std::stoi(numbers[1]);
            searchStart = match.suffix().first;
        }
    }

    return std::to_string(result);
}

std::string day03::process2(std::string file)
{
    std::vector<std::string> lines;
    parse::read_all(file, &lines);

    std::regex exp("mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\)");
    std::smatch match;

    bool enabled = true;
    int64_t result = 0;
    for (auto &&line : lines) {
        std::string::const_iterator searchStart(line.cbegin());
        while (std::regex_search(searchStart, line.cend(), match, exp)) {
            if (match[0] == "do()") {
                enabled = true;
            } else if (match[0] == "don't()") {
                enabled = false;
            } else if (enabled) {
                auto part = std::string(match[0]).substr(4, match[0].length() - 4 - 1);
                auto numbers = parse::split(part, ',');
                auto values = parse::getIntegers(match[0]);
                result += std::stoi(numbers[0]) * std::stoi(numbers[1]);
            }
            searchStart = match.suffix().first;
        }
    }

    return std::to_string(result);
}