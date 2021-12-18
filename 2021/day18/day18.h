/**
 * @file    day18.h
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    18 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "common.h"
#include <stdint.h>
#include <string>

#include <memory>
#include <vector>

/**
 * Run the first problem
 * @param file input file
 * @return result
 */
std::string process1(std::string file);

/**
 * Run the second problem
 * @param file input file
 * @return result
 */
std::string process2(std::string file);


struct Node {
    Node *parent = nullptr;
    uint64_t depth = 0;
    bool isALeaf = false;
    int value = 0;
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
    Node (Node * parentPtr = nullptr);
    uint64_t magnitude();
    void explodeLeft();
};

std::unique_ptr<Node> makeLeaf(int value, Node *parent = nullptr);

struct Tree {
    std::unique_ptr<Node> root;
    void operator+(Tree* right);
    Tree();
    uint64_t magnitude();
    void updateDepths();
    void reduce();
    bool explode();
    bool split();
};

typedef std::vector<std::unique_ptr<Tree>> TreeList;

void convertLine(TreeList *treeList, std::string line);