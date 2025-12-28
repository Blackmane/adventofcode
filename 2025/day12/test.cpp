/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2025
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
#include "day12.h"

#include <string>

using namespace day12;

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT) tester("2025/day12/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE("Test day12", "[day12]")
{
    SECTION("Problem 1")
    {
        TESTING(1, process1, "2");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "0");
    }
}

TEST_CASE("Benchmarks day12", "[day12]")
{
    BENCHMARK("Problem 1")
    {
        return process1("2025/day12/input.txt");
    };

    BENCHMARK("Problem 2")
    {
        return process2("2025/day12/input.txt");
    };
}
