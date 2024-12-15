/**
 * @file    day15.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    15 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day15.h"

#include "common.h"

std::pair<int, int> getStep(char dir)
{
    switch (dir) {
        case 'v':
            return { 1, 0 };
        case '>':
            return { 0, 1 };
        case '<':
            return { 0, -1 };
        case '^':
            return { -1, 0 };
    }
    return { 0, 0 };
}

void moveRobot(std::vector<std::string> &map, int &i, int &j, char dir)
{
    auto [stepi, stepj] = getStep(dir);
    if (map[i + stepi][j + stepj] == '.') {
        map[i][j] = '.';
        i += stepi;
        j += stepj;
        map[i][j] = '@';
    } else if (map[i + stepi][j + stepj] == '#') {
        return;
    } else if (map[i + stepi][j + stepj] == 'O') {
        int step = 2;
        while (map[i + stepi * step][j + stepj * step] == 'O') {
            step++;
        }
        if (map[i + stepi * step][j + stepj * step] == '.') {
            map[i + stepi * step][j + stepj * step] = 'O';
            map[i + stepi][j + stepj] = '@';
            map[i][j] = '.';
            i += stepi;
            j += stepj;
        }
    }
}

void moveRobotWide(std::vector<std::string> &map, int &i, int &j, char dir)
{
    auto [stepi, stepj] = getStep(dir);
    if (map[i + stepi][j + stepj] == '.') {
        map[i][j] = '.';
        i += stepi;
        j += stepj;
        map[i][j] = '@';
    } else if (map[i + stepi][j + stepj] == '#') {
        return;
    } else if (map[i + stepi][j + stepj] == '[' || map[i + stepi][j + stepj] == ']') {
        if (dir == '<' || dir == '>') {
            int step = 2;
            while (map[i][j + stepj * step] == '[' || map[i][j + stepj * step] == ']') {
                step++;
            }
            if (map[i][j + stepj * step] == '.') {
                for (int k = step; k > 1; k--) {
                    map[i][j + stepj * k] = map[i][j + stepj * (k - 1)];
                }
                map[i + stepi][j + stepj] = '@';
                map[i][j] = '.';
                i += stepi;
                j += stepj;
            }
        } else {
            std::set<std::tuple<char, int, int>> objs;
            bool movable = true;
            bool emptyLine = false;
            std::set<std::pair<int, int>> next;
            next.insert({ i, j });

            while (movable && !emptyLine) {
                std::set<std::pair<int, int>> nextNext;
                for (auto &n : next) {
                    switch (map[n.first + stepi][n.second]) {
                        case ']':
                            nextNext.insert({ n.first + stepi, n.second });
                            nextNext.insert({ n.first + stepi, n.second - 1 });
                            objs.insert({ ']', n.first + stepi, n.second });
                            objs.insert({ '[', n.first + stepi, n.second - 1 });
                            break;
                        case '[':
                            nextNext.insert({ n.first + stepi, n.second });
                            nextNext.insert({ n.first + stepi, n.second + 1 });
                            objs.insert({ '[', n.first + stepi, n.second });
                            objs.insert({ ']', n.first + stepi, n.second + 1 });
                            break;
                        case '#':
                            movable = false;
                            break;
                    }
                    if (!movable) {
                        break;
                    }
                }
                if (nextNext.empty()) {
                    emptyLine = true;
                } else {
                    next = std::move(nextNext);
                }
            }

            if (movable) {
                for (auto [c, ii, jj] : objs) {
                    map[ii][jj] = '.';
                }
                for (auto [c, ii, jj] : objs) {
                    map[ii + stepi][jj + stepj] = c;
                }
                map[i][j] = '.';
                i = i + stepi;
                j = j + stepj;
                map[i][j] = '@';
            }
        }
    }
}

void parseFile(const std::string &file, std::vector<std::string> &map, std::vector<std::string> &instructions)
{
    bool mapdDone = false;
    uint64_t count = 0;
    parse::read<uint64_t &>(
        file, '\n',
        [&](uint64_t &d, const std::string &line) {
            if (line.empty()) {
                mapdDone = true;
                return;
            }
            if (!mapdDone) {
                map.push_back(line);
            } else {
                instructions.push_back(line);
            }
        },
        count);
}

uint64_t process(std::vector<std::string> &map, std::vector<std::string> &instructions, int i, int j,
                 std::function<void(std::vector<std::string> &, int &, int &, char)> moveFun, char target)
{
    int n = map.size();
    int m = map[0].size();
    for (auto &line : instructions) {
        for (auto c : line) {
            moveFun(map, i, j, c);
        }
    }

    uint64_t count = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (map[i][j] == target) {
                count += i * 100 + j;
            }
        }
    }
    return count;
}

std::string day15::process1(std::string file)
{
    std::vector<std::string> map;
    std::vector<std::string> instructions;
    parseFile(file, map, instructions);

    int n = map.size();
    int m = map[0].size();
    int i = 0;
    int j = 0;
    bool found = false;
    for (; i < n; i++) {
        j = 0;
        for (; j < m; j++) {
            if (map[i][j] == '@') {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    auto count = process(map, instructions, i, j, moveRobot, 'O');
    return std::to_string(count);
}

std::string day15::process2(std::string file)
{
    std::vector<std::string> map;
    std::vector<std::string> instructions;
    parseFile(file, map, instructions);

    int n = map.size();
    int m = map[0].size();
    std::string bigEmptyLine(m * 2, '.');
    std::vector<std::string> bigMap(n, bigEmptyLine);
    int ii = 0;
    int jj = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            switch (map[i][j]) {
                case '#':
                    bigMap[i][j * 2] = '#';
                    bigMap[i][j * 2 + 1] = '#';
                    break;
                case 'O':
                    bigMap[i][j * 2] = '[';
                    bigMap[i][j * 2 + 1] = ']';
                    break;
                case '.':
                    break;
                case '@':
                    bigMap[i][j * 2] = '@';
                    ii = i;
                    jj = j * 2;
                    break;
            }
        }
    }

    auto count = process(bigMap, instructions, ii, jj, moveRobotWide, '[');
    return std::to_string(count);
}