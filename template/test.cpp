/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    $TODAY
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
#include "$DAY.h"
#include <string>

using namespace $DAY;

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}

#define TESTING(ID, PROCESS, RESULT) tester("$YEAR/$DAY/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE( "Test $DAY", "[$DAY]" ) {
    SECTION("Problem 1")
    {
        TESTING(1, process1, "0");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "0");
    }
}

TEST_CASE("Benchmarks $DAY", "[$DAY]")
{
    BENCHMARK("Problem 1")
    {
        return process1("$YEAR/$DAY/input.txt");
    };

    BENCHMARK("Problem 2")
    {
        return process2("$YEAR/$DAY/input.txt");
    };
}
