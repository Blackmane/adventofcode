/**
 * @file    day22.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    22 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day22.h"

#include "common.h"

#include <cmath>
#include <unordered_set>

uint64_t evolve(uint32_t N, int steps)
{
    uint32_t limiter = 16777216 - 1;
    for (int i = 0; i < steps; i++) {
        N = (N ^ (N << 6)) & limiter;
        N = (N ^ (N >> 5)) & limiter;
        N = (N ^ (N << 11)) & limiter;
    }
    return N;
}

void increment(std::unordered_map<uint32_t, int> &map, uint32_t key, int value)
{
    auto it = map.find(key);
    if (it == map.end()) {
        map.insert({ key, value });
    } else {
        it->second += value;
    }
}

std::unordered_map<uint32_t, int> sums;

void evolveSaveSequences(uint32_t N, int steps)
{
    std::unordered_set<uint32_t> seqToBanana;
    seqToBanana.reserve(steps);
    std::vector<std::pair<int, int>> diffs;
    diffs.reserve(steps);

    int prec = 0;
    uint32_t limiter = 16777216 - 1;
    for (int i = 0; i < steps; i++) {
        N = (N ^ (N << 6)) & limiter;
        N = (N ^ (N >> 5)) & limiter;
        N = (N ^ (N << 11)) & limiter;
        int cur = N % 10;
        diffs.push_back({ 9 + cur - prec, cur });
        prec = cur;
    }
    uint32_t seqKey = (diffs[1].first << 10) + (diffs[2].first << 5) + diffs[3].first;
    for (int i = 1, n = diffs.size() - 3; i < n; i++) {
        seqKey = ((seqKey << 5) & (1048576 - 1)) + diffs[i + 3].first;
        if (diffs[i + 3].second != 0 && seqToBanana.count(seqKey) == 0) {
            increment(sums, seqKey, diffs[i + 3].second);
            seqToBanana.insert(seqKey);
        }
    }
}

std::string day22::process1(std::string file)
{
    uint64_t sum = 0;
    parse::read(file, '\n', [&](const std::string &line) {
        uint32_t N = std::stoi(line);
        auto p = evolve(N, 2000);
        sum += p;
    });
    return std::to_string(sum);
}

std::string day22::process2(std::string file)
{
    parse::read(file, '\n', [&](const std::string &line) {
        uint32_t N = std::stoi(line);
        evolveSaveSequences(N, 2000);
    });

    int max = 0;
    for (auto [_, sum] : sums) {
        if (sum > max) {
            max = sum;
        }
    }

    return std::to_string(max);
}
