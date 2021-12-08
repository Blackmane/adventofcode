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

/**
 *  aaaa
 * b    c
 * b    c
 *  dddd
 * e    f
 * e    f
 *  gggg
 */

constexpr size_t SEGMENTS_SIZE = 7;
typedef std::bitset<SEGMENTS_SIZE> Segment;
constexpr size_t DIGITS_SIZE = 10;
constexpr size_t SECOND_SIZE = 4;

struct Entry {
    std::array<std::string, DIGITS_SIZE> first;
    std::array<std::string, SECOND_SIZE> second;
};

void populate(std::vector<std::string> *input, std::vector<Entry> *entries)
{
    for (auto &line : *input) {
        auto parts = parse::split(line, '|');
        Entry entry;
        auto firstPart = parse::split(parts[0], ' ');
        for (size_t i = 0; i < DIGITS_SIZE; i++) {
            entry.first[i] = firstPart[i];
        }
        auto secondPart = parse::split(parts[1], ' ');
        for (size_t i = 0; i < SECOND_SIZE; i++) {
            entry.second[i] = secondPart[i + 1];
        }
        entries->push_back(entry);
    }
}

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

Segment combine(std::string input)
{
    Segment res;
    for (auto c : input) {
        int pos = c - 'a';
        res.set(pos, 1);
    }
    return res;
}

uint64_t analyze2(Entry *entry)
{
    // i : [0-6] => possiblesMapping[i] is the possible letters assigned to i^ segment
    /**
     * possiblesMapping: init
     * a: abcdefg
     * b: abcdefg
     * c: abcdefg
     * d: abcdefg
     * e: abcdefg
     * f: abcdefg
     * g: abcdefg
     */
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

    /**
     * possiblesMapping: populated
     * a: abc
     * b: abde
     * c: ab
     * d: abde
     * e: abcdefg
     * f: ab
     * g: abcdefg
     */

    // Apply rules
    for (size_t i = 0; i < SEGMENTS_SIZE; ++i) {
        // Rule: number 1 can remove his segment from othes
        if (i != 2 && i != 5) {
            possiblesMapping[i] &= ~(possiblesMapping[2]);
        }
        // Rule: number 7 can remove his segment from othes
        if (i != 0 && i != 2 && i != 5) {
            possiblesMapping[i] &= ~(possiblesMapping[0]);
            // Vale solo con i = 4 e 6
        }
        // Rule: number 4 can remove his segment from othes
        if (i != 1 && i != 2 && i != 3 && i != 5) {
            possiblesMapping[i] &= ~(possiblesMapping[3]);
            // Vale solo con i = 4 e 6
        }
    }

    /**
     * possiblesMapping: filtered
     * a: c
     * b: de
     * c: ab
     * d: de
     * e: fg
     * f: ab
     * g: fg
     */

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

std::string findSolution1(std::vector<Entry> *entries)
{
    uint64_t sum = 0;
    for (auto &entry : *entries) {
        sum += analyze1(&entry);
    }
    return std::to_string(sum);
}

std::string findSolution2(std::vector<Entry> *entries)
{
    uint64_t sum = 0;
    for (auto &entry : *entries) {
        auto temp = analyze2(&entry);
        sum += temp;
    }
    return std::to_string(sum);
}
/**
 *   0:      1:      2:      3:      4:
 *  aaaa    ....    aaaa    aaaa    ....
 * b    c  .    c  .    c  .    c  b    c
 * b    c  .    c  .    c  .    c  b    c
 *  ....    ....    dddd    dddd    dddd
 * e    f  .    f  e    .  .    f  .    f
 * e    f  .    f  e    .  .    f  .    f
 *  gggg    ....    gggg    gggg    ....
 *
 *   5:      6:      7:      8:      9:
 *  aaaa    aaaa    aaaa    aaaa    aaaa
 * b    .  b    .  .    c  b    c  b    c
 * b    .  b    .  .    c  b    c  b    c
 *  dddd    dddd    ....    dddd    dddd
 * .    f  e    f  .    f  e    f  .    f
 * .    f  e    f  .    f  e    f  .    f
 *  gggg    gggg    ....    gggg    gggg
 */

std::string process1(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    std::vector<Entry> entries;
    populate(&valueList, &entries);

    std::string result = findSolution1(&entries);
    return result;
}

std::string process2(std::string file)
{
    std::vector<std::string> valueList;
    parse::read_all(file, &valueList);
    std::vector<Entry> entries;
    populate(&valueList, &entries);

    std::string result = findSolution2(&entries);
    return result;
}
