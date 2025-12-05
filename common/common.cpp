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

#include <algorithm>
#include <numeric>
#include <regex>
#include <sstream>

namespace parse
{
    void read(std::string inputFilename, char delimiter, std::function<void(const std::string &)> insert)
    {
        std::ifstream source;
        source.open(inputFilename, std::ifstream::in);
        std::string part;
        while (std::getline(source, part, delimiter)) {
            insert(part);
        }
    }

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

    std::vector<std::string> read_all(std::string &inputFilename)
    {
        std::vector<std::string> result;
        read<std::vector<std::string> *>(inputFilename, '\n', push_back, &result);
        return result;
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

    uint64_t getInteger(const std::string &line)
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

    std::string filterDecimal(const std::string &line)
    {
        std::string result;
        for (auto c : line) {
            if (c >= '0' && c <= '9') {
                result += c;
            }
        }
        return result;
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

    Regex::Regex(const std::string &expression) : exp(expression) {}
    void Regex::search(const std::string &text, std::function<void(std::smatch &)> fun)
    {
        std::string::const_iterator searchStart(text.cbegin());
        while (std::regex_search(searchStart, text.cend(), match, exp)) {
            fun(match);
            searchStart = match.suffix().first;
        }
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

    std::string literalsToNumber(const std::string &s, bool overlapping)
    {
        std::vector<std::string> numbers = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
        auto cleanParse = [&numbers](std::string &parse) {
            auto isGoodParse = true;
            while (parse.size() > 0 && isGoodParse) {
                isGoodParse = std::any_of(numbers.begin(), numbers.end(), [parse](const std::string &number) {
                    // Exists a string that fit the current parsing
                    return number.rfind(parse, 0) == 0;
                });
                if (!isGoodParse) {
                    int size = parse.size();
                    if (size > 1) {
                        parse = parse.substr(1, size - 1);
                    } else {
                        parse = "";
                    }
                } else {
                    // Good, continue
                    break;
                }
            }
        };

        std::string result;
        std::string parse;
        for (auto c : s) {
            if (c >= '0' && c <= '9') {
                result += c;
                parse = "";
            } else {
                // Char
                parse += c;
                cleanParse(parse);

                // Check if it is already a complete number
                for (int i = 0, n = numbers.size(); i < n; i++) {
                    if (parse == numbers[i]) {
                        result += ('1' + i);
                        if (overlapping) {
                            // Keep the parse to check for overlapping value
                            parse = parse.substr(1, parse.size() - 1);
                            cleanParse(parse);
                        } else {
                            // No overlapping are permitted, so consume the chars and go on
                            parse = "";
                        }
                        break;
                    }
                }
            }
        }
        return result;
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

    std::vector<Range> split(Range a, Range b)
    {
        std::vector<Range> result;
        auto aLast = a.from + a.len - 1;
        auto bLast = b.from + b.len - 1;

        if (a.from >= b.from && a.from <= bLast) {
            // a start in b
            if (bLast >= aLast) {
                // Entirely contained
                Range first = { a.from, a.len };
                result.push_back(first);
            } else {
                auto delta = a.from - b.from;
                auto len = b.len - delta;
                Range first = { a.from, len };
                Range second = { bLast + 1, a.len - len };
                result.push_back(first);
                result.push_back(second);
            }
            return result;
        }
        if (b.from >= a.from && b.from <= aLast) {
            // b start in a
            auto delta = b.from - a.from;

            Range first = { a.from, delta };
            result.push_back(first);

            if (bLast < aLast) {
                Range second = b;
                result.push_back(second);

                auto lenRes = a.len - delta - b.len;
                Range third = { bLast + 1, lenRes };
                result.push_back(third);
            } else {
                auto lenRes = a.len - delta;
                Range second = { b.from, lenRes };
                result.push_back(second);
            }

            return result;
        }
        // Empty, not found overlaps
        return result;
    }

    std::vector<Range> splitMerge(Range a, Range b)
    {
        auto getLen = [](uint64_t from, uint64_t to) -> uint64_t { return to - from + 1; };
        std::vector<Range> result;
        auto insert = [&](Range left, Range center, Range right) {
            if (left.len > 0) {
                result.push_back(left);
            }
            if (center.len > 0) {
                result.push_back(center);
            }
            if (right.len > 0) {
                result.push_back(right);
            }
        };
        auto aLast = a.from + a.len - 1;
        auto bLast = b.from + b.len - 1;

        if (a.from >= b.from && a.from <= bLast) {
            // a start in b
            Range left = { b.from, getLen(b.from, a.from - 1) };
            if (bLast >= aLast) {
                // a entirely contained in b
                Range right = { aLast + 1, getLen(aLast + 1, bLast) };
                insert(left, a, right);
            } else {
                // Overlap
                Range overlap = { a.from, getLen(a.from, bLast) };
                Range right = { bLast + 1, getLen(bLast + 1, aLast) };
                insert(left, overlap, right);
            }
            return result;
        }
        if (b.from >= a.from && b.from <= aLast) {
            // b start in a
            Range left = { a.from, getLen(a.from, b.from - 1) };
            if (bLast < aLast) {
                // b entirely contained in a
                Range right = { bLast + 1, getLen(bLast + 1, aLast) };
                insert(left, b, right);
            } else {
                // Overlap
                Range overlap = { b.from, getLen(b.from, aLast) };
                Range right = { aLast + 1, getLen(aLast + 1, bLast) };
                insert(left, overlap, right);
            }
            return result;
        }
        // Empty, not found overlaps
        return result;
    }

    std::optional<Range> merge(Range a, Range b)
    {
        auto getLen = [](uint64_t from, uint64_t to) -> uint64_t { return to - from + 1; };
        auto aLast = a.from + a.len - 1;
        auto bLast = b.from + b.len - 1;

        if (a.from >= b.from && a.from <= bLast) {
            // a start in b
            if (bLast >= aLast) {
                // a entirely contained in b
                return b;
            } else {
                // Overlap
                return Range{ b.from, getLen(b.from, aLast) };
            }
        }
        if (b.from >= a.from && b.from <= aLast) {
            // b start in a
            if (bLast < aLast) {
                // b entirely contained in a
                return a;
            } else {
                // Overlap
                return Range{ a.from, getLen(a.from, bLast) };
            }
        }
        // Empty, not found overlaps
        return {};
    }

    uint64_t greatestCommonDivisor(uint64_t a, uint64_t b)
    {
        if (b > a) {
            std::swap(a, b);
        }
        if (a % b == 0) {
            return b;
        }

        // Euclidean algorithm
        // called r the remainder of the division between a and b, the GCD between a and b is equal to the GCD between b
        // and r.
        while (b != 0) {
            auto temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    uint64_t leastCommonMultiple(uint64_t a, uint64_t b)
    {
        return (a * b / greatestCommonDivisor(a, b));
    }

    uint64_t leastCommonMultiple(std::vector<uint64_t> numb)
    {
        return std::accumulate(numb.begin(), numb.end(), numb[0],
                               [](uint64_t a, uint64_t b) { return leastCommonMultiple(a, b); });
    }

    std::string replaceAll(const std::string &line, char from, char to)
    {
        std::string result;
        for (auto c : line) {
            if (c == from) {
                result.push_back(to);
            } else {
                result.push_back(c);
            }
        }
        return result;
    }

    void countingSort(std::vector<int64_t> &values, int64_t pow, std::array<int, 10> count)
    {
        for (size_t i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }

        std::vector<int> output(values.size(), 0);
        for (auto it = values.rbegin(); it != values.rend(); ++it) {
            int digit = (*it / pow) % 10;
            output.at(--count[digit]) = *it;
        }
        std::copy(output.begin(), output.end(), values.begin());
    }

    void radixSort(std::vector<int64_t> &values)
    {
        auto maxVal = *std::max_element(values.begin(), values.end());
        size_t digits = 0;
        for (int pow = 1; maxVal / pow > 0; pow *= 10) {
            digits++;
        }

        // For each digit
        // The array contains the frequency for each possible value
        std::vector<std::array<int, 10>> frequency(digits, { 0 });
        for (auto val : values) {
            int j = 0;
            int64_t rest = val % 10;
            while (val > 0) {
                frequency[j][rest]++;
                val /= 10;
                rest = val % 10;
                j++;
            }
        }

        int64_t pow = 1;
        for (size_t digit = 0; digit < digits; digit++, pow *= 10) {
            countingSort(values, pow, frequency[digit]);
        }
    }

    int digits(int64_t value)
    {
        value = std::abs(value);
        if (value < 10) {
            return 1;
        }
        int n = 0;
        while (value) {
            value /= 10;
            n++;
        }
        return n;
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

    std::vector<std::pair<size_t, size_t>> neighbours8(size_t i, size_t j, size_t height, size_t width)
    {
        std::vector<std::pair<size_t, size_t>> n;
        // Ortho
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
        // Diagonals
        if (i > 0 && j > 0) {
            n.push_back(std::make_pair(i - 1, j - 1));
        }
        if (i > 0 && j < width - 1) {
            n.push_back(std::make_pair(i - 1, j + 1));
        }
        if (i < width - 1 && j > 0) {
            n.push_back(std::make_pair(i + 1, j - 1));
        }
        if (i < width - 1 && j < width - 1) {
            n.push_back(std::make_pair(i + 1, j + 1));
        }
        return n;
    }

    std::vector<size_t> neighbours4(const size_t pos, const size_t width, const size_t maxLen)
    {
        std::vector<size_t> n;
        size_t j = 0;
        // Left
        if (pos % width != 0) {
            j = pos - 1;
            n.push_back(j);
        }
        // Right
        if (pos % width != width - 1) {
            j = pos + 1;
            n.push_back(j);
        }
        // Down
        j = pos + width;
        if (j < maxLen) {
            n.push_back(j);
        }
        n.push_back(j);
        // Up
        if (pos >= width) {
            j = pos - width;
            n.push_back(j);
        }
        return n;
    }

    std::vector<std::pair<size_t, size_t>> neighboursArea(size_t from_i, size_t from_j, size_t to_i, size_t to_j,
                                                          size_t height, size_t width, bool excludeInside)
    {
        std::set<std::pair<size_t, size_t>> found;
        for (size_t i = std::min(from_i, to_i), n = std::max(from_i, to_i); i <= n; i++) {
            for (size_t j = std::min(from_j, to_j), m = std::max(from_j, to_j); j <= m; j++) {
                // Ortho
                if (i > 0) {
                    found.insert(std::make_pair(i - 1, j));
                }
                if (i < height - 1) {
                    found.insert(std::make_pair(i + 1, j));
                }
                if (j > 0) {
                    found.insert(std::make_pair(i, j - 1));
                }
                if (j < width - 1) {
                    found.insert(std::make_pair(i, j + 1));
                }
                // Diagonals
                if (i > 0 && j > 0) {
                    found.insert(std::make_pair(i - 1, j - 1));
                }
                if (i > 0 && j < width - 1) {
                    found.insert(std::make_pair(i - 1, j + 1));
                }
                if (i < width - 1 && j > 0) {
                    found.insert(std::make_pair(i + 1, j - 1));
                }
                if (i < width - 1 && j < width - 1) {
                    found.insert(std::make_pair(i + 1, j + 1));
                }
            }
        }
        if (excludeInside) {
            for (size_t i = std::min(from_i, to_i), n = std::max(from_i, to_i); i <= n; i++) {
                for (size_t j = std::min(from_j, to_j), m = std::max(from_j, to_j); j <= m; j++) {
                    found.erase(std::make_pair(i, j));
                }
            }
        }
        std::vector<std::pair<size_t, size_t>> neighborhood;
        for (auto &&neighbour : found) {
            neighborhood.push_back(neighbour);
        }

        return neighborhood;
    }

} // namespace matrix