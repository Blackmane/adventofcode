/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    08 Dec 2025
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
#include "day08.h"

#include <string>

using namespace day08;

#define TESTING(ID, PROCESS, RESULT) tester("2025/day08/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE("Test day08", "[day08]")
{
    SECTION("Problem 1")
    {
        auto result = process1("2025/day08/test1.txt", 10);
        CHECK_THAT(result, Catch::Matchers::Equals("40"));
    }

    SECTION("Problem 2")
    {
        auto result = process2("2025/day08/test1.txt", 20);
        CHECK_THAT(result, Catch::Matchers::Equals("25272"));
    }
}

TEST_CASE("Benchmarks day08", "[day08]")
{
    BENCHMARK("Problem 1")
    {
        return process1("2025/day08/input.txt", 1000);
    };

    BENCHMARK("Problem 2")
    {
        return process2("2025/day08/input.txt", 1000);
    };
}
