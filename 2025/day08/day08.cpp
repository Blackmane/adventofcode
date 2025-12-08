/**
 * @file    day08.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    08 Dec 2025
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day08.h"

#include "common.h"

#include <queue>

struct Box {
    uint64_t x = 0;
    uint64_t y = 0;
    uint64_t z = 0;
};

uint64_t distance2(Box a, Box b)
{
    uint64_t xx = a.x > b.x ? a.x - b.x : b.x - a.x;
    uint64_t yy = a.y > b.y ? a.y - b.y : b.y - a.y;
    uint64_t zz = a.z > b.z ? a.z - b.z : b.z - a.z;
    return (xx * xx) + (yy * yy) + (zz * zz);
}

struct Pair {
    int i = 0;
    int j = 0;
    uint64_t dist2 = 0;
};

bool cmp(Pair &left, Pair &right)
{
    return left.dist2 > right.dist2;
}

std::priority_queue<Pair, std::deque<Pair>, decltype(&cmp)> getSortedPairs(const std::vector<Box> &boxes)
{
    std::priority_queue<Pair, std::deque<Pair>, decltype(&cmp)> queue(cmp);
    for (int i = 0, n = boxes.size(); i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            auto dist = distance2(boxes[i], boxes[j]);
            queue.push({ i, j, dist });
        }
    }
    return queue;
}

std::vector<Box> getBoxes(const std::string &file)
{
    std::vector<Box> boxes;
    parse::read(file, '\n', [&](const std::string &line) {
        auto parts = parse::split(line, ',');
        boxes.push_back({ std::stoul(parts[0]), std::stoul(parts[1]), std::stoul(parts[2]) });
    });
    return boxes;
}

int getIDx(std::map<int, int> &connected, int idx)
{
    auto it = connected.find(idx);
    return it != connected.end() ? it->second : -1;
}

void internal(Pair &cur, std::map<int, int> &connected, std::map<int, uint64_t> &netSizes, uint64_t &nextIndx)
{
    auto iNet = getIDx(connected, cur.i);
    auto jNet = getIDx(connected, cur.j);
    bool iCon = iNet != -1;
    bool jCon = jNet != -1;
    if (iCon && jCon) {
        // Merge nets
        if (iNet != jNet) {
            netSizes[iNet] = netSizes[iNet] + netSizes[jNet];
            netSizes.erase(jNet);
            for (auto &m : connected) {
                if (m.second == jNet) {
                    m.second = iNet;
                }
            }
        }
    } else if (iCon) {
        // Merge to i
        netSizes[iNet] = netSizes[iNet] + 1;
        connected.insert({ cur.j, iNet });
    } else if (jCon) {
        // Merge to j
        netSizes[jNet] = netSizes[jNet] + 1;
        connected.insert({ cur.i, jNet });
    } else {
        // New net
        netSizes[nextIndx] = 2;
        connected.insert({ cur.i, nextIndx });
        connected.insert({ cur.j, nextIndx });
        nextIndx++;
    }
}

std::string day08::process1(std::string file, int limit)
{
    auto boxes = getBoxes(file);
    auto queue = getSortedPairs(boxes);

    // Box id -> net id
    std::map<int, int> connected;
    // ID -> size
    std::map<int, uint64_t> netSizes;
    uint64_t nextIndx = 0;
    std::set<std::pair<int, int>> paired;

    for (int i = 0; !queue.empty() && i < limit;) {
        auto cur = queue.top();
        queue.pop();

        if (paired.count({ cur.i, cur.j }) > 0) {
            continue;
        }
        paired.insert({ cur.i, cur.j });
        paired.insert({ cur.j, cur.i });
        i++;

        internal(cur, connected, netSizes, nextIndx);
    }

    std::vector<uint64_t> best = { 0, 0, 0 };
    for (auto s : netSizes) {
        auto sizeValue = s.second;
        for (int i = 0; i < 3; i++) {
            if (sizeValue > best[i]) {
                auto temp = sizeValue;
                sizeValue = best[i];
                best[i] = temp;
            }
        }
    }
    uint64_t result = best[0] * best[1] * best[2];
    return std::to_string(result);
}

std::string day08::process2(std::string file, int limit)
{
    auto boxes = getBoxes(file);
    auto queue = getSortedPairs(boxes);

    uint64_t nextIndx = 0;

    // Box id -> net id
    std::map<int, int> connected;
    std::set<std::pair<int, int>> paired;
    // ID -> size
    std::map<int, uint64_t> netSizes;

    for (int i = 0; !queue.empty();) {
        auto cur = queue.top();
        queue.pop();

        if (paired.count({ cur.i, cur.j }) > 0) {
            continue;
        }
        paired.insert({ cur.i, cur.j });
        paired.insert({ cur.j, cur.i });
        i++;

        internal(cur, connected, netSizes, nextIndx);

        if (i > limit && netSizes.size() == 1 && netSizes.begin()->second == boxes.size()) {
            uint64_t result = boxes[cur.i].x * boxes[cur.j].x;
            return std::to_string(result);
        }
    }

    return std::to_string(0);
}
