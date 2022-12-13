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

    static Node getLeaf(uint64_t leafValue)
    {
        Node node;
        node.isLeaf = true;
        node.value = leafValue;
        return node;
    }
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
                auto value = std::stoull(line.substr(i, j - i));
                root.subnodes.push_back(Node::getLeaf(value));
                i = j - 1;
                break;
            }
        }
    }
    return std::make_pair(root, i);
}

// Return (isValid, isRightOrder)
// isValid = false means they are equal (and `isRightOrder` is not a valid result)
std::pair<bool, bool> rightOrder(Node left, Node right)
{
    if (left.isLeaf && right.isLeaf) {
        if (left.value == right.value) {
            return std::make_pair(false, false);
        }
        return std::make_pair(true, left.value < right.value);
    }
    if (left.isLeaf) {
        left.subnodes.push_back(Node::getLeaf(left.value));
    }
    if (right.isLeaf) {
        right.subnodes.push_back(Node::getLeaf(right.value));
    }

    auto ln = left.subnodes.size();
    auto rn = right.subnodes.size();
    for (int i = 0, n = std::min(ln, rn); i < n; i++) {
        auto result = rightOrder(left.subnodes[i], right.subnodes[i]);
        if (result.first) {
            return result;
        }
    }

    if (ln == rn) {
        return std::make_pair(false, false);
    }
    return std::make_pair(true, ln < rn);
}

uint64_t findSolution1(std::vector<std::string> &list)
{
    uint64_t count = 0;
    uint64_t index = 0;
    for (int i = 0, n = list.size(); i < n; i = i + 2) {
        index++;
        auto leftNode = getNode(list[i]);
        auto rightNode = getNode(list[i + 1]);
        auto result = rightOrder(leftNode.first, rightNode.first);
        if (result.second) {
            count += index;
        }
    }
    return count;
}

uint64_t findSolution2(std::vector<std::string> &list)
{
    std::vector<Node> nodes;
    for (int i = 0, n = list.size(); i < n; ++i) {
        nodes.push_back(getNode(list[i]).first);
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
    parse::read_all_notempty(file, &list);
    auto result = findSolution1(list);
    return std::to_string(result);
}

std::string process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all_notempty(file, &list);
    auto result = findSolution2(list);
    return std::to_string(result);
}
