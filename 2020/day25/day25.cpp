/**
 * @file    day25.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    23 Gen 2021
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

#include <iostream>
#include <vector>


namespace day25 {

class Transformer {
public:
    Transformer(uint64_t subjectNumber, uint64_t limit = 20201227);
    uint64_t getLoop(uint64_t key);
    uint64_t getKey(uint64_t loop);
private:
    uint64_t _value;
    uint64_t _subjectNumber;
    uint64_t _limit;
    std::vector<uint64_t> _transformed;
};

uint64_t process1();

} // namespace day25


// ===== ===== ===== Main ===== ===== ===== 
int main () {

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day25::process1() << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day25::process1() {
    uint64_t card = 14222596;
    uint64_t door = 4057428;

    Transformer transformer(7);
    Transformer transformerKey(card);
    uint64_t result = transformerKey.getKey(transformer.getLoop(door));
    return result;
}

// ===== ===== ===== Implementations ===== ===== ===== 

day25::Transformer::Transformer(uint64_t subjectNumber, uint64_t limit) {
    _subjectNumber = subjectNumber;
    _limit = limit;
    _transformed.push_back(1);
}

uint64_t day25::Transformer::getLoop(uint64_t key) {
    size_t max = _transformed.size();
    size_t i = 0;
    while (i < max) {
        if (_transformed[i] == key) {
            return i;
        }
        i++;
    }
    uint64_t v = _transformed[i-1];
    while (v != key) {
        v *= _subjectNumber;
        v %= _limit;
        _transformed.push_back(v);
        i++;
    }
    return i-1;
}

uint64_t day25::Transformer::getKey(uint64_t loop) {
    if (loop < _transformed.size()) {
        return _transformed[loop];
    }
    size_t i = _transformed.size() - 1;
    uint64_t v = _transformed[i];
    while (i <= loop) {
        v *= _subjectNumber;
        v %= _limit;
        _transformed.push_back(v);
        i++;
    }
    return _transformed[loop];
}