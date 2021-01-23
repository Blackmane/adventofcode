/**
 * @file    day20.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    20 Dec 2020
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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


namespace day20 {

const size_t SIDE = 12;

uint64_t Rotation_none = 0;
uint64_t Rotation_gr90 = 1;
uint64_t Rotation_gr180 = 2;
uint64_t Rotation_gr270 = 3;

struct Image {
    std::vector<std::string> lines;
};

struct Tile {
    uint64_t id;
    std::vector<std::string> camera; // = std::vector<std::string>(10, "");
    std::vector<std::string> borders; // = std::vector<std::string>(4, "");
    uint64_t rotation = 0;
    bool isFlipUpDown = false;
    bool isFlipRightLeft = false;
    void generateBorders();
    std::vector<Tile *> nearby = std::vector<Tile *>(4, nullptr);
    uint64_t nearbyCount = 0;
    void rotateNearby();
    void flipUpDown();
    void flipRightLeft();
    void getImage(Image * image);
};

/*===== ===== ===== =====
/           0
/          ____
/         |    |
/      3  |    |  1
/         |____|
/
/           2
===== ===== ===== =====*/

void readTiles(std::string inputFilename, std::vector<Tile *>* listTile);
void combineNearby(std::vector<Tile *>* listTile);
uint64_t foundCorners(std::vector<Tile *>* listTile);
uint64_t createMap(std::vector<Tile *>* listTile);
uint64_t countLockness (Image *matrixImage);


std::vector<std::string> rotate(std::vector<std::string> from);
std::vector<std::string> flipVertical(std::vector<std::string> from);


uint64_t process1(std::string file);
uint64_t process2(std::string file);

} // namespace day20


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day20::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day20::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day20::process1(std::string file) {
    std::vector<Tile *> listTile;
    readTiles(file, &listTile);
    combineNearby(&listTile);
    return foundCorners(&listTile);
}


uint64_t day20::process2(std::string file) {

    std::vector<Tile *> listTile;
    readTiles(file, &listTile);
    combineNearby(&listTile);
    return createMap(&listTile);
}


// ===== ===== ===== Implementations ===== ===== ===== 

void day20::Tile::generateBorders() {
    // Generate border and his flipped version (id +4)
    borders = std::vector<std::string>(8, "");
    // Border up
    borders[0] = camera[0];
    borders[4] = borders[0];
    std::reverse(borders[4].begin(), borders[4].end());
    // Border down
    borders[2] = camera[9];
    std::reverse(borders[2].begin(), borders[2].end());
    borders[6] = camera[9];
    // Laterals
    size_t len = camera.size();
    for (size_t i = 0; i < len; i++) {
        borders[1] += camera[i][9];
        borders[5] += camera[9-i][9];
        borders[3] += camera[9-i][0];
        borders[7] += camera[i][0];
    }
}


void day20::Tile::rotateNearby() {
    // Clockwise
    Tile * tmp = nearby[3];
    nearby[3] = nearby[2];
    nearby[2] = nearby[1];
    nearby[1] = nearby[0]; 
    nearby[0] = tmp;
    rotation = (rotation + 1) % 4;
}


void day20::Tile::flipUpDown() {
    Tile * tmp = nearby[0];
    nearby[0] = nearby[2]; 
    nearby[2] = tmp;
    isFlipUpDown = !isFlipUpDown;
}


void day20::Tile::flipRightLeft() {
    Tile * tmp = nearby[1];
    nearby[1] = nearby[3]; 
    nearby[3] = tmp;
    isFlipRightLeft = !isFlipRightLeft;
}


void day20::Tile::getImage(Image * result) {
    const size_t size = 8;
    std::string tmp[size];
    std::string image[size];
    for (size_t i = 1; i <= size; i++) {
        tmp[i-1] = camera[i].substr(1, size);
        image[i-1] = tmp[i-1];
    }

    // Rotate
    for (size_t i = rotation; i > 0; i--) {
        for (size_t row = 0; row < size; row++) {
            for (size_t col = 0; col < size; col++) {
                tmp[col][size-row-1] = image[row][col];
            }
        }
        for (size_t j = 0; j < size; j++) {
            image[j] = tmp[j];
        }
    }

    // Flip up down
    if (isFlipUpDown) {
        for (size_t row = 0; row < size/2; row++) {
            for (size_t col = 0; col < size; col++) {
                char t = image[row][col];
                image[row][col] = image[size-row-1][col];
                image[size-row-1][col] = t;
            }
        }
    }

    // Flip right left
    if (isFlipRightLeft) {
        for (size_t row = 0; row < size; row++) {
            for (size_t col = 0; col < size/2; col++) {
                char t = image[row][col];
                image[row][col] = image[row][size-col-1];
                image[row][size-col-1] = t;
            }
        }
    }

        for (size_t i = 0; i < size; i++) {
        result->lines.push_back(image[i]);
    }
}


