/**
 * @file    day07.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    07 Dec 2023
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
#include <set>

enum Type { Five_kind = 0, Four_kind = 1, Full_house = 2, Three_kind = 3, Two_pair = 4, One_pair = 5, High_card = 6 };

std::string cards = { "AKQJT98765432" };
std::string cards2 = { "AKQT98765432J" };

struct Hand {
    std::string hand;
    Type type;
    uint64_t bid;
    Hand(const std::string &line, bool part2 = false);
    Type setType();
    Type setTypeJ();
};

Type Hand::setType()
{
    std::multiset<char> groups;
    for (auto c : hand) {
        groups.insert(c);
    }
    int size = 0;
    for (auto each = groups.begin(); each != groups.end(); each = groups.upper_bound(*each)) {
        size++;
    }
    switch (size) {
        case 1:
            return Type::Five_kind;
        case 2: {
            auto count = groups.count(hand[0]);
            if (count == 3 || count == 2) {
                return Type::Full_house;
            } else {
                return Type::Four_kind;
            }
        }
        case 3: {
            for (auto card : hand) {
                auto count = groups.count(card);
                if (count == 3) {
                    return Type::Three_kind;
                }
                if (count == 2) {
                    return Type::Two_pair;
                }
            }
            break;
        }
        case 4:
            return Type::One_pair;

        case 5:
            return Type::High_card;
    }
    return Type::High_card;
}

Type Hand::setTypeJ()
{
    int jCount = 0;
    std::multiset<char> groups;
    for (auto c : hand) {
        if (c != 'J') {
            groups.insert(c);
        } else {
            jCount++;
        }
    }
    if (jCount == 5 || jCount == 4) {
        return Type::Five_kind;
    }
    int size = 0;
    for (auto each = groups.begin(); each != groups.end(); each = groups.upper_bound(*each)) {
        size++;
    }
    switch (size) {
        case 2: {
            // AA B JJ
            // A B JJJ
            if (jCount == 3 || jCount == 2) {
                return Type::Four_kind;
            }
            // AA BB J
            // AAA B J
            for (auto card : hand) {
                auto count = groups.count(card);
                if (count == 3) {
                    return Type::Four_kind;
                }
                if (count == 2) {
                    return Type::Full_house;
                }
            }
            break;
        }
        case 3: {
            // ABC JJ
            // AABC J
            // ABBC J
            // ABCC J
            return Type::Three_kind;
        }
        case 4:
            // ABCD J
            return Type::One_pair;
    }
    return Type::High_card;
}

Hand::Hand(const std::string &line, bool part2)
{
    auto parts = parse::split(line, ' ');
    hand = parts[0];
    bid = std::stol(parts[1]);

    bool jFound = std::find_if(hand.begin(), hand.end(), [](char c) { return c == 'J'; }) != hand.end();
    if (part2 && jFound) {
        type = setTypeJ();
    } else {
        type = setType();
    }
}

bool order(Hand a, Hand b)
{
    if (a.type == b.type) {
        for (int i = 0, n = a.hand.size(); i < n; i++) {
            if (a.hand[i] != b.hand[i]) {
                return cards.find(a.hand[i], 0) > cards.find(b.hand[i], 0);
            }
        }
    }
    return a.type > b.type;
}

std::string process(std::string file, bool part2 = false)
{
    std::vector<Hand> hands;
    parse::read<std::vector<Hand> *>(
        file, '\n',
        [part2](std::vector<Hand> *hand_list, const std::string &line) { hand_list->push_back(Hand(line, part2)); },
        &hands);

    if (part2) {
        cards.swap(cards2);
    }
    std::sort(hands.begin(), hands.end(), order);
    uint64_t winning = 0;
    for (int i = 0, n = hands.size(); i < n; i++) {
        winning += (i + 1) * hands[i].bid;
    }
    return std::to_string(winning);
}

std::string day07::process1(std::string file)
{
    return process(file, false);
}

std::string day07::process2(std::string file)
{
    return process(file, true);
}
