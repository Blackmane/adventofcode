/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    06 Dec 2025
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
#include "day06.h"

#include <string>

using namespace day06;

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT) tester("2025/day06/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE("Test day06", "[day06]")
{
    SECTION("Problem 1")
    {
        TESTING(1, process1, "4277556");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "3263827");
    }
}

TEST_CASE("Benchmarks day06", "[day06]")
{
    BENCHMARK("Problem 1")
    {
        return process1("2025/day06/input.txt");
    };

    BENCHMARK("Problem 2")
    {
        return process2("2025/day06/input.txt");
    };
}
