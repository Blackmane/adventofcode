/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "catch.hpp"
#include "common.h"
#include "day12.h"
#include <string>

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}


TEST_CASE( "Test day12", "[day12]" ) {

    SECTION ("Problem 1") {
        SECTION ("Test 1") {
            tester("2021/day12/test1.txt", process1, "10");
        }

        SECTION ("Test 2") {
            tester("2021/day12/test2.txt", process1, "19");
        }

        SECTION ("Test 3") {
            tester("2021/day12/test3.txt", process1, "226");
        }
    }

    SECTION ("Problem 2") {
        SECTION ("Test 1") {
            tester("2021/day12/test1.txt", process2, "36");
        }

        SECTION ("Test 2") {
            tester("2021/day12/test2.txt", process2, "103");
        }

        SECTION ("Test 3") {
            tester("2021/day12/test3.txt", process2, "3509");
        }
    }

}
