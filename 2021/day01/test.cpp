/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    30 Nov 2021
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
#include "day01.h"

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}


TEST_CASE( "Test day01", "[day01]" ) {

    SECTION ("Problem 1") {
        SECTION ("Test 1") {
            tester("2021/day01/test1.txt", process1, "7");
        }
    }

    SECTION ("Problem 2") {
        SECTION ("Test 1") {
            tester("2021/day01/test1.txt", process2, "5");
        }
    }

}
