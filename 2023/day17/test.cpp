/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    17 Dec 2023
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
#include "day17.h"

#include <string>

using namespace day17;

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT)                           \
    SECTION("Test " #ID)                                       \
    {                                                          \
        tester("2023/day17/test" #ID ".txt", PROCESS, RESULT); \
    }

TEST_CASE("Test day17", "[day17]")
{
    SECTION("Problem 1"){ TESTING(1, process1, "102") }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "94")
        TESTING(2, process2, "71")
    }
}
