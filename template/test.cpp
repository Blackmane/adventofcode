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

#include "catch.hpp"
#include "common.h"
#include "$DAY.h"
#include <string>

using namespace $DAY;

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}

#define TESTING(ID, PROCESS, RESULT) SECTION ("Test "#ID) {tester("$YEAR/$DAY/test"#ID".txt", PROCESS, RESULT);}

TEST_CASE( "Test $DAY", "[$DAY]" ) {

    SECTION ("Problem 1") {
        TESTING(1, process1, "0")
    }

    SECTION ("Problem 2") {
        TESTING(1, process2, "0")
    }

}
