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

using namespace day12;

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}

#define TESTING(ID, PROCESS, RESULT)                           \
    SECTION("Test " #ID)                                       \
    {                                                          \
        tester("2021/day12/test" #ID ".txt", PROCESS, RESULT); \
    }

TEST_CASE( "Test day12", "[day12]" ) {
    SECTION("Problem 1")
    {
        TESTING(1, process1, "10");
        TESTING(2, process1, "19");
        TESTING(3, process1, "226");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "36");
        TESTING(2, process2, "103");
        TESTING(3, process2, "3509");
    }
}
