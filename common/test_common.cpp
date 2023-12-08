/**
 * @file    test_common.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    10 Dec 2022
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

#include <string>

// @formatter:off


TEST_CASE("Test common", "[common]")
{
    SECTION("OP::OCR")
    {
        std::vector<std::string> input1 = {
            ".##..###...##..####.####..##..#..#...##.#..#.#.....##..###..###...###.#..#.####",
            "#..#.#..#.#..#.#....#....#..#.#..#....#.#.#..#....#..#.#..#.#..#.#....#..#....#",
            "#..#.###..#....###..###..#....####....#.##...#....#..#.#..#.#..#.#....#..#...#.",
            "####.#..#.#....#....#....#.##.#..#....#.#.#..#....#..#.###..###...##..#..#..#..",
            "#..#.#..#.#..#.#....#....#..#.#..#.#..#.#.#..#....#..#.#....#.#.....#.#..#.#...",
            "#..#.###...##..####.#.....###.#..#..##..#..#.####..##..#....#..#.###...##..####"
        };
        // Same input, just different mapping for on/off chars
        std::vector<std::string> input2 = {
            "0110011100011001111011110011001001000110100101000001100111001110001110100101111",
            "1001010010100101000010000100101001000010101001000010010100101001010000100100001",
            "1001011100100001110011100100001111000010110001000010010100101001010000100100010",
            "1111010010100001000010000101101001000010101001000010010111001110001100100100100",
            "1001010010100101000010000100101001010010101001000010010100001010000010100101000",
            "1001011100011001111010000011101001001100100101111001100100001001011100011001111"
        };
        std::string expected("ABCEFGHJKLOPRSUZ");

        op::OCR ocr;
        auto result = ocr.execute(input1, '#', '.');
        CHECK_THAT(result, Catch::Matchers::Equals(expected));
        result = ocr.execute(input2);
        CHECK_THAT(result, Catch::Matchers::Equals(expected));
    }

    SECTION("literalsToNumber")
    {
        std::vector<std::string> input = { "two1nine",         "eightwothree", "abcone2threexyz", "xtwone3four",
                                           "4nineeightseven2", "zoneight234",  "7pqrstsixteen" };
        std::vector<std::string> expected = { "219", "83", "123", "234", "49872", "1234", "76" };

        CHECK(input.size() == expected.size());
        for (int i = 0, n = input.size(); i < n; i++) {
            CHECK(expected[i] == convert::literalsToNumber(input[i]));
        }
    }

    SECTION("literalsToNumberOverlapping")
    {
        std::vector<std::string> input = { "two1nine",         "eightwothree", "abcone2threexyz", "xtwone3four",
                                           "4nineeightseven2", "zoneight234",  "7pqrstsixteen" };
        std::vector<std::string> expected = { "219", "823", "123", "2134", "49872", "18234", "76" };

        CHECK(input.size() == expected.size());
        for (int i = 0, n = input.size(); i < n; i++) {
            CHECK(expected[i] == convert::literalsToNumber(input[i], true));
        }
    }

    SECTION("Range")
    {
        op::Range a = { 1, 10 };
        op::Range b = { 8, 4 };
        auto res = op::split(a, b);
        CHECK(res[0].from == 1);
        CHECK(res[0].len == 7);
        CHECK(res[1].from == 8);
        CHECK(res[1].len == 3);
        a = { 1, 15 };
        res = op::split(a, b);
        CHECK(res[0].from == 1);
        CHECK(res[0].len == 7);
        CHECK(res[1].from == 8);
        CHECK(res[1].len == 4);
        CHECK(res[2].from == 12);
        CHECK(res[2].len == 4);
        a = { 3, 4 };
        b = { 1, 10 };
        res = op::split(a, b);
        CHECK(res[0].from == 3);
        CHECK(res[0].len == 4);
        a = { 8, 4 };
        b = { 1, 10 };
        res = op::split(a, b);
        CHECK(res[0].from == 8);
        CHECK(res[0].len == 3);
        CHECK(res[1].from == 11);
        CHECK(res[1].len == 1);
    }

    SECTION("GCD & LCM")
    {
        CHECK(op::greatestCommonDivisor(6, 6) == 6);
        CHECK(op::greatestCommonDivisor(6, 12) == 6);
        CHECK(op::greatestCommonDivisor(12, 6) == 6);
        CHECK(op::greatestCommonDivisor(10, 12) == 2);

        CHECK(op::leastCommonMultiple(10, 12) == 60);
        CHECK(op::leastCommonMultiple(10, 5) == 10);

        CHECK(op::leastCommonMultiple(10, 5) == 10);

        CHECK(op::leastCommonMultiple({ 10, 5 }) == 10);
        CHECK(op::leastCommonMultiple({ 10, 12, 14, 22 }) == 2 * 2 * 3 * 5 * 7 * 11);
    }
}
