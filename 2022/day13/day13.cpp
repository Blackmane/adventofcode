/**
 * @file    day13.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    13 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day13.h"

#include "common.h"

struct Node {
    std::vector<Node> subnodes;
    uint64_t value = 0;
    bool isLeaf = false;

    Node(){};
};

std::pair<Node, size_t> getNode(std::string line)
{
    Node root;
    int i = 0;
    for (int n = line.size(); i < n; ++i) {
        switch (line[i]) {
            case '[': {
                auto part = getNode(line.substr(i + 1, n - i - 1));
                root.subnodes.push_back(part.first);
                i += part.second;
                break;
            }
            case ']':
                return std::make_pair(root, i + 1);
            case ',':
                break;
            default: { // Is a number
                int j = i;
                for (; j < n; j++) {
                    if (line[j] < '0' || line[j] > '9') {
                        break;
                    }
                }
                Node value;
                value.isLeaf = true;
                value.value = std::stoull(line.substr(i, j - i));
                root.subnodes.push_back(value);
                i = j - 1;
                break;
            }
        }
    }
    return std::make_pair(root, i);
}

std::pair<bool, bool> rightOrder(Node left, Node right)
{
    if (left.isLeaf && right.isLeaf) {
        if (left.value < right.value) {
            return std::make_pair(true, true);
        }
        if (left.value > right.value) {
            return std::make_pair(true, false);
        }
        return std::make_pair(false, false);
    }
    if (left.isLeaf) {
        Node node;
        node.isLeaf = true;
        node.value = left.value;
        left.subnodes.push_back(node);
    }
    if (right.isLeaf) {
        Node node;
        node.isLeaf = true;
        node.value = right.value;
        right.subnodes.push_back(node);
    }

    auto ln = left.subnodes.size();
    auto rn = right.subnodes.size();
    for (int i = 0, n = std::min(ln, rn); i < n; i++) {
        auto result = rightOrder(left.subnodes[i], right.subnodes[i]);
        if (result.first) {
            return result;
        }
    }

    if (ln < rn) {
        return std::make_pair(true, true);
    }
    if (ln > rn) {
        return std::make_pair(true, false);
    }
    return std::make_pair(false, false);
}

bool rightOrder(const std::string &left, const std::string &right)
{
    auto leftNode = getNode(left);
    auto rightNode = getNode(right);
    auto result = rightOrder(leftNode.first, rightNode.first);
    if (!result.first) {
        return true;
    } else {
        return result.second;
    }
}

uint64_t findSolution1(std::vector<std::string> &list)
{
    uint64_t count = 0;
    uint64_t index = 0;
    for (int i = 0, n = list.size(); i < n; i = i + 3) {
        index++;
        if (rightOrder(list[i], list[i + 1])) {
            count += index;
        }
    }
    return count;
}

uint64_t findSolution2(std::vector<std::string> &list)
{
    std::vector<Node> nodes;
    for (int i = 0, n = list.size(); i < n; ++i) {
        if (list[i] != "") {
            nodes.push_back(getNode(list[i]).first);
        }
    }
    auto two = getNode("[[2]]").first;
    auto six = getNode("[[6]]").first;
    uint64_t minTwo = 1;
    uint64_t minSix = 2; // Count the "two" node
    for (int i = 0, n = nodes.size(); i < n; ++i) {
        if (rightOrder(nodes[i], two).second) {
            minTwo++;
        }
        if (rightOrder(nodes[i], six).second) {
            minSix++;
        }
    }
    return minTwo * minSix;
}

std::string process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = findSolution1(list);
    return std::to_string(result);
}

std::string process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    auto result = findSolution2(list);
    return std::to_string(result);
}