void day20::readTiles(std::string inputFilename, std::vector<Tile *>* listTile) {
    std::ifstream source;
    source.open(inputFilename);
    std::string line;
    Tile * tile = new Tile();
    while (std::getline(source, line, '\n')) {
        if (line != "") {
            if (line[0] == '#' || line[0] == '.') {
                // Image line
                tile->camera.push_back(line);
            } else {
                // Tile XXX:
                size_t pos = line.find(' ');
                size_t stop = line.find(':', pos);
                tile->id = std::stol(line.substr(pos, pos-stop));
            }
        } else {
            // Tile end
            tile->generateBorders();
            listTile->push_back(tile);
            // Nee Tile
            tile = new Tile();
        }
    }
    // Save last tile
    tile->generateBorders();
    listTile->push_back(tile);
}


void day20::combineNearby(std::vector<Tile *>* listTile) {

    size_t len = listTile->size();
    // For every tileI
    for (size_t i = 0; i < len - 1; i++) {
        Tile * tileI = (*listTile)[i];
        // Compare one by one with all other Tiles
        for (size_t j = i + 1; j < len; j++) {
            Tile * tileJ = (*listTile)[j];
            // Every border of tileI
            for (size_t bordi = 0; bordi < 4; bordi++) {
                // If border is not already assigned
                if ( tileI->nearby[bordi] == nullptr ) {
                    // Compare with tileJ borders
                    for (size_t bordj = 0; bordj < 4; bordj++) {
                        // If border is not already assigned
                        if ( tileJ->nearby[bordj] == nullptr ) {
                            if ( tileI->borders[bordi] == tileJ->borders[bordj] 
                                || tileI->borders[bordi] == tileJ->borders[bordj + 4] ) {
                                tileI->nearby[bordi] = tileJ;
                                tileI->nearbyCount++;
                                tileJ->nearby[bordj] = tileI;
                                tileJ->nearbyCount++;
                            }
                        }
                    }
                }
            }
        }
    }
}


uint64_t day20::foundCorners(std::vector<Tile *>* listTile) {
    uint64_t mul = 1;
    for (auto tile : (*listTile)) {
        if (tile->nearbyCount == 2) {
            mul *= tile->id;
        }
    }
    return mul;
}


uint64_t day20::createMap(std::vector<Tile *>* listTile) {
    // Create image
    Tile* image[SIDE][SIDE];
    for (size_t row = 0; row < SIDE; row++) {
        for (size_t col = 0; col < SIDE; col++) {
            image[row][col] = nullptr;
        }
    }
    
    // Find a corner
    for(auto tile : (*listTile) ) {
        if (tile->nearbyCount == 2) {
            image[0][0] = tile;
            break;
        }
    }
    // Rotate corner
    while (image[0][0]->nearby[1] == nullptr 
        || image[0][0]->nearby[2] == nullptr) {
        image[0][0]->rotateNearby();
    } // Now nearbies are in 1 e 2 direction
    
    // Populate cell with ordered tiles
    for (size_t row = 0; row < SIDE; row++) {
        for (size_t col = 0; col < SIDE; col++) {
            // Cell must be set by construction
            if (image[row][col] != nullptr) {
                // Set right side tile
                if (col+1 < SIDE) {
                    // From left
                    if (image[row][col+1] != nullptr) {
                        // Already positioned
                        if (image[row][col+1]->nearby[3] != image[row][col]) {
                            image[row][col+1]->flipRightLeft();
                        }
                    } else {
                        // Is the first row
                        image[row][col+1] = image[row][col]->nearby[1];
                        // Rotate to match sides
                        while (image[row][col+1]->nearby[3] != image[row][col]) {
                            image[row][col+1]->rotateNearby();
                        }
                        if (image[row][col+1]->nearby[0] != nullptr) {
                            image[row][col+1]->flipUpDown();
                        } // else ok, upper border
                    }
                }
                // Set down side tile
                if (row+1 < SIDE) {
                    // From top
                    if (image[row+1][col] != nullptr) {
                    } else {
                        image[row+1][col] = image[row][col]->nearby[2];
                        // Rotate to match sides
                        while (image[row+1][col]->nearby[0] != image[row][col]) {
                            image[row+1][col]->rotateNearby();
                        }
                        if (image[row+1][col]->nearby[3] != nullptr) {
                            image[row+1][col]->flipRightLeft();
                        }
                    }
                }
            } // Else cell is already set
        }
    }
    // Tile cell are now setted

    // Get images rotated from the tiles
    Image tileImage[SIDE][SIDE];
    
    for (size_t row = 0; row < SIDE; row++) {
        for (size_t col = 0; col < SIDE; col++) {
            image[row][col]->getImage(&tileImage[row][col]);
        }
    }

    // Compact inside a matrix
    Image matrixImage;
    size_t size = tileImage[0][0].lines.size();
    for (size_t row = 0; row < SIDE; row++) {
        for (size_t i = 0; i < size; i++) {
            std::string line = "";
            for (size_t col = 0; col < SIDE; col++) {
                // Append
                line += tileImage[row][col].lines[i];
            }
            matrixImage.lines.push_back(line);
        }
    }

    // Count lochness
    return countLockness(&matrixImage);
}


