/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    18 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
#include "common.h"
#include "day18.h"

#include <string>

using namespace day18;

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT)                           \
    SECTION("Test " #ID)                                       \
    {                                                          \
        tester("2024/day18/test" #ID ".txt", PROCESS, RESULT); \
    }

TEST_CASE("Test day18", "[day18]")
{
    // SECTION ("Problem 1") {
    //     TESTING(1, process1, "0")
    // }

    // SECTION ("Problem 2") {
    //     TESTING(1, process2, "0")
    // }
    SECTION("Benchmarks")
    {
        BENCHMARK("BENCHMARK problem 1")
        {
            return process1("2024/day18/input.txt");
        };

        BENCHMARK("BENCHMARK problem 2")
        {
            return process2("2024/day18/input.txt");
        };
    }
}
