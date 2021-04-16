/**
 * @file    day08.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    08 Dec 2020
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
#include <functional>
#include <vector>

namespace day08 {
/*
There isn't much to say.
Just read istructions and execute them.
In part 2 I try to modify one instruction at a time and check that there are no more loops.
A better solution could be to try to modify the istruction only when a loop is found.

I expect this to be taken up again in the next problems.
*/

enum OperationId {
    acc,
    jmp,
    nop
};

struct Instruction  {
    bool done = false;
    OperationId id;
    int64_t value;
};


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

int64_t process1(std::string file);
int64_t process2(std::string file);

int64_t execute (std::vector<Instruction> &program);
bool terminate (std::vector<Instruction> &program);
int64_t correctAndExecute (std::vector<Instruction> &program);


// ===== ===== ===== Lambdas ===== ===== ===== 

auto toInstruction = [](std::string part) -> Instruction { 
    Instruction istr;
    // Read operation id
    std::string name = part.substr(0, 3);
    if (name == "acc") {
        istr.id = acc;
    } else if (name == "jmp") {
        istr.id = jmp;
    } else { // nop
        istr.id = nop;
    }
    // Read value (eventually negative)
    bool neg = part.substr(4, 1) == "-";
    uint64_t value = std::stoi(part.substr(5, part.length()-5));
    istr.value = neg ? value * -1 : value;

    return istr;
};


auto insert = [](Instruction instruction, std::vector<Instruction> * program) {
    program->push_back(instruction);
};


} // namespace day08


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day08::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day08::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

int64_t day08::process1(std::string file) {
    std::vector<Instruction> program;
    read<Instruction, std::vector<Instruction>*>(file, '\n', toInstruction, insert, &program);

    int64_t result = execute(program);
    return result;
}

int64_t day08::process2(std::string file) {
    std::vector<Instruction> program;
    read<Instruction, std::vector<Instruction>*>(file, '\n', toInstruction, insert, &program);

    return correctAndExecute(program);
}


int64_t day08::execute(std::vector<Instruction> &program) {
    int64_t accumulator = 0;
    size_t i = 0;
    bool end = false;
    while (!end && i < program.size()) {
        size_t increment = 1;
        // Check loop
        if (!program[i].done) {
            // Execute operation
            switch (program[i].id) {
                case acc:
                    accumulator += program[i].value;
                    break;
                case jmp:
                    increment = program[i].value;
                    break;
                default:
                    break;
            }
        } else {
            // Loop found, terminate
            end = true;
        }
        // Update istruction and set next
        program[i].done = true;
        i += increment;
    }
    
    return accumulator;
}


bool day08::terminate (std::vector<Instruction> &program) {
    std::vector<bool> dones(program.size(), false);
    size_t i = 0;
    // Must terminate with last one instruction
    while (i < program.size()) {
        size_t increment = 1;
        if (!dones[i]) {
            // Necessary execute only jump operations
            if (program[i].id == jmp) {
                increment = program[i].value;
            }
        } else {
            return false;
        }
        dones[i] = true;
        i += increment;
    }
    
    return true;
}


int64_t day08::correctAndExecute(std::vector<Instruction> &program) {
    for (size_t i = 0; i < program.size(); i++) {
        // Change nop into jump
        if (program[i].id == nop && program[i].value != 0) {
            program[i].id = jmp;
            // If modified it terminate then execute
            if (terminate(program)) {
                return execute(program);
            } else {
                // Restore operation
                program[i].id = nop;
            }
        } else if (program[i].id == jmp) {
            // Change jmp into nop
            program[i].id = nop;
            if (terminate(program)) {
                return execute(program);
            } else {
                // Restore operation
                program[i].id = jmp;
            }
        }
    }
    return -1;
}