/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    05 Dec 2021
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
#include "day06.h"
#include <string>

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}


TEST_CASE( "Test day06", "[day06]" ) {

    SECTION ("Problem 1") {
        SECTION ("Test 1") {
            tester("2021/day06/test1.txt", process1, "5934");
        }
    }

    SECTION ("Problem 2") {
        SECTION ("Test 1") {
            tester("2021/day06/test1.txt", process2, "26984457539");
        }
    }

}
