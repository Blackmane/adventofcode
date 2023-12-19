/**
 * @file    day19.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    19 Dec 2023
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

struct Rule {
    bool isMin;
    char var;
    int value;
    std::string ifValidJmp;

    Rule(const std::string line)
    {
        auto parts = parse::split(line, ':');
        ifValidJmp = parts[1];
        if (parts[0].find('<', 0) != std::string::npos) {
            isMin = true;
            parts = parse::split(parts[0], '<');
        } else {
            isMin = false;
            parts = parse::split(parts[0], '>');
        }
        var = parts[0][0];
        value = stoi(parts[1]);
    }
};

struct Rating {
    Rating(int x, int m, int a, int s) : values({ x, m, a, s }) {}
    std::array<int, 4> values;
    uint64_t rate()
    {
        return values[0] + values[1] + values[2] + values[3];
    }
};

struct Workflow {
    std::string key;
    std::vector<Rule> rules;
    std::string ifNoValidJmp;
};

struct Input {
    std::unordered_map<std::string, Workflow> workflows;
    std::vector<Rating> ratings;
    bool readWorkflows = true;
};

void insert(Input *input, const std::string &line)
{
    if (line == "") {
        input->readWorkflows = false;
        return;
    }
    if (input->readWorkflows) {
        Workflow workflow;
        auto parts = parse::split(line, '{');
        workflow.key = parts[0];
        parts = parse::split(parts[1], ',');
        int n = parts.size();
        workflow.ifNoValidJmp = parts[n - 1].substr(0, parts[n - 1].size() - 1);
        for (int i = 0; i < n - 1; i++) {
            Rule rule(parts[i]);
            workflow.rules.push_back(rule);
        }
        input->workflows.insert({ workflow.key, workflow });
    } else {
        auto line2 = line;
        std::replace(line2.begin(), line2.end(), '=', ' ');
        auto values = parse::getGenericIntegers<int>(line2);
        Rating rating(values[0], values[1], values[2], values[3]);
        input->ratings.push_back(rating);
    }
}

const std::string XMAS("xmas");

uint64_t apply(Input &input)
{
    uint64_t sum = 0;
    for (auto &rating : input.ratings) {
        std::string cur = "in";
        while (cur != "A" && cur != "R") {
            std::string next;
            for (auto &rule : input.workflows[cur].rules) {
                int idx = XMAS.find(rule.var, 0);
                if (rule.isMin && rating.values[idx] < rule.value) {
                    next = rule.ifValidJmp;
                    break;
                }
                if (!rule.isMin && rating.values[idx] > rule.value) {
                    next = rule.ifValidJmp;
                    break;
                }
            }
            if (next != "") {
                cur = next;
            } else {
                cur = input.workflows[cur].ifNoValidJmp;
            }
        }
        if (cur == "A") {
            sum += rating.rate();
        }
    }
    return sum;
}

struct Range {
    std::array<std::pair<int, int>, 4> ranges = { { { 1, 4000 }, { 1, 4000 }, { 1, 4000 }, { 1, 4000 } } };
    uint64_t product()
    {
        uint64_t val = 1;
        for (size_t i = 0; i < 4; i++) {
            if (ranges[i].first > ranges[i].second) {
                return 0;
            }
            val *= ranges[i].second - ranges[i].first + 1;
        }
        return val;
    }
};

Range intersect(Range a, Range b)
{
    Range res = a;
    for (size_t i = 0; i < 4; i++) {
        res.ranges[i] = { std::max(a.ranges[i].first, b.ranges[i].first),
                          std::min(a.ranges[i].second, b.ranges[i].second) };
    }
    return res;
}

uint64_t countCombines(Input &input)
{
    std::function<uint64_t(const std::string &cur, Range range)> check;
    check = [&](const std::string &cur, Range range) -> uint64_t {
        if (range.product() == 0 || cur == "R") {
            return 0;
        }
        if (cur == "A") {
            return range.product();
        }
        uint64_t sum = 0;
        Range last = range;
        for (auto &rule : input.workflows[cur].rules) {
            int idx = XMAS.find(rule.var, 0);
            Range reduced;
            reduced.ranges[idx] = rule.isMin ? std::make_pair(1, rule.value - 1) : std::make_pair(rule.value + 1, 4000);
            reduced = intersect(reduced, range);
            Range reverse;
            reverse.ranges[idx] = rule.isMin ? std::make_pair(rule.value, 4000) : std::make_pair(1, rule.value);
            reverse = intersect(reverse, range);
            sum += check(rule.ifValidJmp, intersect(last, reduced));
            last = intersect(last, reverse);
        }
        return sum + check(input.workflows[cur].ifNoValidJmp, last);
    };

    Range first;
    return check("in", first);
}

std::string day19::process1(std::string file)
{
    Input input;
    parse::read<Input *>(file, '\n', insert, &input);
    return std::to_string(apply(input));
}

std::string day19::process2(std::string file)
{
    Input input;
    parse::read<Input *>(file, '\n', insert, &input);
    return std::to_string(countCombines(input));
}