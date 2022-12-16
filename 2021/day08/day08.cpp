/**
 * @file    day08.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    08 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day08.h"

#include "common.h"

#include <bitset>

constexpr size_t SEGMENTS_SIZE = 7;
typedef std::bitset<SEGMENTS_SIZE> Segment;
constexpr size_t DIGITS_SIZE = 10;
constexpr size_t SECOND_SIZE = 4;

struct Entry {
    std::array<std::string, DIGITS_SIZE> first;
    std::array<std::string, SECOND_SIZE> second;
};

uint64_t analyze1(Entry *entry)
{
    uint64_t count = 0;
    for (size_t i = 0; i < SECOND_SIZE; ++i) {
        auto size = entry->second[i].size();
        // 1 4 7 8
        if (size == 2 || size == 4 || size == 3 || size == 7) {
            count++;
        }
    }
    return count;
}

Segment combine(std::string &input)
{
    Segment res;
    for (auto& c : input) {
        res.set(c - 'a', 1);
    }
    return res;
}

uint64_t converts(std::array<Segment, SEGMENTS_SIZE> &possiblesMapping, Entry *entry)
{
    /* 0: 012 456   */
    /* 1:   2  5    */
    /* 2: 0 234 6   */
    /* 3: 0 23 56   */
    /* 4:  123 5    */
    /* 5: 01 3 56   */
    /* 6: 01 3456   */
    /* 7: 0 2  5    */
    /* 8: 0123456   */
    /* 9: 0123 56    */
    std::array<Segment, DIGITS_SIZE> converter = {
        possiblesMapping[0] | possiblesMapping[1] | possiblesMapping[2] | possiblesMapping[4] | possiblesMapping[5] |
            possiblesMapping[6],
        possiblesMapping[2] | possiblesMapping[5],
        possiblesMapping[0] | possiblesMapping[2] | possiblesMapping[3] | possiblesMapping[4] | possiblesMapping[6],
        possiblesMapping[0] | possiblesMapping[2] | possiblesMapping[3] | possiblesMapping[5] | possiblesMapping[6],
        possiblesMapping[1] | possiblesMapping[2] | possiblesMapping[3] | possiblesMapping[5],
        possiblesMapping[0] | possiblesMapping[1] | possiblesMapping[3] | possiblesMapping[5] | possiblesMapping[6],
        possiblesMapping[0] | possiblesMapping[1] | possiblesMapping[3] | possiblesMapping[4] | possiblesMapping[5] |
            possiblesMapping[6],
        possiblesMapping[0] | possiblesMapping[2] | possiblesMapping[5],
        possiblesMapping[0] | possiblesMapping[1] | possiblesMapping[2] | possiblesMapping[3] | possiblesMapping[4] |
            possiblesMapping[5] | possiblesMapping[6],
        possiblesMapping[0] | possiblesMapping[1] | possiblesMapping[2] | possiblesMapping[3] | possiblesMapping[5] |
            possiblesMapping[6],
    };

    uint64_t result = 0;
    // All solutions done, return the 4 number value
    for (size_t i = 0; i < SECOND_SIZE; i++) {
        result *= 10;
        auto segment = combine(entry->second[i]);
        for (size_t j = 0; j < DIGITS_SIZE; j++) {
            if (segment == converter[j]) {
                result += j;
                break;
            }
        }
    }
    return result;
}

