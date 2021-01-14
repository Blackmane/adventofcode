/**
 * @file    day24.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    13 Gen 2020
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
#include <set>
#include <unordered_set>
#include <string>
#include <unordered_map>


namespace day24 {

struct Position {
    int32_t x = 0;
    int32_t y = 0;
    void ne() { y++; };
    void e()  { x++; };
    void se() { y--; x++; };
    void sw() { y--; };
    void w()  { x--; };
    void nw() { y++; x--; };
    bool operator< (const Position& rPos) const {
        if (x == rPos.x) {
            return y < rPos.y;
        }
        return x < rPos.x;
    };
    bool operator== (const Position& rPos) const { 
        return x == rPos.x && y == rPos.y; 
    } 
};

class PositionHash { 
public: 
    size_t operator()(const Position& pos) const { 
        union Hasher {
            struct Pos {
                int32_t x;
                int32_t y;
            } pos;
            size_t result;
        };
        Hasher h;
        h.pos.x = pos.x;
        h.pos.y = pos.y;
        return h.result;
    } 
}; 

typedef std::unordered_set<Position, PositionHash> Flipped;
typedef std::unordered_map<Position, uint64_t, PositionHash> HitTable;

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

void runFlipDay(Flipped* flipped, uint64_t days);
void addToHitTable(HitTable * hitTable, Position& pos);

// ===== ===== ===== Lambdas ===== ===== ===== 

auto move = [](std::string part) -> Position { 
    Position pos;
    bool nord = false;
    bool sud = false;
    for (auto c : part) {
        switch (c) {
        case 'e':
            if (nord) {
                pos.ne();
                nord = false;
            } else if (sud) {
                pos.se();
                sud = false;
            } else {
                pos.e();
            }
            break;
        case 'w':
            if (nord) {
                pos.nw();
                nord = false;
            } else if (sud) {
                pos.sw();
                sud = false;
            } else {
                pos.w();
            }
            break;
        case 's':
            sud = true;
            break;
        case 'n':
            nord = true;
            break;
        default:
            break;
        }
    }
    return pos;
};

auto flip = [](Position pos, Flipped * flipped) {
    auto it = flipped->find(pos);
    if (it != flipped->end()) {
        // Already flipped, turn white
        flipped->erase(it);
    } else {
        // Not flipped, flip
        flipped->emplace(pos);
    }
};


} // namespace day24


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day24::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day24::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day24::process1(std::string file) {
    Flipped flipped;
    read<Position, Flipped*>(file, '\n', 
                move, 
                flip, &flipped);

    uint64_t result = flipped.size();
    return result;
}


uint64_t day24::process2(std::string file) {
    Flipped flipped;
    read<Position, Flipped*>(file, '\n', 
                move, 
                flip, &flipped);
    runFlipDay(&flipped, 100);
    uint64_t result = flipped.size();
    return result;
}

// ===== ===== ===== Implementations ===== ===== ===== 


void day24::runFlipDay(Flipped* flipped, uint64_t days) {
    for (size_t i = 0; i < days; i++) {
        // Count neighbors for every tile
        HitTable hitTiles;
        for (auto& tile : *flipped) {
            // If tile not already hitted add with 0 hit, so is possibile remove it
            auto it = hitTiles.find(tile);
            if (it == hitTiles.end()) {
                hitTiles.insert(std::make_pair(tile, 0));
            }
            // Check nearby neighbors
            Position neighbor = tile;
            neighbor.ne();
            addToHitTable(&hitTiles, neighbor);
            neighbor = tile;
            neighbor.e();
            addToHitTable(&hitTiles, neighbor);
            neighbor = tile;
            neighbor.se();
            addToHitTable(&hitTiles, neighbor);
            neighbor = tile;
            neighbor.sw();
            addToHitTable(&hitTiles, neighbor);
            neighbor = tile;
            neighbor.w();
            addToHitTable(&hitTiles, neighbor);
            neighbor = tile;
            neighbor.nw();
            addToHitTable(&hitTiles, neighbor);
        }
        // Flip
        for (auto& hit : hitTiles) {
            auto it = flipped->find(hit.first);
            if (it != flipped->end()) {
                // Black tile
                if (hit.second == 0 || hit.second > 2) {
                    // Flipped to white
                    flipped->erase(it);
                }
            } else {
                // White tile
                if (hit.second == 2) {
                    // Insert as black
                    flipped->emplace(hit.first);
                }
            }
        }
    }
}

void day24::addToHitTable(HitTable * hitTiles, Position& pos) {
    auto it = hitTiles->find(pos);
    if (it != hitTiles->end()) {
        it->second++;
    } else {
        hitTiles->insert(std::make_pair(pos, 1));
    }
}