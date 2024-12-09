/**
 * @file    day09.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    09 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day09.h"

#include "common.h"

uint64_t applySum(int &mem_pos, int indx, int space)
{
    uint64_t sum = 0;
    for (int x = 0; x < space; x++) {
        sum += uint64_t(mem_pos) * uint64_t(indx);
        mem_pos++;
    }
    return sum;
}

std::string day09::process1(std::string file)
{
    auto line = parse::read_all(file);
    uint64_t sum = 0;
    int n = line[0].size();
    bool freeSpace = false;
    int memj = 0;
    int z = n - 1;
    int zres = line[0][z] - '0';
    int idz = n / 2;
    int idi = 0;
    int i = 0;
    for (; i < z; i++) {
        if (freeSpace) {
            int space = line[0][i] - '0';
            while (space >= zres && i < z) {
                sum += applySum(memj, idz, zres);
                space -= zres;
                zres = 0;
                while (zres == 0) {
                    idz--;
                    z = z - 2;
                    zres = line[0][z] - '0';
                }
            }
            if (space > 0 && i < z) {
                sum += applySum(memj, idz, space);
                zres -= space;
            }
        } else {
            sum += applySum(memj, idi, line[0][i] - '0');
            idi++;
        }

        freeSpace = !freeSpace;
    }

    if (zres > 0 && i <= z) {
        sum += applySum(memj, idz, zres);
    }
    return std::to_string(sum);
}

std::string day09::process2(std::string file)
{
    auto line = parse::read_all(file);
    uint64_t sum = 0;
    int n = line[0].size();
    std::vector<int> mem(n, 0);
    for (int i = 1; i < n; i++) {
        mem[i] = mem[i - 1] + line[0][i - 1] - '0';
    }

    int idz = n / 2;
    for (int z = n - 1; z >= 0 && idz >= 0; z = z - 2, idz--) {
        int zspace = line[0][z] - '0';
        if (zspace <= 0) {
            continue;
        }
        bool found = false;
        for (int i = 1; i < z && !found; i = i + 2) {
            int ispace = line[0][i] - '0';
            if (ispace >= zspace) {
                sum += applySum(mem[i], idz, zspace);
                line[0][i] -= zspace;
                found = true;
                break;
            }
        }
        if (!found) {
            sum += applySum(mem[z], idz, zspace);
        }
    }

    return std::to_string(sum);
}
