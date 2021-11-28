/**
 * @file    common.h
 * @brief   Common library for AoC
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

#include <fstream>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
//#include <set>


// TODO: aggiungere i test per common

namespace parse {

    template<class L, class S>
    void read(std::string inputFilename, char delimiter,
              std::function <void(S, L)> insert, S structure) {
        std::ifstream source;
        source.open(inputFilename);
        std::string part;
        while (std::getline(source, part, delimiter)) {
            std::cout << "OK";
            insert(structure, part);
        }
    }

    static auto push_back = [](std::vector<std::string> * list, std::string part) -> void {
        list->push_back(part);
    };

}

/**
 * Just a Test
 */
void test_output();

