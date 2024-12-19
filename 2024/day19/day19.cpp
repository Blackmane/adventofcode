/**
 * @file    day19.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    19 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day19.h"

#include "common.h"

bool check(int pos, const std::string &towel, std::set<std::string> &rules)
{
    if (pos >= int(towel.size())) {
        return true;
    }
    char c = towel[pos];
    auto it = rules.find("" + c);
    if (it == rules.end()) {
        it = rules.begin();
    }
    for (; it != rules.end(); it++) {
        bool match = true;
        int n = it->size();
        for (int i = 0; i < n; i++) {
            if (towel[pos + i] != it->at(i)) {
                match = false;
                break;
            }
        }
        if (match) {
            if (check(pos + n, towel, rules)) {
                return true;
            }
        }
    }

    return false;
}

uint64_t countMatch(const std::string &towel, const std::set<std::string> &rules,
                    std::unordered_map<std::string, uint64_t> &cache)
{
    if (towel.empty()) {
        return 1;
    }
    auto cit = cache.find(towel);
    if (cit != cache.end()) {
        return cit->second;
    }

    uint64_t count = 0;
    int tn = towel.size();
    auto it = rules.find("" + towel[0]);
    if (it == rules.end()) {
        it = rules.begin();
    }
    for (; it != rules.end(); it++) {
        bool match = true;
        int n = it->size();
        if (n > tn) {
            continue;
        }
        for (int i = 0; i < n; i++) {
            if (towel[i] != it->at(i)) {
                match = false;
                break;
            }
        }
        if (match) {
            count += countMatch(towel.substr(n, towel.size() - n), rules, cache);
        }
    }
    cache.insert({ towel, count });
    return count;
}

void parseFile(const std::string &file, std::set<std::string> &rules,
               std::function<void(const std::string &)> processTowel)
{
    int count = 0;
    parse::read<int &>(
        file, '\n',
        [&](int &i, const std::string &line) {
            if (i == 0) {
                auto parts = parse::split(line, ',');
                for (auto &part : parts) {
                    if (part[0] == ' ') {
                        rules.insert(part.substr(1, part.size() - 1));
                    } else {
                        rules.insert(part);
                    }
                }
            }
            if (i > 1) {
                processTowel(line);
            }
            i++;
        },
        count);
}

std::string day19::process1(std::string file)
{
    std::set<std::string> rules;
    std::vector<std::string> towels;
    int count = 0;
    parseFile(file, rules, [&](const std::string &towel) { count += check(0, towel, rules) ? 1 : 0; });
    return std::to_string(count);
}

std::string day19::process2(std::string file)
{
    std::set<std::string> rules;
    std::vector<std::string> towels;
    uint64_t count = 0;
    std::unordered_map<std::string, uint64_t> cache;
    parseFile(file, rules, [&](const std::string &towel) { count += countMatch(towel, rules, cache); });
    return std::to_string(count);
}