/**
 * @file    day15.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    15 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day15.h"

#include "common.h"

void addHash(uint64_t *sum, std::string part)
{
    uint64_t hash = 0;
    for (auto c : part) {
        if (c != '\n') {
            hash += (int)c;
            hash *= 17;
            hash = hash % 256;
        }
    }
    (*sum) += hash;
}

typedef std::vector<std::vector<std::pair<std::string, uint8_t>>> Boxes;
void setBox(Boxes *boxes, std::string part)
{
    uint64_t hash = 0;
    int n = part.size();
    int i = 0;
    for (; i < n; i++) {
        char c = part[i];
        if (c == '-' || c == '=' || c == '\n') {
            break;
        }
        hash += (int)c;
        hash *= 17;
        hash = hash % 256;
    }
    auto key = part.substr(0, i);
    if (part[i] == '-') {
        for (auto pos = boxes->at(hash).begin(); pos != boxes->at(hash).end(); pos++) {
            if (pos->first == key) {
                boxes->at(hash).erase(pos);
                break;
            }
        }
    }
    if (part[i] == '=') {
        i++;
        uint8_t lens = part[i] - '0';
        bool found = false;
        for (auto pos = boxes->at(hash).begin(); pos != boxes->at(hash).end(); pos++) {
            if (pos->first == key) {
                pos->second = lens;
                found = true;
                break;
            }
        }
        if (!found) {
            boxes->at(hash).push_back({ key, lens });
        }
    }
}

std::string day15::process1(std::string file)
{
    uint64_t sum = 0;
    parse::read<uint64_t *>(file, ',', addHash, &sum);
    return std::to_string(sum);
}

std::string day15::process2(std::string file)
{
    std::vector<std::pair<std::string, uint8_t>> empty;
    empty.clear();
    Boxes boxes(256, empty);
    parse::read<Boxes *>(file, ',', setBox, &boxes);
    uint64_t focusPower = 0;
    int i = 1;
    for (auto &&box : boxes) {
        for (int j = 0, n = box.size(); j < n; j++) {
            focusPower += i * (j + 1) * box[j].second;
        }
        i++;
    }
    return std::to_string(focusPower);
}