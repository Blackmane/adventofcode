/**
 * @file    day04.cpp
 * @brief   
 * @project advent of code
 * 
 * @author  Niccolò Pieretti
 * @date    22 Mar 2021
 * 
 ****************************************************************************-
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
#include <functional>
#include <openssl/md5.h>

namespace day04 {

uint64_t process1(std::string input);
uint64_t process2(std::string input);

uint64_t findSolution();

void compute_md5(const char *str, size_t strlen, unsigned char digest[16]);

uint64_t md5FinderTh(std::string input);
uint64_t md5FinderTh2(std::string input);

} // namespace day04


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day04::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day04::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day04::process1(std::string input) {
    return md5FinderTh(input);
}


uint64_t day04::process2(std::string input) {
    return md5FinderTh2(input);
}


uint64_t day04::md5FinderTh(std::string input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    bool found = false;
    for (auto current = 0; !found; current++) {
        auto toMd5 = input + std::to_string(current);
        compute_md5(toMd5.c_str(), toMd5.length(), digest);
        if (digest[0] == 0 &&
            digest[1] == 0 &&
            digest[2] < 8 ) {
            found = true;
            return current;
        }
    }
    return 0;
}


uint64_t day04::md5FinderTh2(std::string input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    bool found = false;
    for (auto current = 0; !found; current++) {
        auto toMd5 = input + std::to_string(current);
        compute_md5(toMd5.c_str(), toMd5.length(), digest);
        if (digest[0] == 0 &&
            digest[1] == 0 &&
            digest[2] == 0 ) {
            found = true;
            return current;
        }
    }
    return 0;
}


void day04::compute_md5(const char *str, size_t strlen, unsigned char digest[16]) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, str, strlen);
    MD5_Final(digest, &ctx);
}
