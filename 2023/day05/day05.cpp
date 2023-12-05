/**
 * @file    day05.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    05 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day05.h"

#include "common.h"

#include <algorithm>
#include <queue>

struct Conversion {
    Conversion(std::vector<uint64_t> numbers) : dest(numbers[0]), source(numbers[1]), range(numbers[2]){};
    uint64_t dest = 0;
    uint64_t source = 0;
    uint64_t range = 0;

    uint64_t convert(uint64_t value)
    {
        auto diff = value - source;
        return dest + diff;
    }
};

typedef std::vector<Conversion> Map;

struct SeedMap {
    SeedMap(const std::string &inputFilename);

    uint64_t getMinimum();
    uint64_t getMinimumRange();

    std::vector<uint64_t> seeds;
    std::vector<Map> maps;
};

SeedMap::SeedMap(const std::string &inputFilename)
{
    std::ifstream source;
    source.open(inputFilename);
    std::string part;

    Map map;
    bool firstLine = true;
    while (std::getline(source, part, '\n')) {
        if (firstLine) {
            seeds = parse::getIntegers(part);
            firstLine = false;
        } else {
            if (part != "") {
                if (part[0] >= '0' && part[0] <= '9') {
                    Conversion conversion(parse::getIntegers(part));
                    map.push_back(std::move(conversion));
                } // else Skip descriptions
            } else {
                // New map
                if (!map.empty()) {
                    // Avoid to add empty map from "\n\n" after seeds
                    maps.push_back(std::move(map));
                    map.clear();
                }
            }
        }
    }

    maps.push_back(std::move(map));
    map.clear();
}

uint64_t SeedMap::getMinimum()
{
    std::vector<uint64_t> results;
    for (auto &&seed : seeds) {
        auto current = seed;
        for (auto &&map : maps) {
            for (auto &&conversion : map) {
                if (current >= conversion.source && current <= conversion.source + conversion.range) {
                    current = conversion.dest + (current - conversion.source);
                    break;
                }
            }
        }
        results.push_back(current);
    }

    auto minValue = std::min_element(results.begin(), results.end());
    return *minValue;
}

bool applyConversion(op::Range &current, Conversion &conversion, std::queue<op::Range> &currents,
                     std::queue<op::Range> &nextCurrents)
{
    op::Range conversionRange = { conversion.source, conversion.range };
    auto splitRes = op::split(current, conversionRange);
    switch (splitRes.size()) {
        case 0:
            // not found
            break;
        case 1:
            // Interaly contained
            nextCurrents.emplace(op::Range{ conversion.convert(splitRes[0].from), splitRes[0].len });
            break;
        case 2: {
            // Two possible case
            auto conversionLast = conversion.source + conversion.range - 1;
            if (current.from >= conversion.source && current.from <= conversionLast) {
                // Seed is in conversion
                nextCurrents.emplace(op::Range{ conversion.convert(splitRes[0].from), splitRes[0].len });
                currents.emplace(splitRes[1]);
            } else {
                // Conversion is in seed
                currents.emplace(splitRes[0]);
                nextCurrents.emplace(op::Range{ conversion.convert(splitRes[1].from), splitRes[1].len });
            }
            break;
        }
        case 3:
            // Conversion interaly contained in seed
            currents.emplace(splitRes[0]);
            nextCurrents.emplace(op::Range{ conversion.convert(splitRes[1].from), splitRes[1].len });
            currents.emplace(splitRes[2]);
            break;
    }
    if (splitRes.size() > 0) {
        return true;
    }
    return false;
}

uint64_t SeedMap::getMinimumRange()
{
    std::vector<uint64_t> results;
    for (int i = 0, n = seeds.size(); i < n - 1; i = i + 2) {
        auto seed = seeds[i];
        auto range = seeds[i + 1];
        std::queue<op::Range> currents;
        currents.emplace(op::Range{ seed, range });

        for (auto &&map : maps) {
            std::queue<op::Range> nextCurrents;

            while (!currents.empty()) {
                auto current = currents.front();
                currents.pop();
                bool found = false;
                for (auto &&conversion : map) {
                    found = applyConversion(current, conversion, currents, nextCurrents);
                    if (found) {
                        break;
                    }
                }
                if (!found) {
                    nextCurrents.emplace(current);
                }
            }

            // All currents processed, pass to nextCurrents
            currents.swap(nextCurrents);
        }

        uint64_t minCurrent = currents.front().from;
        while (!currents.empty()) {
            auto c = currents.front();
            currents.pop();
            if (c.from < minCurrent) {
                minCurrent = c.from;
            }
        }
        results.push_back(minCurrent);
    }

    auto minValue = std::min_element(results.begin(), results.end());
    return *minValue;
}

std::string day05::process1(std::string file)
{
    SeedMap seedmap(file);
    auto result = seedmap.getMinimum();
    return std::to_string(result);
}

std::string day05::process2(std::string file)
{
    SeedMap seedmap(file);
    auto result = seedmap.getMinimumRange();
    return std::to_string(result);
}