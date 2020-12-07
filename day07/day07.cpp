/**
 * @file    day07.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    05 Dec 2020
 * @bug     
 * @todo    
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
#include <list>
#include <unordered_map>
#include <set>

namespace day07 {
/*
A more complex problem, but not difficult on paper.
Write the parser for input is still a time consuming task
and debugging the problems in a short time was not easy.

The immediate idea could have been to build a graph of bags, connected by relation "is contained".
I preferred to save the graph arcs (is contained relation) as an entry to a key-value map.
I believe the solution is equivalent.

Part1: the map is <bag, bags in which is contained>
Part2: the map is <bag, contained bags> (with quantity)
*/

template<class T, class R>
void read(std::string inputFilename, char delimiter, 
        std::function <T(std::string)> convert, 
        std::function <void(T, R)> insert, R structure) {
    
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    while (std::getline(source, part, delimiter)) {
        insert(convert(part), structure);
    }
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

typedef std::set<std::string> BagWrapper;
typedef std::list<std::pair<uint64_t, std::string>> BagContent;
typedef std::pair<std::string, BagContent*> ConvertedLine;
typedef std::unordered_map<std::string, BagWrapper*> AllWrappers;
typedef std::unordered_map<std::string, BagContent*> AllBags;

uint64_t countWrappers(AllWrappers *);
uint64_t countBags(AllBags *);

// ===== ===== ===== Lambdas ===== ===== ===== 

std::pair<uint64_t, std::string> readBag(std::string part) {
    // Format: "n firstColor secondColor"
    int n = std::atoi(&part[0]);
    int remove = 6;
    if (n>1) {
        remove++;
    }
    return std::make_pair(n, part.substr(2, part.length()-remove));
}

auto convertToBag = [](std::string line) -> ConvertedLine {
    BagContent *content = new BagContent();
    // Read bag's color
    std::string delimeterB = " bags contain ";
    std::size_t pos = line.find(delimeterB);
    std::string bag = line.substr(0, pos);
    pos += delimeterB.length();
    // Read content of bag
    if (line.substr(pos) != "no other bags.") {
        std::string delimeterC = ", ";
        std::size_t comma = line.find(delimeterC, pos);
        while (comma != std::string::npos) {
            auto bagContent = readBag(line.substr(pos, comma-pos));
            content->push_back(bagContent);
            // Step forward
            pos = comma + delimeterC.length();
            comma = line.find(delimeterC, pos);
        }
        // Last bag
        auto bagContent = readBag(line.substr(pos, line.length()-pos-1));
        content->push_back(bagContent);
    }
    // else: empty content

    return std::make_pair(bag, content);
};

auto wrapper_insert = [](ConvertedLine bag, day07::AllWrappers * allwrappers) {
    std::string wrapper = bag.first;
    BagContent *content = bag.second;
    // Create entry if the bag is not present yet
    auto wrapIt = allwrappers->find(wrapper);
    if (wrapIt == allwrappers->end()) {
        BagWrapper * bagsWrapper = new BagWrapper();
        // Empty list of containers
        allwrappers->emplace(std::make_pair(wrapper, bagsWrapper));
    }
    // For each contained bag 
    for (auto it = content->begin(); it != content->end(); it++) {
        auto bags = allwrappers->find(it->second);
        if (bags != allwrappers->end()) {
            // Add to entry
            BagWrapper * bagsWrapper = bags->second;
            bagsWrapper->insert(wrapper);
        } else {
            // Create entry
            BagWrapper * bagsWrapper = new BagWrapper();
            bagsWrapper->insert(wrapper);
            allwrappers->emplace(std::make_pair(it->second, bagsWrapper));
        }
    }
};

auto bag_insert = [](ConvertedLine bag, day07::AllBags * allbags) {
    allbags->emplace(bag);
};


} // namespace day07


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day07::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day07::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day07::countWrappers(AllWrappers * allwrappers) {
    // Shiny gold must not be counted, so start to count from -1
    uint64_t count = -1;
    std::list<std::string> queue;
    queue.push_back("shiny gold");
    while (queue.size() > 0) {
        auto wrappers = allwrappers->find(queue.front());
        if (wrappers != allwrappers->end()) {
            // New colour, count it
            count++;
            // Save containers of bag
            std::set<std::string>* bagsList = wrappers->second;
            for (auto it = bagsList->begin(); it != bagsList->end(); ++it) {
                queue.push_back(*it);
            // Remove this colour
            }
            allwrappers->erase(wrappers);
        }
        // else: bag's colour already counted
        queue.pop_front();
    }
    return count;
}

uint64_t day07::countBags(AllBags * allbags) {
    // Shiny gold must not be counted, so start to count from -1
    uint64_t count = -1;
    // Must save multiplier value
    std::list<std::pair<std::string, uint64_t>> queue;
    queue.push_back(std::make_pair("shiny gold", 1));
    while (queue.size() > 0) {
        std::string bag = queue.front().first;
        uint64_t mul = queue.front().second;
        // Every bag must be count
        count += mul;
        auto bags = allbags->find(bag);
        if (bags != allbags->end()) {
            // Save contained bags, updating multiplier value
            BagContent* bagsList = bags->second;
            for (auto it = bagsList->begin(); it != bagsList->end(); ++it) {
                queue.push_back(std::make_pair(it->second, mul*it->first));
            }
        }
        queue.pop_front();
    }
    return count;
}

uint64_t day07::process1(std::string file) {
    AllWrappers allwrappers;
    read<ConvertedLine, AllWrappers*>(
                file, '\n', 
                convertToBag, 
                wrapper_insert, &allwrappers);

    return countWrappers(&allwrappers);
}

uint64_t day07::process2(std::string file) {
    AllBags allbags;
    read<ConvertedLine, AllBags*>(
                file, '\n', 
                convertToBag, 
                bag_insert, &allbags);

    return countBags(&allbags);
}