/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    28 Nov 2021
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
#include "day02.h"
#include <string>

// @formatter:off

TEST_CASE( "Test day02", "[day02]" ) {

    SECTION ("Problem 1") {
        SECTION ("Test 1") {
            std::string inputFile("2016/day02/test1.txt");
            std::string expected = "1985";
            auto result = process1(inputFile);
            CHECK(expected.compare(result) ==  0);
        }
    }

    SECTION ("Problem 2") {
        SECTION ("Test 1") {
            std::string inputFile("2016/day02/test1.txt");
            std::string expected = "5DB3";
            auto result = process2(inputFile);
            CHECK(expected.compare(result) ==  0);
        }
    }

}
