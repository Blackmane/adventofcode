/**
 * @file    day21.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    20 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day21.h"

#include "common.h"

#include <queue>

const std::string ROOT("root");
const std::string HUMAN("humn");

struct Monkey {
    std::string name;
    bool validValue = false;
    int64_t value = 0;
    std::string subMonkey1;
    std::string subMonkey2;
    char op;
};

void insert(std::map<std::string, Monkey> *monkeys, std::string line)
{
    Monkey monkey;
    monkey.name = line.substr(0, 4);
    if (line[6] >= '0' && line[6] <= '9') {
        monkey.value = std::stoi(line.substr(6, line.size() - 6));
        monkey.validValue = true;
    } else {
        monkey.subMonkey1 = line.substr(6, 4);
        monkey.op = line[11];
        monkey.subMonkey2 = line.substr(13, 4);
    }
    monkeys->insert(std::make_pair(monkey.name, std::move(monkey)));
}

uint64_t searchSolution(std::map<std::string, Monkey> &monkeys)
{
    std::queue<std::string> visit;
    for (auto &&m : monkeys) {
        if (!m.second.validValue) {
            visit.push(m.first);
        }
    }
    while (!visit.empty()) {
        auto curName = visit.front();
        visit.pop();
        auto &cur = monkeys[curName];

        if (cur.validValue) {
            continue;
        }

        auto &m1 = monkeys[cur.subMonkey1];
        auto &m2 = monkeys[cur.subMonkey2];
        if (m1.validValue && m2.validValue) {
            switch (cur.op) {
                case '+':
                    cur.value = m1.value + m2.value;
                    break;
                case '-':
                    cur.value = m1.value - m2.value;
                    break;
                case '*':
                    cur.value = m1.value * m2.value;
                    break;
                case '/':
                    cur.value = m1.value / m2.value;
                    break;
                default:
                    break;
            }
            cur.validValue = true;
            if (curName == ROOT) {
                break;
            }
        } else {
            visit.push(curName);
        }
    }

    return monkeys[ROOT].value;
}

uint64_t partial(std::map<std::string, Monkey> &monkeys, const std::string &from)
{
    std::set<std::string> waiting;
    std::queue<std::string> visit;
    visit.push(from);

    while (!visit.empty()) {
        auto curName = visit.front();
        visit.pop();
        auto &cur = monkeys[curName];

        if (cur.validValue) {
            continue;
        }

        auto &m1 = monkeys[cur.subMonkey1];
        auto &m2 = monkeys[cur.subMonkey2];
        if (m1.validValue && m2.validValue) {
            switch (cur.op) {
                case '+':
                    cur.value = m1.value + m2.value;
                    break;
                case '-':
                    cur.value = m1.value - m2.value;
                    break;
                case '*':
                    cur.value = m1.value * m2.value;
                    break;
                case '/':
                    cur.value = m1.value / m2.value;
                    break;
                default:
                    break;
            }
            cur.validValue = true;
            if (curName == from) {
                return cur.value;
            }
        } else {
            if (waiting.count(curName) == 0) {
                if (!m1.validValue) {
                    visit.push(cur.subMonkey1);
                }
                if (!m2.validValue) {
                    visit.push(cur.subMonkey2);
                }
                waiting.insert(curName);
            }
            visit.push(curName);
        }
    }
    return monkeys[from].value;
}

int64_t getTarget(std::map<std::string, Monkey> &monkeys, const std::set<std::string> &depends, std::string name,
                  int64_t target)
{
    if (name == HUMAN) {
        return target;
    }

    auto &cur = monkeys[name];
    if (depends.find(cur.subMonkey1) != depends.end()) {
        auto value = partial(monkeys, cur.subMonkey2);
        int64_t newTarget = 0;
        switch (cur.op) {
            case '+':
                newTarget = target - value;
                break;
            case '-':
                newTarget = target + value;
                break;
            case '*':
                newTarget = target / value;
                break;
            case '/':
                newTarget = target * value;
                break;
            default:
                break;
        }
        return getTarget(monkeys, depends, cur.subMonkey1, newTarget);
    }
    if (depends.find(cur.subMonkey2) != depends.end()) {
        auto value = partial(monkeys, cur.subMonkey1);
        int64_t newTarget = 0;
        switch (cur.op) {
            case '+':
                newTarget = target - value;
                break;
            case '-':
                newTarget = value - target;
                break;
            case '*':
                newTarget = target / value;
                break;
            case '/':
                newTarget = value / target;
                break;
            default:
                break;
        }
        return getTarget(monkeys, depends, cur.subMonkey2, newTarget);
    }
    return 0;
}

uint64_t searchSolution2(std::map<std::string, Monkey> &monkeys)
{
    std::map<std::string, std::set<std::string>> dependencies;
    std::set<std::string> emptySet;
    for (auto &&m : monkeys) {
        dependencies.insert(std::make_pair(m.first, emptySet));
    }
    for (auto &&m : monkeys) {
        if (!m.second.validValue) {
            dependencies[m.second.subMonkey1].insert(m.first);
            dependencies[m.second.subMonkey2].insert(m.first);
        }
    }
    std::set<std::string> depends;
    depends.insert(HUMAN);
    std::queue<std::string> visit;
    visit.push(HUMAN);
    while (!visit.empty()) {
        auto curName = visit.front();
        visit.pop();
        for (auto &&p : dependencies[curName]) {
            visit.push(p);
            depends.insert(p);
        }
    }

    auto &root = monkeys[ROOT];
    bool isLeft = depends.count(root.subMonkey1) > 0;
    if (isLeft) {
        auto target = partial(monkeys, root.subMonkey2);
        return getTarget(monkeys, depends, root.subMonkey1, target);
    } else {
        auto target = partial(monkeys, root.subMonkey1);
        return getTarget(monkeys, depends, root.subMonkey2, target);
    }
}

std::string day21::process1(std::string file)
{
    std::map<std::string, Monkey> monkeys;
    parse::read<std::map<std::string, Monkey> *>(file, '\n', insert, &monkeys);
    auto result = searchSolution(monkeys);
    return std::to_string(result);
}

std::string day21::process2(std::string file)
{
    std::map<std::string, Monkey> monkeys;
    parse::read<std::map<std::string, Monkey> *>(file, '\n', insert, &monkeys);
    auto result = searchSolution2(monkeys);
    return std::to_string(result);
}