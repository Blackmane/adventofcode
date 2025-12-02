/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    02 Dec 2025
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
#include "02.h"
#include <string>

using namespace day02;

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}

#define TESTING(ID, PROCESS, RESULT) tester("2025/02/test" #ID ".txt", PROCESS, RESULT)

TEST_CASE( "Test 02", "[02]" ) {
    SECTION("Problem 1")
    {
        TESTING(1, process1, "1227775554");
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "4174379265");
    }
}

TEST_CASE("Benchmarks 02", "[02]")
{
    BENCHMARK("Problem 1")
    {
        return process1("2025/02/input.txt");
    };

    BENCHMARK("Problem 2")
    {
        return process2("2025/02/input.txt");
    };
}
