/**
 * @file    day14.h
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    14 Dec 2024
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

namespace day14
{

    /**
     * Run the first problem
     * @param file input file
     * @return result
     */
    std::string process1(std::string file, uint64_t steps, uint64_t wide, uint64_t tall);

    /**
     * Run the second problem
     * @param file input file
     * @return result
     */
    std::string process2(std::string file);

} // namespace day14