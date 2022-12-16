/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    16 Dec 2021
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
#include "day16.h"
#include <string>

using namespace day16;

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}

#define TESTING(ID, PROCESS, RESULT)                           \
    SECTION("Test " #ID)                                       \
    {                                                          \
        tester("2021/day16/test" #ID ".txt", PROCESS, RESULT); \
    }

TEST_CASE( "Test day16", "[day16]" ) {
    SECTION("Problem 1")
    {
        TESTING(1, process1, "16");
        TESTING(2, process1, "12");
        TESTING(3, process1, "23");
        TESTING(4, process1, "31");
    }

    SECTION("Problem 2")
    {
        TESTING(21, process2, "3");
        TESTING(22, process2, "54");
        TESTING(23, process2, "7");
        TESTING(24, process2, "9");
        TESTING(25, process2, "1");
        TESTING(26, process2, "0");
        TESTING(27, process2, "0");
        TESTING(28, process2, "1");
        TESTING(29, process2, "19891");

        // SECTION ("Test 1 bis") {
        //     tester("2021/day16/test1.txt", process2, "15");
        // }
        // SECTION ("Test 2 bis") {
        //     tester("2021/day16/test2.txt", process2, "46");
        // }
        // SECTION ("Test 3 bis") {
        //     tester("2021/day16/test3.txt", process2, "46");
        // }
        // SECTION ("Test 4 bis") {
        //     tester("2021/day16/test4.txt", process2, "54");
        // }
    }
}
