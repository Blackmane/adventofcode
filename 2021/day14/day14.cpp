/**
 * @file    day14.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    14 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day14.h"

#include "common.h"

#include <list>
#include <map>

struct Polymer {
    std::string templ;
    std::map<std::pair<char, char>, char> rules;
    bool changed = false;
};

typedef std::map<char, uint64_t> Occurrences;

void convertInput(Polymer *polymer, std::string line)
{
    if (line.empty()) {
        polymer->changed = true;
        return;
    }
    if (!polymer->changed) {
        polymer->templ = line;
    } else {
        polymer->rules.insert(std::make_pair(std::make_pair(line[0], line[1]), line[6]));
    }
}

uint64_t differenceMaxMin(Occurrences * occurrences) {
    uint64_t max = 0;
    uint64_t min = -1;
    for (auto &o : *occurrences) {
        if (o.second > max) {
            max = o.second;
        }
        if (o.second < min) {
            min = o.second;
        }
    }
    return max - min;
}

std::string polymerization(std::string templ, std::map<std::pair<char, char>, char> *rules)
{
    std::string res;
    size_t n = templ.size();
    for (size_t i = 0; i < n - 1; ++i) {
        res.push_back(templ[i]);
        auto it = rules->find(std::make_pair(templ[i], templ[i + 1]));
        if (it != rules->end()) {
            res.push_back(it->second);
        }
    }
    res.push_back(templ[n - 1]);

    return res;
}

uint64_t findSolution1(Polymer *polymer, size_t n)
{
    std::string currentTemplate = polymer->templ;
    for (size_t i = 0; i < n; ++i) {
        currentTemplate = polymerization(currentTemplate, &polymer->rules);
    }
    Occurrences occurrences;
    for (auto &c : currentTemplate) {
        auto it = occurrences.find(c);
        if (it == occurrences.end()) {
            occurrences.insert(std::make_pair(c, 1));
        } else {
            it->second++;
        }
    }
    return differenceMaxMin(&occurrences);
}

typedef std::map<std::pair<char, char>, uint64_t> Frequency;

uint64_t findSolution2(Polymer *polymer, size_t n)
{
    // Init
    Frequency frequency;
    Occurrences occurrences;
    size_t len = polymer->templ.size();
    for (size_t i = 0; i < len - 1; ++i) {
        auto couple = std::make_pair(polymer->templ[i], polymer->templ[i + 1]);
        op::increaseOrInsert<std::pair<char, char>, uint64_t> (&frequency, couple, 1);
        op::increaseOrInsert<char, uint64_t> (&occurrences, polymer->templ[i], 1);
    }
    op::increaseOrInsert<char, uint64_t> (&occurrences, polymer->templ[len-1], 1);

    // Steps
    for (size_t i = 0; i < n; ++i) {
        Frequency newFrequency;
        for (auto &f : frequency) {
            // For each couple cherck exists a rule
            auto it = polymer->rules.find(f.first);
            if (it != polymer->rules.end()) {
                // If rule exists change the two frequency
                auto c = it->second;
                op::increaseOrInsert<std::pair<char, char>, uint64_t> (&newFrequency, std::make_pair(it->first.first, c), f.second);
                op::increaseOrInsert<std::pair<char, char>, uint64_t> (&newFrequency, std::make_pair(c, it->first.second), f.second);
                // The new char increase his occurrences
                op::increaseOrInsert<char, uint64_t> (&occurrences, c, f.second);
            }
        }
        frequency = newFrequency;
    }
    return differenceMaxMin(&occurrences);
}

std::string day14::process1(std::string file)
{
    Polymer polymer;
    parse::read<Polymer *>(file, '\n', convertInput, &polymer);
    auto res = findSolution1(&polymer, 10);
    return std::to_string(res);
}

std::string day14::process2(std::string file)
{
    Polymer polymer;
    parse::read<Polymer *>(file, '\n', convertInput, &polymer);
    auto res = findSolution2(&polymer, 40);
    return std::to_string(res);
}