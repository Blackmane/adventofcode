/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    16 Dec 2021
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
#include "day16.h"
#include <string>

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected) {
    auto result = process(inputFile);
    CHECK_THAT( result, Catch::Matchers::Equals( expected ) );
}


TEST_CASE( "Test day16", "[day16]" ) {

    SECTION ("Problem 1") {
        SECTION ("Test 1") {
            tester("2021/day16/test1.txt", process1, "16");
        }
        SECTION ("Test 2") {
            tester("2021/day16/test2.txt", process1, "12");
        }
        SECTION ("Test 3") {
            tester("2021/day16/test3.txt", process1, "23");
        }
        SECTION ("Test 4") {
            tester("2021/day16/test4.txt", process1, "31");
        }
    }

    SECTION ("Problem 2") {
        SECTION ("Test 1") {
            tester("2021/day16/test21.txt", process2, "3");
        }
        SECTION ("Test 2") {
            tester("2021/day16/test22.txt", process2, "54");
        }
        SECTION ("Test 3") {
            tester("2021/day16/test23.txt", process2, "7");
        }
        SECTION ("Test 4") {
            tester("2021/day16/test24.txt", process2, "9");
        }
        SECTION ("Test 5") {
            tester("2021/day16/test25.txt", process2, "1");
        }
        SECTION ("Test 6") {
            tester("2021/day16/test26.txt", process2, "0");
        }
        SECTION ("Test 7") {
            tester("2021/day16/test27.txt", process2, "0");
        }
        SECTION ("Test 8") {
            tester("2021/day16/test28.txt", process2, "1");
        }
        SECTION ("Test SPECIALE") {
            tester("2021/day16/test29.txt", process2, "19891");
        }

        // SECTION ("Test 1 bis") {
        //     tester("2021/day16/test1.txt", process2, "15");
        // }
        // SECTION ("Test 2 bis") {
        //     tester("2021/day16/test2.txt", process2, "46");
        // }
        // SECTION ("Test 3 bis") {
        //     tester("2021/day16/test3.txt", process2, "46");
        // }
        // SECTION ("Test 4 bis") {
        //     tester("2021/day16/test4.txt", process2, "54");
        // }
    }

}
