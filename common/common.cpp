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

namespace parse {

    void push_back(std::vector <std::string> *list, std::string part) {
        list->push_back(part);
    };

    void push_back_integer(std::vector <uint64_t> *list, std::string part) {
        list->push_back(std::stoi(part));
    };

    void read_all(std::string& inputFilename, std::vector <std::string> *list) {
        read<std::string, std::vector < std::string> * > (inputFilename, '\n', push_back, list);
    }

    void read_all_integers(std::string& inputFilename, std::vector <uint64_t> *list) {
        read<std::string, std::vector < uint64_t> * > (inputFilename, '\n', push_back_integer, list);
    }

    uint64_t getInteger(std::string& line) {
        uint64_t res = 0;
        const std::regex base_regex("(\\d+)");
        std::smatch base_match;
        if (std::regex_search(line, base_match, base_regex)) {
            std::string value = base_match[0].str();
            res = std::stoull(value);
        }
        return res;
    }

}

namespace convert {

    uint64_t fromBinary(std::string& binary) {
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
}