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
              std::function<void(S, L)> insert, S structure) {
        std::ifstream source;
        source.open(inputFilename, std::ifstream::in);
        std::string part;
        while (std::getline(source, part, delimiter)) {
            insert(structure, part);
        }
    }

    void push_back(std::vector <std::string> *list, std::string part);

    /**
     * Read the entire file as is and store it in a vector of strings
     * @param inputFilename the path to the file
     * @param list the structure where to save the file
     */
    void read_all(std::string inputFilename, std::vector <std::string> *list);
}

/**
 * Just a Test
 */
void test_output();

