/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    21 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "catch.hpp"
#include "common.h"
#include "day21.h"
#include <string>

using namespace day21;

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}

#define TESTING(ID, PROCESS, RESULT) SECTION ("Test "#ID) {tester("2021/day21/test"#ID".txt", PROCESS, RESULT);}

TEST_CASE( "Test day21", "[day21]" ) {

    SECTION ("Problem 1") {
        TESTING(1, process1, "739785")
    }

    SECTION ("Problem 2") {
        TESTING(1, process2, "444356092776315")
    }

}
