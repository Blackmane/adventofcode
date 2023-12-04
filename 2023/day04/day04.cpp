/**
 * @file    day04.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    04 Dec 2023
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

struct Card {
    uint64_t id = 0;
    std::vector<uint64_t> winning;
    std::vector<uint64_t> numbers;
    uint64_t count = 1;
};

Card parseCard(std::string line)
{
    Card card;
    auto parts = parse::split(line, '|');
    auto initial = parse::split(parts[0], ':');
    card.numbers = parse::getIntegers(parts[1]);
    card.winning = parse::getIntegers(initial[1]);
    card.id = parse::getInteger(initial[0]);
    return card;
}

void calculate(Card card, uint64_t *sum)
{
    uint64_t match = 0;
    for (auto &w : card.winning) {
        for (auto &n : card.numbers) {
            if (n == w) {
                match++;
            }
        }
    }
    if (match > 0) {
        uint64_t points = 1 << (match - 1);
        *sum += points;
    }
}

void push_back(Card card, std::vector<Card> *cards)
{
    cards->push_back(std::move(card));
}

void calculateWinnings(std ::vector<Card> &cards)
{
    for (auto &&card : cards) {
        uint64_t match = 0;
        for (auto &w : card.winning) {
            for (auto &n : card.numbers) {
                if (n == w) {
                    match++;
                }
            }
        }
        for (uint64_t i = 0; i < match; i++) {
            cards[card.id + i].count += card.count;
        }
    }
}

std::string day04::process1(std::string file)
{
    uint64_t sum = 0;

    parse::read<Card, uint64_t *>(file, '\n', parseCard, calculate, &sum);

    return std::to_string(sum);
}

std::string day04::process2(std::string file)
{
    std::vector<Card> cards;

    parse::read<Card, std::vector<Card> *>(file, '\n', parseCard, push_back, &cards);

    calculateWinnings(cards);

    auto res = 0;
    for (auto &&card : cards) {
        res += card.count;
    }
    return std::to_string(res);
}