/**
 * @file    day15.h
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    15 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include <stdint.h>
#include <string>

namespace day15
{

    /**
     * Run the first problem
     * @param file input file
     * @return result
     */
    std::string process1(std::string file);
    std::string test1(std::string file);

    /**
     * Run the second problem
     * @param file input file
     * @return result
     */
    std::string process2(std::string file);
    std::string test2(std::string file);

} // namespace day15