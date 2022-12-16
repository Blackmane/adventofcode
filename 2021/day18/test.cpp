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

#include <memory>
#include <string>

using namespace day18;

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
        auto treeList = std::make_unique<TreeList>();
        std::vector<std::string> input = { "[[1,2],[[3,4],5]]",
                                           "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]",
                                           "[[[[1,1],[2,2]],[3,3]],[4,4]]",
                                           "[[[[3,0],[5,3]],[4,4]],[5,5]]",
                                           "[[[[5,0],[7,4]],[5,5]],[6,6]]",
                                           "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]" };
        std::vector<uint64_t> magnitudes = { 143, 1384, 445, 791, 1137, 3488 };
        for (auto &line : input) {
            convertLine(treeList.get(), line);
        }

        for (size_t i = 0; i < treeList->size(); ++i) {
            CHECK(magnitudes[i] == treeList->at(i)->magnitude());
        }
    }

    SECTION("Explode")
    {
        auto treeFromList = std::make_unique<TreeList>();
        std::vector<std::string> from = { "[[[[[9,8],1],2],3],4]", "[7,[6,[5,[4,[3,2]]]]]", "[[6,[5,[4,[3,2]]]],1]",
                                          "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]",
                                          "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]" };
        for (auto &line : from) {
            convertLine(treeFromList.get(), line);
        }
        auto treeToList = std::make_unique<TreeList>();
        std::vector<std::string> to = { "[[[[0,9],2],3],4]", "[7,[6,[5,[7,0]]]]", "[[6,[5,[7,0]]],3]",
                                        "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[7,0]]]]" };
        for (auto &line : to) {
            convertLine(treeToList.get(), line);
        }

        for (size_t i = 0; i < treeFromList->size(); ++i) {
            CHECK(treeFromList->at(i)->explode());
            CHECK(treeFromList->at(i)->magnitude() == treeToList->at(i)->magnitude());
        }
    }

    SECTION("SUM")
    {
        auto treeList = std::make_unique<TreeList>();
        std::vector<std::string> input = { "[[[[4,3],4],4],[7,[[8,4],9]]]", "[1,1]" };
        for (auto &line : input) {
            convertLine(treeList.get(), line);
        }
        Tree *sum = treeList->at(0).get();
        for (size_t i = 1, n = treeList->size(); i < n; ++i) {
            *sum + treeList->at(i).get();
        }
        auto checkList = std::make_unique<TreeList>();
        convertLine(checkList.get(), "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
        CHECK(sum->magnitude() == checkList->at(0)->magnitude());
    }

    SECTION("Multi sum")
    {
        auto treeList = std::make_unique<TreeList>();
        std::vector<std::string> input = { "[1,1]", "[2,2]", "[3,3]", "[4,4]", "[5,5]", "[6,6]" };
        for (auto &line : input) {
            convertLine(treeList.get(), line);
        }
        auto checkList = std::make_unique<TreeList>();
        std::vector<std::string> response = { "[1,1]",
                                              "[[1,1],[2,2]]",
                                              "[[[1,1],[2,2]],[3,3]]",
                                              "[[[[1,1],[2,2]],[3,3]],[4,4]]",
                                              "[[[[3,0],[5,3]],[4,4]],[5,5]]",
                                              "[[[[5,0],[7,4]],[5,5]],[6,6]]" };
        for (auto &line : response) {
            convertLine(checkList.get(), line);
        }

        Tree *sum = treeList->at(0).get();
        for (size_t i = 1, n = treeList->size(); i < n; ++i) {
            *sum + treeList->at(i).get();
            CHECK(sum->magnitude() == checkList->at(i)->magnitude());
        }
    }

    SECTION("Big sum")
    {
        auto treeList = std::make_unique<TreeList>();
        std::vector<std::string> input = {
            "[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]", 
            "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]",
            "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]",
             "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]",
             "[7,[5,[[3,8],[1,4]]]]",
             "[[2,[2,2]],[8,[8,1]]]",
             "[2,9]",
             "[1,[[[9,3],9],[[9,0],[0,7]]]]",
             "[[[5,[7,4]],7],1]",
             "[[[[4,2],2],6],[8,7]]"
        };
        for (auto &line : input) {
            convertLine(treeList.get(), line);
        }
        auto checkList = std::make_unique<TreeList>();
        std::vector<std::string> response = { "[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]",
                                              "[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]",
                                              "[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]",
                                              "[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]",
                                              "[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]",
                                              "[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]",
                                              "[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]",
                                              "[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]",
                                              "[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]",
                                              "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]" };
        for (auto &line : response) {
            convertLine(checkList.get(), line);
        }

        Tree *sum = treeList->at(0).get();
        for (size_t i = 1, n = treeList->size(); i < n; ++i) {
            *sum + treeList->at(i).get();
            CHECK(sum->magnitude() == checkList->at(i)->magnitude());
        }
    }

    SECTION("Problem 1")
    { 
        TESTING(1, process1, "4140") 
    }

    SECTION("Problem 2")
    {
        TESTING(1, process2, "3993")
    }
}