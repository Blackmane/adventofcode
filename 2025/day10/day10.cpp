/**
 * @file    day10.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    10 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day10.h"

#include "common.h"

#include <cmath>
#include <queue>

struct MachineLights {
    MachineLights(const std::string &line)
    {
        auto parts = parse::split(line, ' ');
        for (int i = parts[0].size() - 2; i > 0; i--) {
            char c = parts[0][i];
            final <<= 1;
            if (c == '#') {
                final += 1;
            }
        }
        for (int i = 1, n = parts.size(); i < n - 1; i++) {
            auto temp = parts[i].substr(1, parts[i].size() - 2);
            std::replace(temp.begin(), temp.end(), ',', ' ');
            auto values = parse::getIntegers(temp);
            unsigned int combo = 0;
            for (auto value : values) {
                combo += 1 << (value);
            }
            buttons.push_back(combo);
        }
    }

    uint64_t powerOn()
    {
        std::set<int> states;
        struct Attempt {
            unsigned int value = 0;
            uint64_t clicks = 0;
            std::vector<unsigned int> buttons;
        };
        std::queue<Attempt> attempts;
        {
            Attempt attempt;
            attempt.value = 0;
            for (auto button : buttons) {
                if ((final & button) != 0) {
                    attempt.buttons.push_back(button);
                }
            }
            attempts.push(attempt);
        }
        while (!attempts.empty()) {
            auto cur = attempts.front();
            attempts.pop();
            if (cur.value == final) {
                return cur.clicks;
            }
            if (states.count(cur.value) > 0) {
                continue;
            }
            states.insert(cur.value);
            for (auto b : cur.buttons) {
                Attempt attempt;
                attempt.clicks = cur.clicks + 1;
                attempt.value = cur.value ^ b;
                auto diff = final ^ (cur.value ^ b);
                for (auto button : buttons) {
                    if ((diff & button) != 0) {
                        attempt.buttons.push_back(button);
                    }
                }
                attempts.push(attempt);
            }
        }
        return 0;
    }

    unsigned int final = 0;
    std::vector<unsigned int> buttons;
};

std::string day10::process1(std::string file)
{
    std::vector<MachineLights> MachineLightss;
    parse::read(file, '\n', [&](const std::string &line) { MachineLightss.emplace_back(line); });

    uint64_t count = 0;
    for (auto &MachineLights : MachineLightss) {
        count += MachineLights.powerOn();
    }

    return std::to_string(count);
}

std::vector<int> toInt(std::vector<uint64_t> vec)
{
    std::vector<int> result;
    result.reserve(vec.size());
    for (auto v : vec) {
        result.push_back(v);
    }
    return result;
}

std::vector<int> half(std::vector<int> joltages)
{
    for (int i = 0, n = joltages.size(); i < n; i++) {
        joltages[i] /= 2;
    }
    return joltages;
}

uint64_t toKey(std::vector<int> joltages)
{
    uint64_t key = 0;
    for (auto j : joltages) {
        key = key << 1;
        key += j % 2;
    }
    return key;
}

struct MachineJoltages {
    MachineJoltages(const std::string &line)
    {
        auto parts = parse::split(line, ' ');
        for (int i = 1, n = parts.size(); i < n - 1; i++) {
            auto temp = parts[i].substr(1, parts[i].size() - 2);
            std::replace(temp.begin(), temp.end(), ',', ' ');
            wirings.push_back(toInt(parse::getIntegers(temp)));
        }
        {
            auto last = parts.size() - 1;
            auto temp = parts[last].substr(1, parts[last].size() - 2);
            std::replace(temp.begin(), temp.end(), ',', ' ');
            joltages = toInt(parse::getIntegers(temp));
        }
    }

    uint64_t powerJoltages() const
    {
        // Thanks to
        // https://www.reddit.com/r/adventofcode/comments/1pk87hl/2025_day_10_part_2_bifurcate_your_way_to_victory/

        // Pre calculate combinations based on odd even joltajes
        std::map<uint64_t, std::vector<uint64_t>> oddEvenToConfs;
        for (uint64_t conf = 0, last = std::pow(2, wirings.size()) - 1; conf <= last; conf++) {
            std::vector<int> buttons(joltages.size(), 0);
            int pos = 0;
            auto curConf = conf;
            while (curConf > 0) {
                if (curConf % 2 == 1) {
                    for (auto button : wirings[pos]) {
                        buttons[button]++;
                    }
                }
                curConf = curConf >> 1;
                pos++;
            }
            auto key = toKey(buttons);
            auto it = oddEvenToConfs.find(key);
            if (it == oddEvenToConfs.end()) {
                oddEvenToConfs.insert({ key, { conf } });
            } else {
                it->second.push_back(conf);
            }
        }

        std::map<std::vector<int>, uint64_t> calculated;

        std::function<uint64_t(std::vector<int>)> press = [&](std::vector<int> curJoltages) -> uint64_t {
            if (std::all_of(curJoltages.begin(), curJoltages.end(), [](int j) { return j == 0; })) {
                return 0;
            }

            // Memoziation
            auto it = calculated.find(curJoltages);
            if (it != calculated.end()) {
                return it->second;
            }

            uint64_t minClics = 100000; // High enough but not so much to overflow :*D

            // Check each configuration
            auto oddEvenKey = toKey(curJoltages);
            for (int conf : oddEvenToConfs[oddEvenKey]) {
                std::vector<int> newJoltajes = curJoltages;
                uint64_t clicks = 0;
                int pos = 0;
                auto curConf = conf;
                while (curConf > 0) {
                    if (curConf % 2 == 1) {
                        for (auto button : wirings[pos]) {
                            newJoltajes[button]--;
                        }
                        clicks++;
                    }
                    curConf = curConf >> 1;
                    pos++;
                }
                bool isGood =
                    std::all_of(newJoltajes.begin(), newJoltajes.end(), [](int j) { return j >= 0 && j % 2 == 0; });
                if (isGood) {
                    auto curClicks = clicks + 2 * press(half(newJoltajes));
                    if (curClicks < minClics) {
                        minClics = curClicks;
                    }
                }
            }

            calculated[curJoltages] = minClics;
            return minClics;
        };

        return press(joltages);
    }

    std::vector<std::vector<int>> wirings;
    std::vector<int> joltages;
};

std::string day10::process2(std::string file)
{
    std::vector<MachineJoltages> MachineJoltagess;
    parse::read(file, '\n', [&](const std::string &line) { MachineJoltagess.emplace_back(line); });

    uint64_t count = 0;
    for (auto &MachineJoltages : MachineJoltagess) {
        count += MachineJoltages.powerJoltages();
    }

    return std::to_string(count);
}
