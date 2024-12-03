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

// Use both the approaches, one with std::regex and one with parse::Regex
std::string day03::process1(std::string file)
{
    std::regex exp{ "mul\\((\\d+),(\\d+)\\)" };
    std::smatch match;

    int64_t result = 0;
    parse::read<int64_t *>(
        file, '\n',
        [&](int64_t *, const std::string &line) {
            std::string::const_iterator searchStart(line.cbegin());
            while (std::regex_search(searchStart, line.cend(), match, exp)) {
                result += std::stoi(match[1]) * std::stoi(match[2]);
                searchStart = match.suffix().first;
            }
        },
        &result);

    return std::to_string(result);
}

std::string day03::process2(std::string file)
{
    parse::Regex r("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");

    bool enabled = true;
    int64_t result = 0;
    auto apply = [&](std::smatch &match) {
        if (match[0] == "do()") {
            enabled = true;
        } else if (match[0] == "don't()") {
            enabled = false;
        } else if (enabled) {
            result += std::stoi(match[1]) * std::stoi(match[2]);
        }
    };

    parse::read<int64_t *>(file, '\n', [&](int64_t *, const std::string &line) { r.search(line, apply); }, &result);

    return std::to_string(result);
}