/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    14 Dec 2024
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
#include "day14.h"

#include <string>

using namespace day14;

void tester(std::string inputFile, std::function<std::string(std::string, uint64_t, uint64_t, uint64_t)> process,
            std::string expected)
{
    auto result = process(inputFile, 100, 11, 7);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT) tester("2024/day14/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE("Test day14", "[day14]")
{
    SECTION("Problem 1")
    {
        TESTING(1, process1, "12");
    }
}

TEST_CASE("Benchmarks day14", "[day14]")
{
    BENCHMARK("Problem 1")
    {
        return process1("2024/day14/input.txt", 100, 101, 103);
    };

    BENCHMARK("Problem 2")
    {
        return process2("2024/day14/input.txt");
    };
}
