/**
 * @file    day16.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    16 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day16.h"

#include "common.h"

#include <queue>

void convertLine(std::vector<uint8_t> *packet, std::string line)
{
    std::vector<uint8_t> temp;
    for (auto c : line) {
        if ('0' <= c && c <= '9') {
            temp.push_back(c - '0');
        } else {
            temp.push_back(c - 'A' + 10);
        }
    }
    // Merge
    auto len = temp.size() / 2;
    for (size_t i = 0; i < len; ++i) {
        auto value = (temp[i * 2] << 4) + temp[i * 2 + 1];
        packet->push_back(value);
    }
}

struct Pointer {
    size_t octect = 0;
    size_t bit = 0;
    void operator++()
    {
        bit++;
        if (bit >= 8) {
            octect += bit / 8;
            bit = bit % 8;
        }
    }
    int get(std::vector<uint8_t> *packet)
    {
        auto byte = packet->at(octect);
        return (byte & (1 << (7 - bit))) != 0 ? 1 : 0;
    }
    uint64_t read(std::vector<uint8_t> *packet, size_t len)
    {
        uint64_t res = 0;
        for (size_t i = 0; i < len; ++i) {
            res *= 2;
            res += get(packet);
            this->operator++();
        }
        return res;
    }
};

struct Operation {
    uint64_t version;
    uint64_t typeId;
    size_t lengthType = 0;
    size_t counterTotal = 0;
    size_t counter = 0;
    size_t bitsLength = 0;
    std::vector<uint64_t> values;
    Operation(size_t v, size_t t, size_t tot, size_t type) : version(v), typeId(t), lengthType(type), counterTotal(tot)
    {
    }
    Operation(size_t v, size_t t) : version(v), typeId(t) {}
};

uint64_t findSolution1(std::vector<uint8_t> *packet)
{
    uint64_t versionSum = 0;
    std::deque<Operation> stack;
    Pointer p;
    auto packetLen = packet->size();
    while (p.octect < packetLen - 1) {
        auto version = p.read(packet, 3);
        auto typeId = p.read(packet, 3);
        versionSum += version;
        Operation curOp(version, typeId);
        if (typeId == 4) {
            // Literal
            curOp.counter = 6;
            uint64_t value = 0;
            bool isLast = false;
            while (!isLast) {
                isLast = p.read(packet, 1) == 0;
                value = value << 4;
                value += p.read(packet, 4);
                curOp.counter += 5;
            }
            // Save the number
            curOp.bitsLength = curOp.counter;
            curOp.values.push_back(value);
        } else {
            // Operators
            curOp.lengthType = p.read(packet, 1);
            if (curOp.lengthType == 0) {
                curOp.counterTotal = p.read(packet, 15);
                curOp.bitsLength = 6 + 1 +15;
            } else {
                curOp.counterTotal = p.read(packet, 11);
                curOp.bitsLength = 6 + 1 + 11;
            }
        }
        stack.push_back(curOp);

        while (!stack.empty()) {
            auto op = stack.back();
            if (op.counterTotal <= op.counter) {
                stack.pop_back();
            } else {
                // Still on the current operation
                break;
            }
            // Apply operation ...
            if (stack.empty()) {
                return versionSum;
            }
            auto& back = stack.back();
            if (back.lengthType == 0) {
                back.counter += op.bitsLength;
            } else {
                back.counter += 1;
            }
            back.bitsLength += op.bitsLength;
        }
    }
    return versionSum;
}

uint64_t applyOperation(Operation *op)
{
    // Do operation on values
    uint64_t result = 0;
    switch (op->typeId) {
        case 0:
            // Sum
            result = 0;
            for (auto val : op->values) {
                result += val;
            }
            break;
        case 1:
            // Product
            result = 1;
            for (auto val : op->values) {
                result *= val;
            }
            break;
        case 2:
            // Min
            result = -1;
            for (auto val : op->values) {
                if (val < result) {
                    result = val;
                }
            }
            break;
        case 3:
            // Max
            result = 0;
            for (auto val : op->values) {
                if (val > result) {
                    result = val;
                }
            }
            break;
        case 4:
            // Literal
            result = op->values[0];
            break;
        case 5:
            // Greather than
            result = op->values[0] > op->values[1] ? 1 : 0;
            break;
        case 6:
            // Lesser than
            result = op->values[0] < op->values[1] ? 1 : 0;
            break;
        case 7:
            // Equal
            result = op->values[0] == op->values[1] ? 1 : 0;
            break;
    }
    return result;
}

uint64_t findSolution2(std::vector<uint8_t> *packet)
{
    std::deque<Operation> stack;
    Pointer p;
    auto packetLen = packet->size();
    while (p.octect < packetLen - 1) {
        auto version = p.read(packet, 3);
        auto typeId = p.read(packet, 3);
        Operation curOp(version, typeId);
        if (typeId == 4) {
            // Literal
            curOp.counter = 6;
            uint64_t value = 0;
            bool isLast = false;
            while (!isLast) {
                isLast = p.read(packet, 1) == 0;
                value = value << 4;
                value += p.read(packet, 4);
                curOp.counter += 5;
            }
            // Save the number
            curOp.bitsLength = curOp.counter;
            curOp.values.push_back(value);
        } else {
            // Operators
            curOp.lengthType = p.read(packet, 1);
            if (curOp.lengthType == 0) {
                curOp.counterTotal = p.read(packet, 15);
                curOp.bitsLength = 6 + 1 + 15;
            } else {
                curOp.counterTotal = p.read(packet, 11);
                curOp.bitsLength = 6 + 1 + 11;
            }
        }
        stack.push_back(curOp);

        while (!stack.empty()) {
            auto op = stack.back();
            if (op.counterTotal <= op.counter) {
                stack.pop_back();
            } else {
                // Still on the current operation
                break;
            }
            auto result = applyOperation(&op);
            if (stack.empty()) {
                return result;
            }
            auto& back = stack.back();
            back.values.push_back(result);
            if (back.lengthType == 0) {
                back.counter += op.bitsLength;
            } else {
                back.counter += 1;
            }
            back.bitsLength += op.bitsLength;
        }
    }

    auto last = stack.back();
    return applyOperation(&last);
}

std::string process1(std::string file)
{
    std::vector<uint8_t> packet;
    parse::read<std::vector<uint8_t> *>(file, '\n', convertLine, &packet);
    auto res = findSolution1(&packet);
    return std::to_string(res);
}

std::string process2(std::string file)
{
    std::vector<uint8_t> packet;
    parse::read<std::vector<uint8_t> *>(file, '\n', convertLine, &packet);
    auto res = findSolution2(&packet);
    return std::to_string(res);
}
