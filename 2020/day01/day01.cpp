/**
 * @file    day01.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    01 Dec 2020
 * @bug     
 * @todo    
 * 
 ****************************************************************************
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include "day01.h"

#include "common.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ===== ===== ===== Const ===== ===== =====
const int64_t SUMVALUE = 2020;

// ===== ===== ===== Utils ===== ===== =====
/*
    Find two number, a b, such that a+b = 2020.
    The idea is:
        if a == b then a = 1010 and b = 1010
        if a < b then a < 1010 and b > 1010
        if a > b then a > 1010 and b > 1010
    Then you don't need to check all possible combination, but just from the two subset.
        one value from subset of value lesser than 1010 with
        one value from subset of value greater than 1010
*/
class ExpenseReport
{
  public:
    explicit ExpenseReport(const std::string &filename);
    int64_t solution();

  private:
    void readFileToVector(const std::string &filename);

    const int64_t HalfValue = SUMVALUE / 2;
    std::vector<int64_t> lessHalf;
    std::vector<int64_t> greaterHalf;
    int64_t half = 0;
};

/*
    Find three number, a b c, such that a+b+b = 2020.
    The idea is the same. Possible ordered combinations are:
        if a > 1346 then b <= 673 and c <= 673
        if a <= 1346 & a > 673 then b <= 1346 and c <= 673

    Then you don't need to check all possible combination, but just some:
        one value from the grater subset with two value from lesser subset
        two value from the mid subset with one value from lesser subset
        one value from the mid subset with two value from lesser subset
*/
class ExpenseReportTriple
{
  public:
    explicit ExpenseReportTriple(const std::string &filename);
    int64_t solution();

  private:
    void readFileToVector(const std::string &filename);

    const int64_t FirstThirdValue = 673;
    const int64_t SecondThirdValue = 1346;
    std::vector<int64_t> lesserThird;
    std::vector<int64_t> midThird;
    std::vector<int64_t> greaterThird;
};

// ===== ===== ===== Implementations ===== ===== =====

ExpenseReport::ExpenseReport(const std::string &filename)
{
    readFileToVector(filename);
}

void ExpenseReport::readFileToVector(const std::string &filename)
{
    std::ifstream source;
    source.open(filename);
    int64_t value = 0;
    std::string line;
    while (std::getline(source, line)) {
        try {
            value = stol(line);
        } catch (const std::exception &e) {
            continue;
        }
        if (value == HalfValue) {
            half++;
        } else if (value < HalfValue) {
            lessHalf.push_back(value);
        } else {
            greaterHalf.push_back(value);
        }
    }
}

int64_t ExpenseReport::solution()
{
    for (auto lesser : lessHalf) {
        for (auto greater : greaterHalf) {
            if (lesser + greater == SUMVALUE) {
                return lesser * greater;
            }
        }
    }
    return 0;
}

ExpenseReportTriple::ExpenseReportTriple(const std::string &filename)
{
    readFileToVector(filename);
}

void ExpenseReportTriple::readFileToVector(const std::string &filename)
{
    std::ifstream source;
    source.open(filename);
    int64_t value;
    std::string line;
    while (std::getline(source, line)) {
        try {
            value = stol(line);
        } catch (const std::exception &e) {
            continue;
        }
        if (value <= FirstThirdValue) {
            lesserThird.push_back(value);
        } else if (value <= SecondThirdValue) {
            midThird.push_back(value);
        } else {
            greaterThird.push_back(value);
        }
    }
}

int64_t ExpenseReportTriple::solution()
{
    // Iterate greater
    for (auto greater : greaterThird) {
        // Value *greatit >= 1346
        for (auto lessit = std::begin(lesserThird); lessit != std::end(lesserThird); ++lessit) {
            // Value *lessit <= 673
            int64_t twoSum = greater + *lessit;
            if (twoSum < SUMVALUE) {
                // TODO: lessit2 parte da lessit
                for (auto lessit2 = lessit; lessit2 != std::end(lesserThird); ++lessit2) {
                    if (twoSum + *lessit2 == SUMVALUE) {
                        return greater * (*lessit) * (*lessit2);
                    }
                }
            }
        }
    }

    // Iterate half
    for (auto halfit = std::begin(midThird); halfit != std::end(midThird); ++halfit) {
        for (auto halfit2 = halfit; halfit2 != std::end(midThird); ++halfit2) {
            int64_t twoSum = *halfit + *halfit2;
            if (twoSum < SUMVALUE) {
                for (auto lesser : lesserThird) {
                    if (twoSum + lesser == SUMVALUE) {
                        return (*halfit) * (*halfit2) * lesser;
                    }
                }
            }
        }

        for (auto lessit = std::begin(lesserThird); lessit != std::end(lesserThird); ++lessit) {
            int64_t twoSum = *halfit + *lessit;
            if (twoSum >= SecondThirdValue) {
                for (auto lessit2 = lessit; lessit2 != std::end(lesserThird); ++lessit2) {
                    if (twoSum + *lessit2 == SUMVALUE) {
                        return (*halfit) * (*lessit) * (*lessit2);
                    }
                }
            }
        }
    }

    return -1;
}

std::string day01::process1(std::string file)
{
    ExpenseReport report(file);
    return std::to_string(report.solution());
}

std::string day01::process2(std::string file)
{
    ExpenseReportTriple reportTriple(file);
    return std::to_string(reportTriple.solution());
}