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

    void push_back_integer(std::vector<uint64_t> *list, std::string part)
    {
        list->push_back(std::stoi(part));
    }

    void read_all(std::string &inputFilename, std::vector<std::string> *list)
    {
        read<std::vector<std::string> *>(inputFilename, '\n', push_back, list);
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

    std::vector<uint64_t> getIntegers(std::string &line)
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

} // namespace convert