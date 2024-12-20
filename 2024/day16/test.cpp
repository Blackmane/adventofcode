/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    16 Dec 2024
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
#include "day16.h"

#include <string>

using namespace day16;

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT) tester("2024/day16/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE("Test day16", "[day16]")
{
    SECTION("Problem 1")
    {
        TESTING(1, process1, "7036");
        TESTING(2, process1, "11048");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "45");
        TESTING(2, process2, "64");
    }
}

TEST_CASE("Benchmarks day16", "[day16]")
{
    BENCHMARK("Problem 1")
    {
        return process1("2024/day16/input.txt");
    };

    BENCHMARK("Problem 2")
    {
        return process2("2024/day16/input.txt");
    };
}
