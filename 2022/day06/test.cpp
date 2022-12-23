/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    06 Dec 2022
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

using namespace day06;

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT)                           \
    SECTION("Test " #ID)                                       \
    {                                                          \
        tester("2022/day06/test" #ID ".txt", PROCESS, RESULT); \
    }

TEST_CASE("Test day06", "[day06]")
{
    SECTION("Problem 1")
    {
        TESTING(1, process1, "7");
        TESTING(2, process1, "5");
        TESTING(3, process1, "6");
        TESTING(4, process1, "10");
        TESTING(5, process1, "11");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "19");
        TESTING(2, process2, "23");
        TESTING(3, process2, "23");
        TESTING(4, process2, "29");
        TESTING(5, process2, "26");
    }
}