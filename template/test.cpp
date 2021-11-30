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


TEST_CASE( "Test $DAY", "[$DAY]" ) {

    SECTION ("Problem 1") {
        SECTION ("Test 1") {
            std::string inputFile("$YEAR/$DAY/test1.txt");
            std::string expected = "0";
            auto result = process1(inputFile);
            CHECK(result == expected);
        }
    }

    SECTION ("Problem 2") {
        SECTION ("Test 1") {
            std::string inputFile("$YEAR/$DAY/test1.txt");
            std::string expected = "0";
            auto result = process2(inputFile);
            CHECK(result == expected);
        }
    }

}
