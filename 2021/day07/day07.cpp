/**
 * @file    day07.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    07 Dec 2021
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

#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>

struct whitespaces : std::ctype<char> {
    static const mask *make_table()
    {
        static std::vector<mask> v(classic_table(), classic_table() + table_size);
        v[','] |= space;
        return &v[0];
    }
    whitespaces(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};

std::string day07::process1(std::string file)
{
    std::ifstream in(file);
    in.imbue(std::locale(in.getloc(), new whitespaces));

    std::vector<int> values;
    int value;
    while (in >> value) {
        values.push_back(value);
    }
    std::sort(values.begin(), values.end());
    auto median       = values[values.size() / 2];
    uint64_t solution = std::accumulate(values.begin(), values.end(), 0ull,
                                        [&](uint64_t sum, int val) { return sum + std::abs(val - median); });

    return std::to_string(solution);
}

std::string day07::process2(std::string file)
{
    std::ifstream in(file);
    in.imbue(std::locale(in.getloc(), new whitespaces));

    std::vector<int> values;
    int value;
    while (in >> value) {
        values.push_back(value);
    }
    uint64_t total =
        std::accumulate(values.begin(), values.end(), 0ull, [&](uint64_t sum, int val) { return sum + val; });

    int64_t mediaVal = total / values.size();

    auto solutor = [&](int64_t media) -> uint64_t {
        auto lambda = [&](uint64_t sum, int val) {
            uint64_t diff = std::abs(media - val);
            return sum + (diff * (diff + 1)) / 2;
        };
        return (uint64_t)std::accumulate(values.begin(), values.end(), 0ull, lambda);
    };
    uint64_t solutionA = solutor(mediaVal);
    uint64_t solutionB = solutor(mediaVal + 1);

    return std::to_string(solutionA < solutionB ? solutionA : solutionB);
}
