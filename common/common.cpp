/**
 * @file    common.cpp
 * @brief   implementation of the common library
 *
 * @author  Niccolò Pieretti
 * @date    28 Nov 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "common.h"

#include <regex>
#include <sstream>

namespace parse
{
    void push_back(std::vector<std::string> *list, std::string part)
    {
        list->push_back(part);
    }

    void push_back_notempty(std::vector<std::string> *list, std::string part)
    {
        if (part != "") {
            list->push_back(part);
        }
    }

    void push_back_integer(std::vector<uint64_t> *list, std::string part)
    {
        list->push_back(std::stoi(part));
    }

    void read_all(std::string &inputFilename, std::vector<std::string> *list)
    {
        read<std::vector<std::string> *>(inputFilename, '\n', push_back, list);
    }

    void read_all_notempty(std::string &inputFilename, std::vector<std::string> *list)
    {
        read<std::vector<std::string> *>(inputFilename, '\n', push_back_notempty, list);
    }

    void emplace(std::set<std::string> *set, std::string part)
    {
        set->emplace(part);
    }

    void read_all_ordered(std::string &inputFilename, std::set<std::string> *set)
    {
        read<std::set<std::string> *>(inputFilename, '\n', emplace, set);
    }

    void read_all_integers(std::string &inputFilename, std::vector<uint64_t> *list)
    {
        read<std::vector<uint64_t> *>(inputFilename, '\n', push_back_integer, list);
    }

    uint64_t getInteger(std::string &line)
    {
        uint64_t res = 0;
        const std::regex base_regex("(\\d+)");
        std::smatch base_match;
        if (std::regex_search(line, base_match, base_regex)) {
            std::string value = base_match[0].str();
            res = std::stoull(value);
        }
        return res;
    }

    std::vector<uint64_t> getIntegers(const std::string &line)
    {
        std::vector<uint64_t> res;
        std::stringstream ss(line);
        std::string word;
        uint64_t number;
        while (!ss.eof()) {
            ss >> word;
            if (std::stringstream(word) >> number) {
                res.push_back(number);
            }
            word = "";
        }
        return res;
    }

    std::vector<std::string> split(std::string input, char separator)
    {
        std::stringstream inputStream(input);
        std::string segment;
        std::vector<std::string> res;

        while (std::getline(inputStream, segment, separator)) {
            res.push_back(segment);
        }
        return res;
    }

} // namespace parse

namespace convert
{
    uint64_t fromBinary(std::string &binary)
    {
        uint64_t value = 0;
        auto len = binary.size();
        for (size_t i = 0; i < len; ++i) {
            value *= 2;
            if (binary[i] == '1') {
                value++;
            }
        }
        return value;
    }

    uint64_t positionOf(char c, bool dist)
    {
        if (c >= 'a' && c <= 'z') {
            return c - 'a';
        }
        if (dist) {
            return c - 'A' + 26;
        } else {
            return c - 'A';
        }
    }

    std::bitset<52> strToBitsetAll(const std::string &s)
    {
        std::bitset<52> contains;
        for (auto c : s) {
            contains.set(positionOf(c, true));
        }
        return contains;
    }

    std::bitset<26> strToBitset(const std::string &s)
    {
        std::bitset<26> contains;
        for (auto c : s) {
            contains.set(positionOf(c, false));
        }
        return contains;
    }

} // namespace convert

namespace op
{
    int normalizeDirection(int64_t direction)
    {
        if (direction == 0) {
            return direction;
        }
        if (direction < 0) {
            return -1 * (direction / direction);
        }
        return direction / direction;
    }

    OCR::OCR()
    {
        smearedToLetter = {
            { std::bitset<24>(std::string("011010011001111110011001")), 'A' },
            { std::bitset<24>(std::string("111010011110100110011110")), 'B' },
            { std::bitset<24>(std::string("011010011000100010010110")), 'C' },
            // { std::bitset<24>(std::string("d")), 'D' },
            { std::bitset<24>(std::string("111110001110100010001111")), 'E' },
            { std::bitset<24>(std::string("111110001110100010001000")), 'F' },
            { std::bitset<24>(std::string("011010011000101110010111")), 'G' },
            { std::bitset<24>(std::string("100110011111100110011001")), 'H' },
            // { std::bitset<24>(std::string("i")), 'I' },
            { std::bitset<24>(std::string("001100010001000110010110")), 'J' },
            { std::bitset<24>(std::string("100110101100101010101001")), 'K' },
            { std::bitset<24>(std::string("100010001000100010001111")), 'L' },
            // { std::bitset<24>(std::string("m")), 'M' },
            // { std::bitset<24>(std::string("n")), 'N' },
            { std::bitset<24>(std::string("011010011001100110010110")), 'O' },
            { std::bitset<24>(std::string("111010011001111010001000")), 'P' },
            //        { std::bitset<24>(std::string("q")), 'Q' },
            { std::bitset<24>(std::string("111010011001111010101001")), 'R' },
            { std::bitset<24>(std::string("011110001000011000011110")), 'S' },
            // { std::bitset<24>(std::string("t")), 'T' },
            { std::bitset<24>(std::string("100110011001100110010110")), 'U' },
            // { std::bitset<24>(std::string("v")), 'V' },
            // { std::bitset<24>(std::string("w")), 'W' },
            // { std::bitset<24>(std::string("x")), 'X' },
            // { std::bitset<24>(std::string("y")), 'Y' },
            { std::bitset<24>(std::string("111100010010010010001111")), 'Z' },
        };
    }

    std::string OCR::execute(std::vector<std::string> image, char on, char off)
    {
        std::string result;
        size_t idx = 0;
        // Assume letter size is 4*6
        size_t width = 4;
        // size_t heigth = 6;

        size_t totalWidth = image[0].size();
        for (; idx < totalWidth; idx += width + 1) {
            std::string smeared;
            for (auto &&line : image) {
                smeared.append(line.substr(idx, width));
            }
            std::replace(smeared.begin(), smeared.end(), on, '1');
            std::replace(smeared.begin(), smeared.end(), off, '0');
            auto it = smearedToLetter.find(std::bitset<24>(smeared));
            if (it != smearedToLetter.end()) {
                result.push_back(it->second);
            }
        }
        return result;
    }

    std::string OCR::execute(std::vector<std::string> image)
    {
        std::string result;
        size_t idx = 0;
        // Assume letter size is 4*6
        size_t width = 4;
        // size_t heigth = 6;

        size_t totalWidth = image[0].size();
        for (; idx < totalWidth; idx += width + 1) {
            std::string smeared;
            for (auto &&line : image) {
                smeared.append(line.substr(idx, width));
            }
            auto it = smearedToLetter.find(std::bitset<24>(smeared));
            if (it != smearedToLetter.end()) {
                result.push_back(it->second);
            }
        }
        return result;
    }

} // namespace op

namespace matrix
{
    std::vector<std::pair<size_t, size_t>> neighbours4(size_t i, size_t j, size_t height, size_t width)
    {
        std::vector<std::pair<size_t, size_t>> n;
        if (i > 0) {
            n.push_back(std::make_pair(i - 1, j));
        }
        if (i < height - 1) {
            n.push_back(std::make_pair(i + 1, j));
        }
        if (j > 0) {
            n.push_back(std::make_pair(i, j - 1));
        }
        if (j < width - 1) {
            n.push_back(std::make_pair(i, j + 1));
        }

        return n;
    }

} // namespace matrix