uint64_t analyze2(Entry *entry)
{
    // i : [0-6] => possiblesMapping[i] is the possible letters assigned to i^ segment
    std::array<Segment, SEGMENTS_SIZE> possiblesMapping;
    for (size_t i = 0; i < SEGMENTS_SIZE; i++) {
        possiblesMapping[i] = ~possiblesMapping[i];
    }

    std::array<int, DIGITS_SIZE + SECOND_SIZE> solutions;

    // Populate possible mapping
    for (size_t i = 0; i < DIGITS_SIZE; i++) {
        solutions[i] = -1;
        auto size = entry->first[i].size();
        auto segment = combine(entry->first[i]);
        switch (size) {
            case (2):
                solutions[i] = 1;
                possiblesMapping[2] = segment;
                possiblesMapping[5] = segment;
                break;
            case (3):
                solutions[i] = 7;
                possiblesMapping[0] = segment;
                break;
            case (4):
                solutions[i] = 4;
                possiblesMapping[1] = segment;
                possiblesMapping[3] = segment;
                break;
            case (7):
                solutions[i] = 8;
                // All mapping
                break;
        }
    }

    // Apply rules
    for (size_t i = 0; i < SEGMENTS_SIZE; ++i) {
        // Rule: number 1 can remove his segment from othes
        if (i != 2 && i != 5) {
            possiblesMapping[i] &= ~(possiblesMapping[2]);
        }
    }
    // Rule: number 7 can remove his segment from othes
    possiblesMapping[4] &= ~(possiblesMapping[0]);
    possiblesMapping[6] &= ~(possiblesMapping[0]);
    // Rule: number 4 can remove his segment from othes
    possiblesMapping[4] &= ~(possiblesMapping[3]);
    possiblesMapping[6] &= ~(possiblesMapping[3]);

    // Find 6 and 3
    for (size_t i = 0; i < DIGITS_SIZE; i++) {
        if (solutions[i] == -1) {
            auto segment = combine(entry->first[i]);
            // Remove the 1's segments
            segment &= ~(possiblesMapping[2]);
            auto count = segment.count();
            switch (count) {
                case (5):
                    solutions[i] = 6;
                    break;
                case (3):
                    solutions[i] = 3;
                    possiblesMapping[3] &= segment;
                    possiblesMapping[6] &= segment;
                    break;
            }
        }
    }

    // Find 0
    for (size_t i = 0; i < DIGITS_SIZE; i++) {
        if (solutions[i] == -1) {
            auto segment = combine(entry->first[i]);
            // Check the d segment
            segment &= possiblesMapping[3];
            if (segment.count() == 0) {
                solutions[i] = 0;
            }
        }
    }

    // Find 9
    for (size_t i = 0; i < DIGITS_SIZE; i++) {
        if (solutions[i] == -1) {
            if (entry->first[i].size() == 6) {
                solutions[i] = 9;
                auto segment = combine(entry->first[i]);
                // Remove the 3's segments
                segment &= ~(possiblesMapping[0] | possiblesMapping[2] | possiblesMapping[3] | possiblesMapping[6]);
                possiblesMapping[1] &= segment;
            }
        }
    }

    // Find 2 and 5
    for (size_t i = 0; i < DIGITS_SIZE; i++) {
        if (solutions[i] == -1) {
            auto segment = combine(entry->first[i]);
            // Check the b segment
            auto filter = segment & possiblesMapping[1];
            if (filter.count() == 0) {
                solutions[i] = 5;
                possiblesMapping[2] &= segment;
            } else {
                solutions[i] = 2;
                possiblesMapping[5] &= segment;
            }
        }
    }

    return converts(possiblesMapping, entry);
}

uint64_t analyze2bis(Entry *entry)
{
    std::string four;
    std::array<int, SEGMENTS_SIZE> segment_frequency = { 0, 0, 0, 0, 0, 0, 0 };
    for (size_t i = 0; i < DIGITS_SIZE; i++) {
        for (auto c : entry->first[i]) {
            segment_frequency[c - 'a']++;
        }
        if (entry->first[i].size() == 4) {
            four = entry->first[i];
        }
    }

    std::array<Segment, SEGMENTS_SIZE> possiblesMapping;

    /*
    a: 02356789     8
    b: 045689       6
    c: 01346789     8
    d: 2345689      7
    e: 0268         4
    f: 013456789    9
    g: 0235689      7
    */

    for (size_t i = 0; i < SEGMENTS_SIZE; i++) {
        switch (segment_frequency[i]) {
            case 9:
                // 'a' + i is f
                possiblesMapping[5].set(i);
                break;
            case 8:
                // 'a' + i is a or c
                if (four.find('a' + i) != std::string::npos) {
                    // is c
                    possiblesMapping[2].set(i);
                } else {
                    // is a
                    possiblesMapping[0].set(i);
                }
                break;
            case 7:
                // 'a' + i is d or g
                if (four.find('a' + i) != std::string::npos) {
                    // is d
                    possiblesMapping[3].set(i);
                } else {
                    // is g
                    possiblesMapping[6].set(i);
                }
                break;
            case 6:
                // 'a' + i is b
                possiblesMapping[1].set(i);
                break;
            case 4:
                // 'a' + i is e
                possiblesMapping[4].set(i);
                break;
        }
    }

    return converts(possiblesMapping, entry);
}

void populateEntry(std::string &line, Entry *entry)
{
    auto parts = parse::split(line, '|');
    auto firstPart = parse::split(parts[0], ' ');
    for (size_t i = 0; i < DIGITS_SIZE; i++) {
        entry->first[i] = firstPart[i];
    }
    auto secondPart = parse::split(parts[1], ' ');
    for (size_t i = 0; i < SECOND_SIZE; i++) {
        entry->second[i] = secondPart[i + 1];
    }
}

uint64_t convertInput1(std::string line)
{
    Entry entry;
    populateEntry(line, &entry);
    return analyze1(&entry);
}

uint64_t convertInput2(std::string line)
{
    Entry entry;
    populateEntry(line, &entry);
    return analyze2bis(&entry);
}

void sum(uint64_t value, uint64_t *total)
{
    *total = value + *total;
}

std::string day08::process1(std::string file)
{
    uint64_t value = 0;
    parse::read<uint64_t, uint64_t *>(file, '\n', convertInput1, sum, &value);
    return std::to_string(value);
}

std::string day08::process2(std::string file)
{
    uint64_t value = 0;
    parse::read<uint64_t, uint64_t *>(file, '\n', convertInput2, sum, &value);
    return std::to_string(value);
}
