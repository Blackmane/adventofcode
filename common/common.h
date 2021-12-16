/**
 * @file    common.h
 * @brief   Common library for AoC
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

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define print(SOMETHING) std::cout << SOMETHING;
#define println(SOMETHING) std::cout << SOMETHING << std::endl;

// TODO: add tests for common lib

namespace parse
{
    /**
     * Read a file
     * @tparam S structure where to save the file
     * @param inputFilename
     * @param delimiter
     * @param insert
     * @param structure
     */
    template<class S>
    void read(std::string inputFilename, char delimiter,
            std::function<void(S, std::string)> insert, S structure)
    {
        std::ifstream source;
        source.open(inputFilename, std::ifstream::in);
        std::string part;
        while (std::getline(source, part, delimiter)) {
            insert(structure, part);
        }
    }

    /**
     * Read a file and apply a conversion to the string read
     * @tparam T transient type
     * @tparam R result type
     * @param inputFilename path to the file
     * @param delimiter delimeter of the string
     * @param convert apply a conversion from string to T
     * @param insert
     * @param structure
     */
    template<class T, class R>
    void read(std::string inputFilename, char delimiter,
            std::function<T(std::string)> convert,
            std::function<void(T, R)> insert, R structure)
    {
        std::ifstream source;
        source.open(inputFilename, std::ifstream::in);
        std::string part;
        while (std::getline(source, part, delimiter)) {
            insert(convert(part), structure);
        }
    }

    /**
     * Apply the push back to the vector
     * @param list
     * @param part string to push back
     */
    void push_back(std::vector<std::string> *list, std::string part);

    /**
     * Apply the push back of a string to the vector of integer
     * @param list
     * @param part string to convert to integer and push back
     */
    void push_back_integer(std::vector<uint64_t> *list, std::string part);

    /**
     * Read the entire file as is and store it in a vector of strings
     * @param inputFilename the path to the file
     * @param list the structure where to save the file
     */
    void read_all(std::string &inputFilename, std::vector<std::string> *list);

    /**
     * Read the entire file as is and store it in a set of strings
     * @param inputFilename the path to the file
     * @param set the structure where to save the file
     */
    void read_all_ordered(std::string &inputFilename, std::set<std::string> *set);

    /**
     * Read the entire file as there are integers
     * @param inputFilename
     * @param list
     */
    void read_all_integers(std::string &inputFilename, std::vector<uint64_t> *list);

    /**
     * Get the first integer of the line
     * @param line a string
     * @return the first integer
     */
    uint64_t getInteger(std::string &line);

    /**
     * Get all the integers of the line
     * @param line a string
     * @return an ordered array of integers
     */
    std::vector<uint64_t> getIntegers(std::string &line);

    /**
     * Split a string input by a char separator
     * @param input string to split
     * @param separator
     * @return an vector of string separated from input
     */
    std::vector<std::string> split(std::string input, char separator);

} // namespace parse

namespace convert
{
    /**
     * Convert a string of binary to a integer.
     * Example: from 101110 get 46
     * @param binary a reference to a string
     */
    uint64_t fromBinary(std::string &binary);

} // namespace convert

namespace op
{
    /**
     * @brief Increase the current key of quantity value if it exists, else insert
     *
     * @tparam M map type
     * @tparam K key type
     * @tparam V value type
     * @param key key to modify
     * @param quantity value to increment
     */
    template<class K, class V> void increaseOrInsert(std::map<K, V> *map, K key, V quantity)
    {
        auto it = map->find(key);
        if (it == map->end()) {
            map->insert(std::make_pair(key, quantity));
        } else {
            it->second += quantity;
        }
    }
} // namespace op

namespace matrix
{
    /**
     * @brief return the list of orthogonal neighbours
     *
     * @param i current vertical position
     * @param j current horizontal position
     * @param height vertical length
     * @param width horizontal length
     * @return std::vector<std::pair<size_t, size_t>> the list of neighbours
     */
    std::vector<std::pair<size_t, size_t>> neighbours4(size_t i, size_t j, size_t height, size_t width);

} // namespace matrix