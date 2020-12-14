/**
 * @file    day13.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    13 Dec 2020
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
#include <vector>

namespace day13 {

struct Wait {
    int bus = 0;
    uint64_t time = 0;
};

struct Bus {
    uint64_t id = 0;
    uint64_t distance = 0;
    void set(uint64_t nid, uint64_t ndistance) {id = nid; distance = ndistance;};
};

template<class H, class L, class R>
R parseHeader(std::string inputFilename, char delimiter, 
        std::function <H(std::string)> convertHeader, 
        std::function <L(std::string)> convertLine, 
        std::function <R(H, L, R)> foldl, R accumulatorValue) {
    
    std::ifstream source;
    source.open(inputFilename);
    R accumulator = accumulatorValue;
    std::string part;
    if (std::getline(source, part, delimiter)) {
        H header = convertHeader(part);
        while (std::getline(source, part, delimiter)) {
            accumulator = foldl(header, convertLine(part), accumulator);
        }
    }
    return accumulator ;
}

uint64_t process1(std::string file);
uint64_t process2(std::string file);

uint64_t multiplicativeInverse(uint64_t coeff, uint64_t module);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto toTime = [](std::string part) -> uint64_t {
    uint64_t time = stol(part);
    return time;
};

auto toBuses = [](std::string part) -> std::vector<uint64_t> {
    std::vector<uint64_t> busList;
    std::size_t pos = 0;
    std::size_t comma = part.find(',');
    while (comma != std::string::npos) {
        std::string bus = part.substr(pos, comma-pos);
        if (bus != "x") {
            uint64_t busNumber = stol(bus);
            busList.push_back(busNumber);
        }
        // Step forward
        pos = comma + 1;
        comma = part.find(',', pos);
    }
    // Last bus
    std::string bus = part.substr(pos, part.length()-pos+1);
    if (bus != "x") {
        uint64_t busNumber = stol(bus);
        busList.push_back(busNumber);
    }
    return busList;
};

auto foldl = [](uint64_t time, std::vector<uint64_t> listBus, Wait wait) -> Wait { 
    Wait minWait(wait);
    for (auto bus : listBus) {
        uint64_t transits = time / bus;
        uint64_t waitTime = ((transits+1) * bus) - time;
        if  (waitTime < wait.time || wait.bus == 0) {
            wait.bus = bus;
            wait.time = waitTime;
        }
    }
    return wait;
};


auto toBuses2 = [](std::string part) -> std::vector<Bus> {
    std::vector<Bus> busList;
    uint64_t distance = 0;
    std::size_t pos = 0;
    std::size_t comma = part.find(',');
    while (comma != std::string::npos) {
        std::string bus = part.substr(pos, comma-pos);
        if (bus != "x") {
            Bus busData;
            busData.set(stol(bus), distance);
            busList.push_back(busData);
            distance = 0;
        }
        // Step forward
        distance++;
        pos = comma + 1;
        comma = part.find(',', pos);
    }
    // Last bus
    std::string bus = part.substr(pos, part.length()-pos+1);
    if (bus != "x") {
        Bus busData;
        busData.set(stol(bus), distance);
        busList.push_back(busData);
    }
    return busList;
};

auto chineseRemainerTh = [](uint64_t time, std::vector<Bus> listBus, uint64_t voif) -> uint64_t { 
    uint64_t product = 1;
    uint64_t distance = 0;
    for(auto bus : listBus) {
        product *= bus.id;
    }
    uint64_t result = 0;
    for(auto bus : listBus) {
        distance += bus.distance;
        uint64_t coeff = product / bus.id;
        uint64_t Y = multiplicativeInverse(coeff, bus.id);
        result += (bus.id - (distance % bus.id)) * coeff * Y;
    }
    return result % product;
};

} // namespace day13

// ===== ===== ===== Implementations ===== ===== ===== 
uint64_t day13::multiplicativeInverse(uint64_t coeff, uint64_t module) {
    // C * X = 1 mod N
    uint64_t value = coeff % module;
    for (uint64_t x = 1; x < module; x++) {
        if ( (value * x) % module == 1) {
            return x;
        }
    }
    return 0;
}


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day13::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day13::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Solutions ===== ===== ===== 

uint64_t day13::process1(std::string file) {
    Wait waitZero;
    Wait result = parseHeader<uint64_t, std::vector<uint64_t>, Wait>(file, '\n', 
                            toTime, 
                            toBuses, 
                            foldl, waitZero);
    return result.bus * result.time;
}

uint64_t day13::process2(std::string file) {
    uint64_t result = parseHeader<uint64_t, std::vector<Bus>, uint64_t>(file, '\n', 
                            toTime, 
                            toBuses2, 
                            chineseRemainerTh, 1);
    return result;
}