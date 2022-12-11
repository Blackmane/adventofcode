/**
 * @file    day11.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    10 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day11.h"

#include "common.h"

class Monkey
{
  public:
    Monkey();
    void readPart(std::string &part);

    // Start data
    std::vector<uint64_t> items;
    bool multiply;
    uint64_t factor;
    uint64_t divisible;
    size_t throwToTrue;
    size_t throwToFalse;
    // Utility data
    uint64_t inspected = 0;
};

class Monkeys
{
  public:
    Monkeys(std::string inputFilename);
    void inspect(size_t rounds, bool divideWorry);
    uint64_t getValue();

    std::vector<Monkey> monkeys;
};

Monkey::Monkey() {}

void Monkey::readPart(std::string &part)
{
    if (part[0] == 'M') {
        return;
    }
    if (part[2] == 'S') {
        items = parse::getIntegers(part);
    }
    if (part[2] == 'O') {
        multiply = part[23] == '*';
        if (part[25] == 'o') {
            factor = 0;
        } else {
            factor = std::stoull(part.substr(25, part.length() - 25));
        }
    }
    if (part[2] == 'T') {
        divisible = std::stoull(part.substr(21, part.length() - 21));
    }

    if (part[2] == ' ') {
        if (part[7] == 't') {
            throwToTrue = std::stoull(part.substr(29, part.length() - 29));
        }
        if (part[7] == 'f') {
            throwToFalse = std::stoull(part.substr(30, part.length() - 30));
        }
    }
}

Monkeys::Monkeys(std::string inputFilename)
{
    std::ifstream source;
    source.open(inputFilename);
    std::string part;

    Monkey monkey;
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            monkey.readPart(part);
        } else {
            // New monkey
            monkeys.push_back(monkey);
            monkey = Monkey();
        }
    }
    monkeys.push_back(monkey);
}

void Monkeys::inspect(size_t rounds, bool divideWorry)
{
    uint64_t modulo = 1;
    for (auto &&m : monkeys) {
        modulo *= m.divisible;
    }

    for (size_t r = 0; r < rounds; ++r) {
        for (auto &&m : monkeys) {
            for (auto item : m.items) {
                m.inspected++;
                uint64_t worry = item;
                if (m.multiply) {
                    if (m.factor == 0) {
                        worry *= worry;
                    } else {
                        worry *= m.factor;
                    }
                } else {
                    worry += m.factor;
                }
                if (divideWorry) {
                    worry /= 3;
                }
                worry = (worry + modulo) % modulo;
                if (worry % m.divisible == 0) {
                    monkeys[m.throwToTrue].items.push_back(worry);
                } else {
                    monkeys[m.throwToFalse].items.push_back(worry);
                }
            }
            m.items.clear();
        }
    }
}

uint64_t Monkeys::getValue()
{
    std::vector<uint64_t> inspected;
    for (auto &&m : monkeys) {
        inspected.push_back(m.inspected);
    }
    std::sort(inspected.begin(), inspected.end());
    auto n = inspected.size();
    return inspected[n - 1] * inspected[n - 2];
}

std::string process1(std::string file)
{
    Monkeys monkeys(file);
    monkeys.inspect(20, true);
    auto result = monkeys.getValue();
    return std::to_string(result);
}

std::string process2(std::string file)
{
    Monkeys monkeys(file);
    monkeys.inspect(10000, false);
    auto result = monkeys.getValue();
    return std::to_string(result);
}
