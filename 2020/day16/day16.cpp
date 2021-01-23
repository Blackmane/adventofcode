/**
 * @file    day15.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    15 Dec 2020
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
#include <vector>


namespace day15 {

typedef std::vector<uint64_t> Ticket;

struct Constraint {
    struct Range {
        uint64_t from;
        uint64_t to;
        bool contain(uint64_t n) { return from <= n && n <= to;};
    };
    Range range1;
    Range range2;
};

class Tickets {
public:
    Tickets(std::string inputFilename);
    uint64_t getSolution();
    uint64_t getSolution2();
    void readConstrait(std::string line);
    void readMyTicket(std::string line);
    void readNearbyTicket(std::string line);

private:
    void toTicket(std::string line, Ticket* ticket);
    std::vector<Constraint> constraints;
    Ticket myTicket;
    std::vector<Ticket> nearbyTickets;
};

} // namespace day15


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    day15::Tickets tickets(inputFilename);
    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << tickets.getSolution() << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << tickets.getSolution2() << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

day15::Tickets::Tickets(std::string inputFilename) {
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    // Constraints
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            readConstrait(part);
        } else {
            break;
        }
    }
    // Ticket
    if (std::getline(source, part, '\n') 
        && part == "your ticket:"
        && std::getline(source, part, '\n')) {
        readMyTicket(part);
    }
    //Nearby tickets
    if (std::getline(source, part, '\n') 
        && std::getline(source, part, '\n') 
        && part == "nearby tickets:") {
        while (std::getline(source, part, '\n')) {
            if (part != "") {
                readNearbyTicket(part);
            } else {
                break;
            }
        }
    }
}


void day15::Tickets::readConstrait(std::string line) {
    uint64_t pos = 0;
    uint64_t stop = line.find(": ", pos);
    std::string type = line.substr(pos, stop-pos);
    pos = stop + 2;
    Constraint cons;
    stop = line.find("-", pos);
    cons.range1.from = std::stol(line.substr(pos, stop-pos));
    pos = stop +1;
    stop = line.find(" or ", pos);
    cons.range1.to = std::stol(line.substr(pos, stop-pos));
    pos = stop+4;
    stop = line.find("-", pos);
    cons.range2.from = std::stol(line.substr(pos, stop-pos));
    pos = stop+1;
    stop = line.length();
    cons.range2.to = std::stol(line.substr(pos, stop-pos));
// println(type << ": " << cons.range1.from << "-" << cons.range1.to << " or " << cons.range2.from << "-" << cons.range2.to)
    constraints.push_back(cons);
}


void day15::Tickets::toTicket(std::string line, Ticket* ticket) {
    uint64_t pos = 0;
    uint64_t stop = line.find(",", pos);
    while (stop != std::string::npos) {
        uint64_t num = std::stol(line.substr(pos, stop-pos));
        ticket->push_back(num);
        pos = stop + 1;
        stop = line.find(",", pos);
    }
    uint64_t num = std::stol(line.substr(pos, line.length()-pos));
    ticket->push_back(num);
}


void day15::Tickets::readMyTicket(std::string line) {
    toTicket(line, &myTicket);
}


void day15::Tickets::readNearbyTicket(std::string line) {
    Ticket ticket;
    toTicket(line, &ticket);
    nearbyTickets.push_back(ticket);
}


uint64_t day15::Tickets::getSolution() {
    uint64_t sum = 0;
    for(auto nTicket : nearbyTickets) {
        for(auto value : nTicket) {
            bool almostOne = false;
            for(auto cons : constraints) {
                if ( cons.range1.contain(value) || cons.range2.contain(value) ) {
                    almostOne = true;
                }
            }
            if (!almostOne) {
                sum += value;
            }
        }
    }
    return sum;
}


uint64_t day15::Tickets::getSolution2() {
    // Support
    size_t maxCons = constraints.size();
    size_t maxCol = nearbyTickets[0].size();
    size_t maxRow = nearbyTickets.size();
    
    // Consider only valid ticket
    std::list<uint64_t> valid; // Rows // NearbyTickets
    for (size_t row = 0; row < maxRow; row++) {
        bool isValid = true;
        for (auto value : nearbyTickets[row]) {
            bool almostOne = false;
            for (auto cons : constraints) {
                // Almost one must be contained
                if ( cons.range1.contain(value) || 
                    cons.range2.contain(value) ) {
                    almostOne = true;
                    break;
                }
            }
            // If no one is contained, drop
            if (!almostOne) {
                isValid = false;
                break;
            }
        }
        // All fields have almost one satisfied constraints
        if (isValid) {
            valid.push_back(row);
        }
    }
    
    // key: Constraint => list of columns
    std::unordered_map<uint64_t, std::list<uint64_t>*> possibleColumns; 
    // For every constraints
    for (size_t i = 0; i < maxCons; i++) {
        // For every column
        for (size_t col = 0; col < maxCol; col++) {
            // Check all row are valids
            bool allOk = true;
            for (auto row : valid) {
                if ( !constraints[i].range1.contain(nearbyTickets[row][col]) && 
                    !constraints[i].range2.contain(nearbyTickets[row][col]) ) {
                    // is not valid, drop
                    allOk = false;
                    break;
                }
            }
            // If are all valid
            if (allOk) {
                // Set as possible
                auto it = possibleColumns.find(i);
                if (it != possibleColumns.end()) {
                    // Already exists, add to list
                    it->second->push_back(col);
                } else {
                    // Not exists, create new list
                    std::list<uint64_t> *possibles = new std::list<uint64_t>;
                    possibles->push_back(col);
                    possibleColumns.insert(make_pair(i, possibles));
                }
            }
        }
    }

    std::vector<uint64_t> consToColumn(maxCons, 0); // Map: Constraint(id) => column

    bool allDone = false;
    while (!allDone) {
        uint64_t colToDelete;
        // Found possible with list size ==1
        for (auto possible : possibleColumns) {
            if (possible.second->size() <= 1) {
                if (possible.second->size() == 1) {
                    // Assign column as solution to constraints
                    consToColumn[possible.first] = possible.second->front();
                    // Save colum to remove from the other constraints list
                    colToDelete = consToColumn[possible.first];
                }
                // Delete entry
                delete possible.second;
                possible.second = nullptr;
                possibleColumns.erase(possible.first);
                // One found, process it
                break;
            }
            
        }
        // Again, in every possibile list
        for (auto possible : possibleColumns) {
            // If assigned column is present
            for (auto it = possible.second->begin(); it != possible.second->end(); ++it) {
                if (*it == colToDelete) {
                    // Remove column
                    possible.second->erase(it);
                    break;
                }
            }
        }
        // Terminate if all possibles are assigned
        allDone = possibleColumns.size() <= 0;
        // Protips: check in consToColumn if first six positions are valued
    }
    
    uint64_t mul = 1;
    // "departure*" are the first six
    for (size_t i = 0; i < 6; i++) {
        mul *= myTicket[consToColumn[i]];
    }
    return mul;
}