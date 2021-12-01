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

namespace parse {

    void push_back(std::vector <std::string> *list, std::string part) {
        list->push_back(part);
    };

    void push_back_integer(std::vector <uint64_t> *list, std::string part) {
        list->push_back(std::stoi(part));
    };

    void read_all(std::string inputFilename, std::vector <std::string> *list) {
        read<std::string, std::vector < std::string> * > (inputFilename, '\n', push_back, list);
    }

    void read_all_integers(std::string inputFilename, std::vector <uint64_t> *list) {
        read<std::string, std::vector < uint64_t> * > (inputFilename, '\n', push_back_integer, list);
    }

}