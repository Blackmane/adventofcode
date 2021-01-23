/**
 * @file    day17.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    17 Dec 2020
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


namespace day17 {

const size_t Iteractions = 6;
const size_t Borders = 7;

template <class T>
class Array3D {
    std::vector<T> data;
public:
    const size_t sizeX, sizeY, sizeZ;
    uint64_t count = 0; // active cubes
public:
    Array3D(size_t x, size_t y, size_t z, T init):
        data(x*y*z, init), sizeX(x), sizeY(y), sizeZ(z) {}

    T get(size_t x, size_t y, size_t z) const {
        return data.at(x + y * sizeX + z * sizeX * sizeY);
    }

    void set(size_t x, size_t y, size_t z, T value) {
        data[x + y * sizeX + z * sizeX * sizeY] = value;
    }
};


template <class T>
class Array4D {
    std::vector<T> data;
public:
    const size_t sizeX, sizeY, sizeZ, sizeW;
    uint64_t count = 0; // active cubes
public:
    Array4D(size_t x, size_t y, size_t z, size_t w, T init):
        data(x*y*z*w, init), sizeX(x), sizeY(y), sizeZ(z), sizeW(w) {}

    T get(size_t x, size_t y, size_t z, size_t w) const {
        return data.at(x + y * sizeX + z * sizeX * sizeY + w * sizeX * sizeY * sizeZ);
    }

    void set(size_t x, size_t y, size_t z, size_t w, T value) {
        data[x + y * sizeX + z * sizeX * sizeY + w * sizeX * sizeY * sizeZ] = value;
    }
};


template<class T, class R>
void readAsIs(std::string inputFilename, char delimiter, 
        std::function <void(T, R)> insert, R structure) {
    
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    while (std::getline(source, part, delimiter)) {
        insert(part, structure);
    }
}


uint64_t process1(std::string file);
uint64_t process2(std::string file);


Array3D<bool>* iterate3D(Array3D<bool>* const space);
uint64_t nearbyActive3D(Array3D<bool>* const space, size_t x, size_t y, size_t z);
Array3D<bool>* inputToSpace3D(std::vector<std::string> * input);

Array4D<bool>* iterate4D(Array4D<bool>* const space);
uint64_t nearbyActive4D(Array4D<bool>* const space, size_t x, size_t y, size_t z, size_t w);
Array4D<bool>* inputToSpace4D(std::vector<std::string> * input);


// ===== ===== ===== Lambdas ===== ===== ===== 

auto insert = [](std::string line, std::vector<std::string> * list) {
    list->push_back(line);
};


} // namespace day17


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day17::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day17::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day17::process1(std::string file) {
    std::vector<std::string> input;
    readAsIs<std::string, std::vector<std::string>*>(file, '\n', insert, &input);

    Array3D<bool>* space = inputToSpace3D(&input);

    for (size_t i = 0; i < Iteractions; i++) {
        Array3D<bool>* newSpace = iterate3D(space);
        delete space;
        space = newSpace;
    }
    uint64_t solution = space->count;    
    delete space;
    return solution;
}


uint64_t day17::process2(std::string file) {
    std::vector<std::string> input;
    readAsIs<std::string, std::vector<std::string>*>(file, '\n', insert, &input);

    Array4D<bool>* space = inputToSpace4D(&input);
    for (size_t i = 0; i < Iteractions; i++) {
        Array4D<bool>* newSpace = iterate4D(space);
        delete space;
        space = newSpace;
    }
    uint64_t solution = space->count;    
    delete space;
    return solution;
}


// ===== ===== ===== Implementations 3D ===== ===== ===== 


uint64_t day17::nearbyActive3D(Array3D<bool>* const space, size_t x, size_t y, size_t z) {
    uint64_t near = 0;
    const size_t dirSize = 3;
    int directions[dirSize] = {-1, 0, 1};
    // Iterate directions
    for (size_t xi = 0; xi < dirSize; xi++) {
        for (size_t yi = 0; yi < dirSize; yi++) {
            for (size_t zi = 0; zi < dirSize; zi++) {
                if (xi != 1 || yi != 1 || zi != 1) {
                    // Don't check the same spot
                    int64_t posx = x + directions[xi];
                    int64_t posy = y + directions[yi];
                    int64_t posz = z + directions[zi];
                    // Count if nearby is active
                    if (space->get(posx, posy, posz) == true) {
                        near++;
                    }
                }
            }
        }
    }
    return near;
}

day17::Array3D<bool>* day17::inputToSpace3D(std::vector<std::string> * input) {
    size_t border = Borders * 2;
    size_t halfborder = Borders / 2;
    size_t maxRow = input->size();
    size_t maxCol = (*input)[0].length();
    // Allocate space
    Array3D<bool>* space = new Array3D<bool>(
                                maxRow + border, // X
                                maxCol + border, // Y
                                border+1,        // Z
                                false);
    // Copy input
    for (size_t row = 0; row < maxRow; row++) {
        for (size_t col = 0; col < maxCol; col++) {
            if ( (*input)[row][col] == '#' ) {
                // # means active
                space->set(row + Borders, col + Borders, halfborder, true);
                space->count++;
            }
        }
    }
    return space;
}

day17::Array3D<bool>* day17::iterate3D(day17::Array3D<bool>* const space) {
    Array3D<bool>* newSpace = new Array3D<bool>(space->sizeX, space->sizeY, space->sizeZ, false);

    for (size_t x = 1; x < space->sizeX - 1; x++) {
        for (size_t y = 1; y < space->sizeY - 1; y++) {
            for (size_t z = 1; z < space->sizeZ - 1; z++) {
                // Count nearby
                uint64_t n = nearbyActive3D(space, x, y, z);
                if (space->get(x, y, z)) {
                    // Active
                    if (n == 2 || n == 3) {
                        newSpace->set(x, y, z, true);
                        newSpace->count++;
                    }
                } else {
                    // Inactive
                    if (n == 3) {
                        newSpace->set(x, y, z, true);
                        newSpace->count++;
                    }
                }
            }
        }
    }
    return newSpace;
}


// ===== ===== ===== Implementations 4D ===== ===== ===== 

uint64_t day17::nearbyActive4D(Array4D<bool>* const space, size_t x, size_t y, size_t z, size_t w) {
    uint64_t near = 0;
    const size_t dirSize = 3;
    int directions[dirSize] = {-1, 0, 1};
    // Iterate directions
    for (size_t xi = 0; xi < dirSize; xi++) {
        for (size_t yi = 0; yi < dirSize; yi++) {
            for (size_t zi = 0; zi < dirSize; zi++) {
                for (size_t wi = 0; wi < dirSize; wi++) {
                    if (xi != 1 || yi != 1 || zi != 1 || wi != 1) {
                        // Don't check the same spot
                        int64_t posx = x + directions[xi];
                        int64_t posy = y + directions[yi];
                        int64_t posz = z + directions[zi];
                        int64_t posw = w + directions[wi];
                        // Count if nearby is active
                        if (space->get(posx, posy, posz, posw) == true) {
                            near++;
                        }
                    }
                }
            }
        }
    }
    return near;
}

day17::Array4D<bool>* day17::inputToSpace4D(std::vector<std::string> * input) {
    size_t border = Borders * 2;
    size_t maxRow = input->size();
    size_t maxCol = (*input)[0].length();
    // Allocate space
    Array4D<bool>* space = new Array4D<bool>(
                                maxRow + border, // X
                                maxCol + border, // Y
                                border+1,        // Z
                                border+1,        // W
                                false);
    // Copy input
    for (size_t row = 0; row < maxRow; row++) {
        for (size_t col = 0; col < maxCol; col++) {
            if ( (*input)[row][col] == '#' ) {
                // # means active
                space->set(row + Borders, col + Borders, Borders, Borders, true);
                space->count++;
            }
        }
    }
    return space;
}

day17::Array4D<bool>* day17::iterate4D(day17::Array4D<bool>* const space) {
    Array4D<bool>* newSpace = new Array4D<bool>(space->sizeX, space->sizeY, space->sizeZ, space->sizeW, false);
    for (size_t x = 1; x < space->sizeX - 1; x++) {
        for (size_t y = 1; y < space->sizeY - 1; y++) {
            for (size_t z = 1; z < space->sizeZ - 1; z++) {
                for (size_t w = 1; w < space->sizeW - 1; w++) {
                    // Check nearby for every single cube
                    uint64_t n = nearbyActive4D(space, x, y, z, w);
                    if (space->get(x, y, z, w)) {
                        // Active
                        if (n == 2 || n == 3) {
                            newSpace->set(x, y, z, w, true);
                            newSpace->count++;
                        }
                    } else {
                        // Inactive
                        if (n == 3) {
                            newSpace->set(x, y, z, w, true);
                            newSpace->count++;
                        }
                    }
                }
            }
        }
    }
    return newSpace;
}
