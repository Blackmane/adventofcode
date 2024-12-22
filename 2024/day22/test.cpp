/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    22 Dec 2024
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
#include "day22.h"

#include <string>

using namespace day22;

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT) tester("2024/day22/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE("Test day22", "[day22]")
{
    SECTION("Problem 1")
    {
        TESTING(1, process1, "37327623");
    }

    SECTION("Problem 2")
    {
        TESTING(2, process2, "23");
    }
}

TEST_CASE("Benchmarks day22", "[day22]")
{
    BENCHMARK("Problem 1")
    {
        return process1("2024/day22/input.txt");
    };

    BENCHMARK("Problem 2")
    {
        return process2("2024/day22/input.txt");
    };
}
