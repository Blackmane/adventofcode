/**
 * @file    main_catch.cpp
 * @brief   main for catch tests
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
#include <iostream>

void test_output() {
    std::cout << "WEWE" << std::endl;
}

void parse::push_back(std::vector <std::string> *list, std::string part) {
    list->push_back(part);
};

void parse::read_all(std::string inputFilename, std::vector <std::string> *list) {
    read<std::string, std::vector < std::string> * > (inputFilename, '\n', push_back, list);
}