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


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace day01 {


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
class ExpenseReport {
public:
    explicit ExpenseReport(const std::string &filename);
    int64_t solution ();

private:
    void readFileToVector(const std::string& filename);
    
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
class ExpenseReportTriple {
public:
    explicit ExpenseReportTriple(const std::string &filename);
    int64_t solution ();

private:
    void readFileToVector(const std::string& filename);
    
    const int64_t FirstThirdValue = 673;
    const int64_t SecondThirdValue = 1346;
    std::vector<int64_t> lesserThird;
    std::vector<int64_t> midThird;
    std::vector<int64_t> greaterThird;
};

} // namespace day01

// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 1) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    day01::ExpenseReport report(inputFilename);
    int64_t solution = report.solution();
    if (solution != -1) {
        std::cout << solution << std::endl;
    } else {
        std::cout << "No solution found!" << std::endl;
    }
    std::cout << std::endl;

    // Part 2
    std::cout << "Part2" << std::endl;
    day01::ExpenseReportTriple reportTriple(inputFilename);
    int64_t solutionTriple = reportTriple.solution();
    if (solutionTriple != -1) {
        std::cout << solutionTriple << std::endl << std::endl;
    } else {
        std::cout << "No solution found!" << std::endl << std::endl;
    }

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

day01::ExpenseReport::ExpenseReport(const std::string & filename) {
    readFileToVector(filename);
}

void day01::ExpenseReport::readFileToVector(const std::string& filename) {
    std::ifstream source;
    source.open(filename);
    int64_t value =0;
    std::string line;
    while (std::getline(source, line)) {
        try {
            value = stol(line);
        } catch (const std::exception &e) {
            std::cout << "Error convert string to int64_t: " << e.what() << std::endl;
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

int64_t day01::ExpenseReport::solution() {
    if (half >= 2) {
        return 1010*1010;
    }
    for (auto lessit = std::begin(lessHalf); lessit != std::end(lessHalf); ++lessit) {
        for (auto greatit = std::begin(greaterHalf); greatit != std::end(greaterHalf); ++greatit) {
            if (*lessit + *greatit == SUMVALUE) {
                int64_t l = *lessit;
                int64_t g = *greatit;
                std::cout << "Value: " << l << " + " << g << ";" << std::endl;
                return *lessit * *greatit;
            }
        }
    }
    return -1;
}


day01::ExpenseReportTriple::ExpenseReportTriple(const std::string &filename) {
    readFileToVector(filename);
}

void day01::ExpenseReportTriple::readFileToVector(const std::string& filename) {
    std::ifstream source;
    source.open(filename);
    int64_t value;
    std::string line;
    while (std::getline(source, line)) {
        try {
            value = stol(line);
        } catch (const std::exception &e) {
            std::cout << "Error convert string to int64_t: " << e.what() << std::endl;
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

int64_t day01::ExpenseReportTriple::solution () {
    // Iterate greater
    for (auto greatit = std::begin(greaterThird); greatit != std::end(greaterThird); ++greatit) {
        // Value *greatit >= 1346
        for (auto lessit = std::begin(lesserThird); lessit != std::end(lesserThird); ++lessit) {
            // Value *lessit <= 673
            int64_t twoSum = *greatit + *lessit;
            if (twoSum < SUMVALUE) {
                for (auto lessit2 = lessit; lessit2 != std::end(lesserThird); ++lessit2) {
                    if (twoSum + *lessit2 == SUMVALUE) {
                        std::cout << "Values: " << *greatit << " + " << *lessit << " + " << *lessit2 << ";" << std::endl;
                        return *greatit * *lessit * *lessit2;
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
                for (auto lessit = std::begin(lesserThird); lessit != std::end(lesserThird); ++lessit) {
                    if (twoSum + *lessit == SUMVALUE) {
                        std::cout << "Values: " << *halfit << " + " << *halfit2 << " + " << *lessit << ";" << std::endl;
                        return *halfit * *halfit2 * *lessit;
                    }
                }
            }
        }

        for (auto lessit = std::begin(lesserThird); lessit != std::end(lesserThird); ++lessit) {
            int64_t twoSum = *halfit + *lessit;
            if (twoSum >= SecondThirdValue) {
                for (auto lessit2 = lessit; lessit2 != std::end(lesserThird); ++lessit2) {
                    if (twoSum + *lessit2 == SUMVALUE) {
                        std::cout << "Values: " << *halfit << " + " << *lessit << " + " << *lessit2 << ";" << std::endl;
                        return *halfit * *lessit * *lessit2;
                    }
                }
            }
        }
    }

    return -1;

}