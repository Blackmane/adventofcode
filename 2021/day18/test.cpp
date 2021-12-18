/**
 * @file    test.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    18 Dec 2021
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
//#include "common.h"
#include "day18.h"

#include <string>

// @formatter:off

void tester(std::string inputFile, std::function<std::string(std::string)> process, std::string expected)
{
    auto result = process(inputFile);
    CHECK_THAT(result, Catch::Matchers::Equals(expected));
}

#define TESTING(ID, PROCESS, RESULT)                           \
    SECTION("Test " #ID)                                       \
    {                                                          \
        tester("2021/day18/test" #ID ".txt", PROCESS, RESULT); \
    }

TEST_CASE("Test day18", "[day18]")
{
    SECTION("Magnitude")
    {
        std::unique_ptr<TreeList> treeList = std::make_unique<TreeList>();
        std::vector<std::string> input = { "[[1,2],[[3,4],5]]",
                                           "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]",
                                           "[[[[1,1],[2,2]],[3,3]],[4,4]]",
                                           "[[[[3,0],[5,3]],[4,4]],[5,5]]",
                                           "[[[[5,0],[7,4]],[5,5]],[6,6]]",
                                           "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]" };
        std::vector<uint64_t> magnitudes = { 143, 1384, 445, 791, 1137, 3488

        };
        for (auto &line : input) {
            println("CONVERTT: " << line);
            convertLine(treeList.get(), line);
        }

        for (size_t i = 0; i < treeList->size(); ++i) {
            println("MAGNITUDE: " << i);
            CHECK(magnitudes[i] == treeList->at(i)->magnitude());
        }
    }

    SECTION("Problem 1"){ TESTING(1, process1, "4140") }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "0")
    }
}
