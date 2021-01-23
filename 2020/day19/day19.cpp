/**
 * @file    day19.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    19 Dec 2020
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
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <vector>


namespace day19 {

const uint64_t MAXNUMBER = 134;
const uint64_t RULE_START = 0;

struct Rule {
    std::vector<std::vector<uint64_t>> *subrules = nullptr;
    std::string solution = "";
    bool isSolved = true;
};

typedef std::vector<Rule> Rules;


class RulesProcessor {
public:
    RulesProcessor();
    void load(std::string inputFilename);
    uint64_t solution = 0;
protected:
    std::pair<uint64_t, Rule> toRule (std::string part);
    std::string getRegex(uint64_t ruleId);
    Rules rules;
};


class RulesProcessor2 : public RulesProcessor {
public:
    RulesProcessor2();
    void load(std::string inputFilename);
private:
    std::string getRegex(uint64_t ruleId);
    bool symmetrical(std::string part, std::string full, std::string regex1, std::string regex2);
};


uint64_t process1(std::string file);
uint64_t process2(std::string file);

// ===== ===== ===== Lambdas ===== ===== ===== 


} // namespace day19


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day19::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day19::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day19::process1(std::string file) {

    RulesProcessor rulesProcessor;
    rulesProcessor.load(file);
    return rulesProcessor.solution;
}


uint64_t day19::process2(std::string file) {
    RulesProcessor2 rulesProcessor;
    rulesProcessor.load(file);
    return rulesProcessor.solution;
}


// ===== ===== ===== Implementations ===== ===== ===== 

day19::RulesProcessor::RulesProcessor() : rules(MAXNUMBER+1) {}


void day19::RulesProcessor::load(std::string inputFilename) {
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    // Load rules
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            auto rule = toRule(part);
            rules[rule.first] = rule.second;
        } else {
            break;
        }
    }
    // Generate regex
    std::string regex = getRegex(RULE_START);
    // Second part
    uint64_t valid = 0;
    while (std::getline(source, part, '\n')) {
        if (std::regex_match (part, std::regex(regex) )) {
            valid++;
        }
    }
    solution = valid;
}

std::pair<uint64_t, day19::Rule> day19::RulesProcessor::toRule (std::string part) {
    Rule rule;
    size_t pos = 0;
    size_t stop = part.find(": ", pos);
    size_t id = std::stol(part.substr(pos, stop-pos));
    pos = stop + 2;
    stop = part.find('"', pos);
    if (stop != std::string::npos) {
        pos = stop+1;
        stop = part.find('"', pos);
        rule.solution = part.substr(pos, stop-pos);
        rule.isSolved = true;
    } else {
        std::vector<std::vector<uint64_t>> * subrules = new std::vector<std::vector<uint64_t>>(2);
        uint64_t ref;
        auto j = 0;
        size_t half;
        do {
            half = part.find(" | ", pos);
            if (half == std::string::npos) {
                half = part.length();
            }
            auto i = 0;
            stop = part.find(' ', pos);
            std::vector<uint64_t> ids;
            while (stop < half) {
                ref = std::stol(part.substr(pos, stop-pos));
                ids.push_back(ref);
                pos = stop + 1;
                stop = part.find(' ', pos);
                i++;
            }
            ref = std::stol(part.substr(pos, half-pos));
            ids.push_back(ref);
            (*subrules)[j] = ids;
            pos = stop + 3;
            j++;
        } while ( half < part.length() );
        rule.subrules = subrules;
        rule.isSolved = false;
    }
    return std::make_pair(id, rule); 
}

std::string day19::RulesProcessor::getRegex(uint64_t ruleId) {
    Rule rule = rules[ruleId];
    if (rule.isSolved) {
        return rule.solution;
    } else {
        std::string regex = "";
        for ( auto sub : (*rule.subrules) ) {
            std::string part = "";
            for (auto id : sub) {
                part += getRegex(id);
            }
            if (part != "") {
                regex += part + "|";
            }
        }
        return "(" + regex.substr(0, regex.length()-1) + ")";
    }
}


day19::RulesProcessor2::RulesProcessor2() : RulesProcessor() {}


void day19::RulesProcessor2::load(std::string inputFilename) {
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    // Load rules
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            auto rule = toRule(part);
            rules[rule.first] = rule.second;
        } else {
            break;
        }
    }
    // Generate regex
    std::string regex = getRegex(RULE_START);
    std::string regex31 = getRegex(31);
    std::string regex42 = getRegex(42);
    // Second part
    uint64_t valid = 0;
    while (std::getline(source, part, '\n')) {
        if (std::regex_match (part, std::regex(regex) )) {
            if (symmetrical(part, regex, regex42, regex31)) {
                valid++;
            }
        }
    }
    solution = valid;
}

std::string day19::RulesProcessor2::getRegex(uint64_t ruleId) {
    if (ruleId != 8 && ruleId != 11) {
        Rule rule = rules[ruleId];
        if (rule.isSolved) {
            return rule.solution;
        } else {
            std::string regex = "";
            for ( auto sub : (*rule.subrules) ) {
                std::string part = "";
                for (auto id : sub) {
                    part += getRegex(id);
                }
                if (part != "") {
                    regex += part + "|";
                }
            }
            return "(" + regex.substr(0, regex.length()-1) + ")";
        }
    } else {
        if (ruleId == 8) {
            return "(" + getRegex(42) + ")+";
        } else {
            return "(" + getRegex(42) + ")+(" + getRegex(31) + ")+";
        }
    }
}

bool day19::RulesProcessor2::symmetrical(std::string part, std::string full, std::string regex1, std::string regex2) {
    // 0: 8 11 => 42(42)+(31)+
    // 8: 42      | 42 8
    // 11: 42 31  | 42 11 31
    std::smatch matches; 
    std::regex_search(part, matches, std::regex("^(" + regex1 + ")+"));
    uint64_t m1len = matches.length();
    std::regex_search(part, matches, std::regex("(" + regex2 + ")+$"));
    uint64_t m2len = matches.length();

    return m1len > m2len;
}