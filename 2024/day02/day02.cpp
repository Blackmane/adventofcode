/**
 * @file    day02.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    02 Dec 2024
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day02.h"

#include "common.h"

bool safe(const std::vector<uint64_t> &values)
{
    int64_t diff = values[0] - values[1];
    for (size_t i = 1, count = values.size(); i < count; i++) {
        int64_t curr_diff = values[i - 1] - values[i];
        if (diff < 0) {
            if (curr_diff >= 0 || curr_diff < -3) {
                return false;
            }
        } else {
            if (curr_diff <= 0 || curr_diff > 3) {
                return false;
            }
        }
    }
    return true;
}

bool safe2(const std::vector<uint64_t> &values)
{
    int n = values.size();
    int asc = 0;
    int desc = 0;
    for (int i = 1; i < n; i++) {
        int64_t diff = values[i - 1] - values[i];
        if (diff < 0) {
            asc++;
        }
        if (diff > 0) {
            desc++;
        }
    }
    if (asc == desc) {
        return false;
    }

    auto checker = [&](const std::vector<int> &indexes) {
        for (size_t i = 1, m = indexes.size(); i < m; i++) {
            int64_t diff = values[indexes[i - 1]] - values[indexes[i]];
            if (asc > desc && (diff >= 0 || diff < -3)) {
                return false;
            }
            if (asc < desc && (diff <= 0 || diff > 3)) {
                return false;
            }
        }
        return true;
    };

    auto indexes = [&](int exclude) -> std::vector<int> {
        std::vector<int> idxs;
        idxs.reserve(n);

        for (int i = 0; i < n; i++) {
            if (i != exclude) {
                idxs.push_back(i);
            }
        }
        return idxs;
    };

    for (int i = 1; i < n; i++) {
        int64_t curr_diff = values[i - 1] - values[i];
        if ((asc > desc && (curr_diff >= 0 || curr_diff < -3)) || (asc < desc && (curr_diff <= 0 || curr_diff > 3))) {
            return checker(indexes(i - 1)) || checker(indexes(i));
        }
    }

    return true;
}

std::string day02::process1(std::string file)
{
    uint64_t result = 0;
    parse::read<uint64_t *>(
        file, '\n',
        [&](uint64_t *, const std::string &line) {
            auto values = parse::getIntegers(line);
            if (safe(values)) {
                result++;
            }
        },
        &result);
    return std::to_string(result);
}

std::string day02::process2(std::string file)
{
    uint64_t result = 0;
    parse::read<uint64_t *>(
        file, '\n',
        [&](uint64_t *, const std::string &line) {
            auto values = parse::getIntegers(line);
            if (safe2(values)) {
                result++;
            }
        },
        &result);
    return std::to_string(result);
}
