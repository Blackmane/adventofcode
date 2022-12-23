/**
 * @file    day05.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    05 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day05.h"

#include "common.h"

#include <vector>

struct Move {
    size_t quantity;
    size_t from;
    size_t to;
    Move(size_t q, size_t f, size_t t) : quantity(q), from(f), to(t) {}
};

class Cargo
{
  public:
    Cargo(std::string inputFilename);
    void readCrates(const std::vector<std::string> &line);
    void readMoves(const std::string &line);
    void applyMoves1();
    void applyMoves2();
    std::string getResult();

  private:
    std::vector<std::string> crates;
    std::vector<Move> moves;
};

std::string day05::process1(std::string file)
{
    auto cargo = Cargo(file);
    cargo.applyMoves1();
    return cargo.getResult();
}

std::string day05::process2(std::string file)
{
    auto cargo = Cargo(file);
    cargo.applyMoves2();
    return cargo.getResult();
}

Cargo::Cargo(std::string inputFilename)
{
    std::ifstream source;
    source.open(inputFilename, std::ifstream::in);
    std::vector<std::string> parts;
    std::string part;
    while (std::getline(source, part, '\n')) {
        if (part != "") {
            parts.push_back(part);
        } else {
            break;
        }
    }
    readCrates(parts);

    while (std::getline(source, part, '\n')) {
        readMoves(part);
    }
}

void Cargo::readCrates(const std::vector<std::string> &lines)
{
    crates.resize(9);
    for (int i = lines.size() - 2; i >= 0; --i) {
        int pos = 0;
        for (int j = 1, n = lines[i].size(); j < n; j = j + 4) {
            if (lines[i][j] >= 'A' && lines[i][j] <= 'Z') {
                crates[pos].push_back(lines[i][j]);
            }
            ++pos;
        }
    }
}

void Cargo::readMoves(const std::string &line)
{
    auto ints = parse::getIntegers(line);
    auto m = Move(ints[0], ints[1] - 1, ints[2] - 1);
    moves.push_back(m);
}

void Cargo::applyMoves2()
{
    for (auto &&m : moves) {
        auto len = crates[m.from].size();
        auto part = crates[m.from].substr(len - m.quantity, m.quantity);
        crates[m.to].append(part);
        crates[m.from] = crates[m.from].substr(0, len - m.quantity);
    }
}

void Cargo::applyMoves1()
{
    for (auto &&m : moves) {
        for (size_t i = 0; i < m.quantity; i++) {
            char c = crates[m.from].back();
            crates[m.from].pop_back();
            crates[m.to].push_back(c);
        }
    }
}

std::string Cargo::getResult()
{
    std::string result;
    for (auto &&c : crates) {
        result.push_back(c[c.size() - 1]);
    }

    return result;
}