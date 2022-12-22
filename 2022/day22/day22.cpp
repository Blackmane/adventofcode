/**
 * @file    day22.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    22 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day22.h"

#include "common.h"

// ===== ===== ===== Class ===== ===== =====

class Plain
{
  public:
    Plain(std::string inputFilename);

    uint64_t getResult();
    void move();

  private:
    std::vector<std::string> map;
    std::string moves;
    std::pair<size_t, size_t> pos;
    int dir;

    void moveAhead(size_t steps);
};

class Cube
{
  public:
    Cube(std::string inputFilename);

    uint64_t getResult();
    void move();

  private:
    std::vector<std::vector<std::string>> map;
    std::string moves;
    std::pair<size_t, size_t> pos;
    size_t face;
    int dir;

    void next(std::pair<size_t, size_t> &pos, size_t &face, int &x, int &y) const;
    void moveAhead(size_t steps);
};

class CubeTest
{
  public:
    CubeTest(std::string inputFilename);

    uint64_t getResult();
    void move();

  private:
    std::vector<std::vector<std::string>> map;
    std::string moves;
    std::pair<size_t, size_t> pos;
    size_t face;
    int dir;

    void next(std::pair<size_t, size_t> &pos, size_t &face, int &x, int &y) const;
    void moveAhead(size_t steps);
};

// ===== ===== ===== Run ===== ===== =====

std::string day22::process1(std::string file)
{
    Plain map(file);
    map.move();
    auto result = map.getResult();
    return std::to_string(result);
}

std::string day22::process2(std::string file)
{
    Cube cube(file);
    cube.move();
    auto result = cube.getResult();
    return std::to_string(result);
}

std::string day22::test2(std::string file)
{
    CubeTest cube(file);
    cube.move();
    auto result = cube.getResult();
    return std::to_string(result);
}

// ===== ===== ===== Implementations ===== ===== =====
// ===== ===== =====      Plain      ===== ===== =====

Plain::Plain(std::string inputFilename)
{
    size_t n = 0;
    std::ifstream source;
    source.open(inputFilename, std::ifstream::in);
    std::string part;
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            map.push_back(part);
            n = std::max(n, part.size());
        } else {
            break;
        }
    }

    while (std::getline(source, part, '\n')) {
        moves = part;
    }

    size_t i = 0;
    while (map[0][i] == ' ') {
        i++;
    }
    pos = std::make_pair(0, i);
    dir = 0; // right;

    // Fill the map with empty spaces
    for (auto &&line : map) {
        auto curn = line.size();
        if (curn < n) {
            for (i = n - curn + 1; i > 0; i--) {
                line.push_back(' ');
            }
        }
    }
}

void Plain::move()
{
    int64_t number = 0;
    for (auto c : moves) {
        switch (c) {
            case 'L':
                moveAhead(number);
                number = 0;
                // rotate left
                dir = (dir - 1 + 4) % 4;
                break;
            case 'R':
                moveAhead(number);
                number = 0;
                // rotate right
                dir = (dir + 1) % 4;
                break;
            default:
                // is a number
                number *= 10;
                number += c - '0';
                break;
        }
    }
    moveAhead(number);
}

uint64_t Plain::getResult()
{
    return 1000 * (pos.first + 1) + 4 * (pos.second + 1) + dir;
}

void Plain::moveAhead(size_t steps)
{
    int y = 0;
    int x = 0;
    switch (dir) {
        case 0:
            x = 1;
            y = 0;
            break;
        case 1:
            x = 0;
            y = 1;
            break;
        case 2:
            x = -1;
            y = 0;
            break;
        case 3:
            x = 0;
            y = -1;
            break;
        default:
            break;
    }

    size_t n = map.size();
    size_t m = map[0].size();
    std::pair<size_t, size_t> cur;
    std::pair<size_t, size_t> newpos = pos;
    for (size_t i = 0; i < steps;) {
        cur.first = (newpos.first + y + n) % n;
        cur.second = (newpos.second + x + m) % m;
        if (map[cur.first][cur.second] != '#') {
            newpos = cur;
            if (map[newpos.first][newpos.second] == '.') {
                pos = newpos;
                i++;
            }
        } else {
            i++;
        }
    }
    if (map[newpos.first][newpos.second] == '.') {
        pos = newpos;
    }
}

// ===== ===== =====      Cube       ===== ===== =====

// INPUT
//     00005555
//     00005555
//     00005555
//     00005555
//     3333
//     3333
//     3333
//     3333
// 22224444
// 22224444
// 22224444
// 22224444
// 1111
// 1111
// 1111
// 1111

Cube::Cube(std::string inputFilename)
{
    std::ifstream source;
    source.open(inputFilename, std::ifstream::in);
    std::string part;

    std::vector<std::string> readed;
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            readed.push_back(part);
        } else {
            break;
        }
    }

    while (std::getline(source, part, '\n')) {
        moves = part;
    }

    face = 0;
    pos = std::make_pair(0, 0);
    dir = 0; // right;

    // Split in faces
    size_t i = 0;
    while (readed[i][0] == ' ') {
        i++;
    }

    size_t j = 0;
    i /= 2;
    std::vector<std::string> empty;
    for (int k = 0; k < 6; k++) {
        map.push_back(empty);
    }
    // Faces 0 5
    for (; j < i; j++) {
        map[0].push_back(readed[j].substr(i, i));
        map[5].push_back(readed[j].substr(i * 2, i));
    }
    // Face 3
    for (; j < i * 2; j++) {
        map[3].push_back(readed[j].substr(i, i));
    }
    // Faces 2 4
    for (; j < i * 3; j++) {
        map[2].push_back(readed[j].substr(0, i));
        map[4].push_back(readed[j].substr(i, i));
    }
    // Faces 1
    for (; j < i * 4; j++) {
        map[1].push_back(readed[j].substr(0, i));
    }
}

void Cube::move()
{
    int64_t number = 0;
    for (auto c : moves) {
        switch (c) {
            case 'L':
                moveAhead(number);
                number = 0;
                // rotate left
                dir = (dir - 1 + 4) % 4;
                break;
            case 'R':
                moveAhead(number);
                number = 0;
                // rotate right
                dir = (dir + 1) % 4;
                break;
            default:
                // is a number
                number *= 10;
                number += c - '0';
                break;
        }
    }
    moveAhead(number);
}

uint64_t Cube::getResult()
{
    size_t n = map[0].size();
    size_t row = 0;
    size_t col = 0;
    switch (face) {
        case 0:
            row = 0;
            col = n;
            break;
        case 1:
            row = n * 3;
            col = 0;
            break;
        case 2:
            row = n * 2;
            col = 0;
            break;
        case 3:
            row = n;
            col = n;
            break;
        case 4:
            row = n * 2;
            col = n;
            break;
        case 5:
            row = 0;
            col = n * 2;
            break;
    }
    return 1000 * (row + pos.first + 1) + 4 * (col + pos.second + 1) + dir;
}

void Cube::moveAhead(size_t steps)
{
    int y = 0;
    int x = 0;

    switch (dir) {
        case 0:
            x = 1;
            y = 0;
            break;
        case 1:
            x = 0;
            y = 1;
            break;
        case 2:
            x = -1;
            y = 0;
            break;
        case 3:
            x = 0;
            y = -1;
            break;
        default:
            break;
    }

    std::pair<size_t, size_t> cur;
    std::pair<size_t, size_t> newpos = pos;
    size_t newface = face;
    int newx = x;
    int newy = y;

    for (size_t i = 0; i < steps;) {
        newpos = pos;
        newface = face;
        newx = x;
        newy = y;

        next(newpos, newface, newx, newy);
        if (map[newface][newpos.first][newpos.second] == '.') {
            pos = newpos;
            face = newface;
            x = newx;
            y = newy;
        }
        i++;
    }

    // Update the new dir
    if (x > 0) {
        dir = 0;
    }
    if (y > 0) {
        dir = 1;
    }
    if (x < 0) {
        dir = 2;
    }
    if (y < 0) {
        dir = 3;
    }
}

void Cube::next(std::pair<size_t, size_t> &curpos, size_t &newface, int &x, int &y) const
{
    size_t n = map[0].size();
    size_t m = map[0][0].size();

    std::pair<size_t, size_t> newpos = curpos;

    if ((y < 0 && curpos.first == 0) || (x < 0 && curpos.second == 0) || (y > 0 && curpos.first == n - 1) ||
        (x > 0 && curpos.second == m - 1)) {
        // Border case
        switch (newface) {
            case 0:
                if (y < 0 && curpos.first == 0) {
                    newface = 1;
                    newpos.first = curpos.second; // n - 1 -
                    newpos.second = 0;
                    y = 0;
                    x = 1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 2;
                    newpos.first = n - 1 - curpos.first;
                    newpos.second = 0;
                    y = 0;
                    x = 1;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 3;
                    newpos.first = 0;
                    newpos.second = curpos.second;
                    x = 0;
                    y = 1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 5;
                    newpos.first = curpos.first;
                    newpos.second = 0;
                    x = 1;
                    y = 0;
                }
                break;
            case 1:
                if (y < 0 && curpos.first == 0) {
                    newface = 2;
                    newpos.first = n - 1;
                    newpos.second = curpos.second;
                    x = 0;
                    y = -1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 0;
                    newpos.first = 0;
                    newpos.second = curpos.first;
                    x = 0;
                    y = 1;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 5;
                    newpos.first = 0;
                    newpos.second = curpos.second; // n - 1 -
                    x = 0;
                    y = 1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 4;
                    newpos.first = n - 1;
                    newpos.second = curpos.first;
                    x = 0;
                    y = -1;
                }
                break;
            case 2:
                if (y < 0 && curpos.first == 0) {
                    newface = 3;
                    newpos.first = curpos.second;
                    newpos.second = 0;
                    x = 1;
                    y = 0;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 0;
                    newpos.first = n - 1 - curpos.first;
                    newpos.second = 0;
                    x = 1;
                    y = 0;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 1;
                    newpos.first = 0;
                    newpos.second = curpos.second;
                    x = 0;
                    y = 1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 4;
                    newpos.first = curpos.first;
                    newpos.second = 0;
                    x = 1;
                    y = 0;
                }
                break;
            case 3:
                if (y < 0 && curpos.first == 0) {
                    newface = 0;
                    newpos.first = n - 1;
                    newpos.second = curpos.second;
                    x = 0;
                    y = -1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 2;
                    newpos.first = 0;
                    newpos.second = curpos.first;
                    x = 0;
                    y = 1;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 4;
                    newpos.first = 0;
                    newpos.second = curpos.second;
                    x = 0;
                    y = 1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 5;
                    newpos.first = n - 1;
                    newpos.second = curpos.first;
                    x = 0;
                    y = -1;
                }
                break;
            case 4:
                if (y < 0 && curpos.first == 0) {
                    newface = 3;
                    newpos.first = n - 1;
                    newpos.second = curpos.second;
                    x = 0;
                    y = -1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 2;
                    newpos.first = curpos.first;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 1;
                    newpos.first = curpos.second;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 5;
                    newpos.first = n - 1 - curpos.first;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                break;

            case 5:
                if (y < 0 && curpos.first == 0) {
                    newface = 1;
                    newpos.first = n - 1;
                    newpos.second = curpos.second;
                    x = 0;
                    y = -1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 0;
                    newpos.first = curpos.first;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 3;
                    newpos.first = curpos.second;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 4;
                    newpos.first = n - 1 - curpos.first;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                break;
        }
    } else {
        newpos.first = newpos.first + y;
        newpos.second = newpos.second + x;
    }
    curpos = newpos;
}

// ===== ===== =====    TestCube     ===== ===== =====

// TEST
//         0000
//         0000
//         0000
//         0000
// 111122223333
// 111122223333
// 111122223333
// 111122223333
//         44445555
//         44445555
//         44445555
//         44445555

//             aAaA
//    .____________________
//    |A   b   0000   C
//    | a   b  0000  c
//    |  A   b 0000 C
//    |   a   b0000c
//   x|111122223333   d
//   X|111122223333  d
//   x|111122223333 d
//   X|111122223333d
//    |   e   f44445555 c
//    |  E   f 44445555 C
//    | e   f  44445555 c
//    |E   f   44445555 C
//    |________________________
//             eEeEXxXx

CubeTest::CubeTest(std::string inputFilename)
{
    size_t n = 0;
    std::ifstream source;
    source.open(inputFilename, std::ifstream::in);
    std::string part;

    std::vector<std::string> readed;
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            readed.push_back(part);
            n = std::max(n, part.size());
        } else {
            break;
        }
    }

    while (std::getline(source, part, '\n')) {
        moves = part;
    }
    face = 0;
    pos = std::make_pair(0, 0);
    dir = 0; // right;

    size_t i = 0;
    while (readed[0][i] == ' ') {
        i++;
    }

    // Split in faces
    size_t j = 0;
    i /= 2;
    std::vector<std::string> empty;
    // Face 0
    map.push_back(empty);
    for (; j < i; j++) {
        map[0].push_back(readed[j].substr(i * 2, i));
    }
    // Faces 1 2 3
    map.push_back(empty);
    map.push_back(empty);
    map.push_back(empty);
    for (; j < i * 2; j++) {
        map[1].push_back(readed[j].substr(0, i));
        map[2].push_back(readed[j].substr(i, i));
        map[3].push_back(readed[j].substr(i * 2, i));
    }
    // Faces 4 5
    map.push_back(empty);
    map.push_back(empty);
    for (; j < i * 3; j++) {
        map[4].push_back(readed[j].substr(i * 2, i));
        map[5].push_back(readed[j].substr(i * 3, i));
    }
}

void CubeTest::move()
{
    int64_t number = 0;
    for (auto c : moves) {
        switch (c) {
            case 'L':
                moveAhead(number);
                number = 0;
                // rotate left
                dir = (dir - 1 + 4) % 4;
                break;
            case 'R':
                moveAhead(number);
                number = 0;
                // rotate right
                dir = (dir + 1) % 4;
                break;
            default:
                // is a number
                number *= 10;
                number += c - '0';
                break;
        }
    }
    moveAhead(number);
}

uint64_t CubeTest::getResult()
{
    size_t n = map[0].size();
    size_t row = 0;
    size_t col = 0;
    switch (face) {
        case 0:
            row = 0;
            col = n * 2;
            break;
        case 1:
            row = n;
            col = 0;
            break;
        case 2:
            row = n;
            col = n;
            break;
        case 3:
            row = n;
            col = n * 2;
            break;
        case 4:
            row = n * 2;
            col = n * 2;
            break;
        case 5:
            row = n * 2;
            col = n * 3;
            break;
    }

    return 1000 * (row + pos.first + 1) + 4 * (col + pos.second + 1) + dir;
}

void CubeTest::moveAhead(size_t steps)
{
    int y = 0;
    int x = 0;

    switch (dir) {
        case 0:
            x = 1;
            y = 0;
            break;
        case 1:
            x = 0;
            y = 1;
            break;
        case 2:
            x = -1;
            y = 0;
            break;
        case 3:
            x = 0;
            y = -1;
            break;
        default:
            break;
    }

    std::pair<size_t, size_t> cur;
    std::pair<size_t, size_t> newpos = pos;
    size_t newface = face;
    int newx = x;
    int newy = y;

    for (size_t i = 0; i < steps;) {
        newpos = pos;
        newface = face;
        newx = x;
        newy = y;

        next(newpos, newface, newx, newy);

        if (map[newface][newpos.first][newpos.second] == '.') {
            pos = newpos;
            face = newface;
            x = newx;
            y = newy;
        }
        i++;
    }

    // Update the new dir
    if (x > 0) {
        dir = 0;
    }
    if (y > 0) {
        dir = 1;
    }
    if (x < 0) {
        dir = 2;
    }
    if (y < 0) {
        dir = 3;
    }
}

void CubeTest::next(std::pair<size_t, size_t> &curpos, size_t &newface, int &x, int &y) const
{
    size_t n = map[0].size();
    size_t m = map[0][0].size();

    std::pair<size_t, size_t> newpos = curpos;

    if ((y < 0 && curpos.first == 0) || (x < 0 && curpos.second == 0) || (y > 0 && curpos.first == n - 1) ||
        (x > 0 && curpos.second == m - 1)) {
        // Border case
        switch (newface) {
            case 0:
                if (y < 0 && curpos.first == 0) {
                    newface = 1;
                    newpos.first = 0;
                    newpos.second = n - 1 - curpos.second;
                    x = 0;
                    y = 1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 2;
                    newpos.first = 0;
                    newpos.second = curpos.first;
                    x = 0;
                    y = 1;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 3;
                    newpos.first = 0;
                    // newpos.second = curpos.second;
                    // x = 0;
                    // y = 1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 5;
                    newpos.first = n - 1 - curpos.first;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                break;
            case 1:
                if (y < 0 && curpos.first == 0) {
                    newface = 0;
                    newpos.first = 0;
                    newpos.second = n - 1 - curpos.first;
                    x = 0;
                    y = 1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 5;
                    newpos.first = n - 1;
                    newpos.second = n - 1 - curpos.first;
                    x = 0;
                    y = -1;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 4;
                    newpos.first = n - 1;
                    newpos.second = n - 1 - curpos.second;
                    x = 0;
                    y = -1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 2;
                    // newpos.first = curpos.first;
                    newpos.second = 0;
                    // x = 1;
                    // y = 0;
                }
                break;
            case 2:
                if (y < 0 && curpos.first == 0) {
                    newface = 0;
                    newpos.first = curpos.second;
                    newpos.second = 0;
                    x = 1;
                    y = 0;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 1;
                    // newpos.first = curpos.first;
                    newpos.second = n - 1;
                    // x = -1;
                    // y = 0;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 4;
                    newpos.first = n - 1 - curpos.second;
                    newpos.second = 0;
                    x = 1;
                    y = 0;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 3;
                    // newpos.first = curpos.first;
                    newpos.second = 0;
                    // x = 1;
                    // y = 0;
                }
                break;
            case 3:
                if (y < 0 && curpos.first == 0) {
                    newface = 0;
                    newpos.first = n - 1;
                    // newpos.second = curpos.second;
                    // x = 0;
                    // y = -1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 2;
                    newpos.first = curpos.first;
                    newpos.second = n - 1;
                    // x = -1;
                    // y = 0;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 4;
                    newpos.first = 0;
                    newpos.second = curpos.second;
                    // x = 0;
                    // y = 1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 5;
                    newpos.first = 0;
                    newpos.second = n - 1 - curpos.first;
                    x = 0;
                    y = 1;
                }
                break;
            case 4:
                if (y < 0 && curpos.first == 0) {
                    newface = 3;
                    newpos.first = n - 1;
                    // newpos.second = curpos.second;
                    // x = 0;
                    // y = -1;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 2;
                    newpos.first = n - 1;
                    newpos.second = n - 1 - curpos.first;
                    x = 0;
                    y = -1;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 1;
                    newpos.first = n - 1;
                    newpos.second = n - 1 - curpos.second;
                    x = 0;
                    y = -1;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 5;
                    // newpos.first = curpos.first;
                    newpos.second = 0;
                    // x = 1;
                    // y = 0;
                }
                break;
            case 5:
                if (y < 0 && curpos.first == 0) {
                    newface = 3;
                    newpos.first = n - 1 - curpos.second;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                if (x < 0 && curpos.second == 0) {
                    newface = 4;
                    // newpos.first = curpos.first;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                if (y > 0 && curpos.first == n - 1) {
                    newface = 1;
                    newpos.first = n - 1 - curpos.second;
                    newpos.second = 0;
                    x = 1;
                    y = 0;
                }
                if (x > 0 && curpos.second == m - 1) {
                    newface = 0;
                    newpos.first = n - 1 - curpos.first;
                    newpos.second = n - 1;
                    x = -1;
                    y = 0;
                }
                break;
        }
    } else {
        newpos.first = newpos.first + y;
        newpos.second = newpos.second + x;
    }
    curpos = newpos;
}
