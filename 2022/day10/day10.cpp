/**
 * @file    day10.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    09 Dec 2022
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

int64_t getValue(const std::string &line)
{
    auto n = line.size();
    if (line[0] == 'a') {
        return std::stoll(line.substr(5, n - 5));
    } else {
        return 0;
    }
}

void insert(int64_t value, std::vector<int64_t> *values)
{
    values->push_back(value);
}

bool checkCycle(uint64_t cycle)
{
    if (cycle == 20) {
        return true;
    }
    int64_t r = int64_t(cycle - 20) % 40;
    return r == 0;
}

uint64_t execute(std::vector<int64_t> &values)
{
    uint64_t cycle = 0;
    uint64_t reg = 1;
    uint64_t result = 0;
    for (auto v : values) {
        cycle++;
        // Start cycle
        if (checkCycle(cycle)) {
            result += cycle * reg;
        }
        if (v != 0) {
            cycle++;
            // Start cycle
            if (checkCycle(cycle)) {
                result += cycle * reg;
            }
        }
        reg += v;
        // End cycle
    }
    return result;
}

const char ON = '1';
const char OFF = '0';

void setPixel(std::vector<std::string> &draw, uint64_t cycle, int64_t reg)
{
    int64_t index = cycle - 1;
    int line = index / 40;
    int pos = index % 40;
    if (reg - 1 <= pos && pos <= reg + 1) {
        draw[line][pos] = ON;
    }
}

std::vector<std::string> execute2(std::vector<int64_t> &values)
{
    std::vector<std::string> draw;
    std::string emptyLine(40, OFF);
    for (int i = 0; i < 6; ++i) {
        draw.push_back(emptyLine);
    }

    uint64_t cycle = 0;
    uint64_t reg = 1;
    for (auto v : values) {
        cycle++;
        // Start cycle
        setPixel(draw, cycle, reg);
        if (v != 0) {
            cycle++;
            // Start cycle
            setPixel(draw, cycle, reg);
        }
        reg += v;
        // End cycle
    }

    return draw;
}

std::string day10::process1(std::string file)
{
    std::vector<int64_t> values;
    parse::read<int64_t, std::vector<int64_t> *>(file, '\n', &getValue, &insert, &values);
    auto result = execute(values);
    return std::to_string(result);
}

std::string day10::process2(std::string file)
{
    std::vector<int64_t> values;
    parse::read<int64_t, std::vector<int64_t> *>(file, '\n', &getValue, &insert, &values);
    std::vector<std::string> result = execute2(values);
    op::OCR ocr;
    return ocr.execute(result);
}
