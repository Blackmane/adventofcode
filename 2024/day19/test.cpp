/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    19 Dec 2024
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
#include "day19.h"

#include <string>

using namespace day19;

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT) tester("2024/day19/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE("Test day19", "[day19]")
{
    SECTION("Problem 1")
    {
        TESTING(1, process1, "6");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "16");
    }
}

TEST_CASE("Benchmarks day19", "[day19]")
{
    BENCHMARK("Problem 1")
    {
        return process1("input.txt");
    };

    BENCHMARK("Problem 2")
    {
        return process2("input.txt");
    };
}