uint64_t day20::countLockness (Image *matrixImage) {

    // Construct all patterns
    typedef std::vector<std::string> Pattern;
    std::vector<Pattern> patterns;

    Pattern originPattern;
    originPattern.push_back("..................O.");
    originPattern.push_back("O....OO....OO....OOO");
    originPattern.push_back(".O..O..O..O..O..O...");

    patterns.push_back(originPattern);    // 0°
    Pattern newPattern = originPattern;
    // Rotations
    for (size_t i = 3; i > 0; i--) {
        newPattern = rotate(newPattern);
        patterns.push_back(newPattern);
    }

    newPattern = flipVertical(originPattern);
    patterns.push_back(newPattern);    // 0° flipped 
    // Rotations
    for (size_t i = 3; i > 0; i--) {
        newPattern = rotate(newPattern);
        patterns.push_back(newPattern);
    }

    uint64_t maxRow = matrixImage->lines.size();
    uint64_t maxCol = matrixImage->lines[0].length();
    Image markedMatrixImage;
    for (auto line: matrixImage->lines) {
        markedMatrixImage.lines.push_back(line);
    }

    // For every patter
    for (auto pattern: patterns) {
        // For row
        for (size_t row = 0; row < maxRow - pattern.size(); row++) {
            // For column
            for (size_t col = 0; col < maxCol - pattern[0].length(); col++) {
                // Check pattern
                bool found = true;
                for (size_t r = 0; r < pattern.size(); r++) {
                    for (size_t c = 0; c < pattern[0].size(); c++) {
                        if (pattern[r][c] == 'O') {
                            if (matrixImage->lines[row+r][col+c] != '#') {
                                found = false;
                            }
                        }
                    }
                }
                if (found) {
                    // Mark the pattern
                    for (size_t r = 0; r < pattern.size(); r++) {
                        for (size_t c = 0; c < pattern[0].size(); c++) {
                            if (pattern[r][c] == 'O' && 
                                matrixImage->lines[row+r][col+c] == '#') {
                                // Then mark pattern
                                markedMatrixImage.lines[row+r][col+c] = 'O';
                            }
                        }
                    }
                }
            }
        }
    }
    uint64_t sum = 0;
    for(auto line : markedMatrixImage.lines) {
        for (char c : line) {
            if (c == '#') {
                sum++;
            }
        }
    }
    return sum;
}


std::vector<std::string> day20::rotate(std::vector<std::string> from) {
    std::vector<std::string> tmp;
    size_t maxRow = from.size();
    size_t maxCol = from[0].length();
    for (size_t col = 0; col < maxCol; col++) {
        std::string line = "";
        for (size_t row = 0; row < maxRow; row++) {
            line += " ";
        }
        tmp.push_back(line);
    }
    
    for (size_t row = 0; row < maxRow; row++) {
        for (size_t col = 0; col < maxCol; col++) {
            tmp[col][maxRow-row-1] = from[row][col];
        }
    }
    return tmp;
}


std::vector<std::string> day20::flipVertical(std::vector<std::string> from) {
    std::vector<std::string> tmp;
    for(auto line : from) {
        tmp.push_back(line);
    }

    size_t maxRow = from.size();
    size_t maxCol = from[0].length();
    for (size_t row = 0; row < maxRow/2; row++) {
        for (size_t col = 0; col < maxCol; col++) {
            tmp[row][col] = from[maxRow-row-1][col];
            tmp[maxRow-row-1][col] = from[row][col];
        }
    }
    return tmp;
}