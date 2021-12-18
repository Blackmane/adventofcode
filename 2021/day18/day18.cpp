/**
 * @file    day18.cpp
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

#include "day18.h"

#include <queue>

Node::Node(Node *parentPtr)
{
    parent = parentPtr;
    depth = (parentPtr == nullptr) ? 0 : parentPtr->depth + 1;
}

uint64_t Node::magnitude()
{
    if (isALeaf) {
        return value;
    } else {
        return 3 * left->magnitude() + 2 * right->magnitude();
    }
}

Tree::Tree()
{
    root = std::make_unique<Node>();
}

uint64_t Tree::magnitude()
{
    return root->magnitude();
}

void Tree::updateDepths()
{
    Node *current = root.get();
    std::deque<Node *> visit;
    visit.push_back(current);
    while (!visit.empty()) {
        current = visit.front();
        visit.pop_front();
        current->depth = (current->parent == nullptr) ? 0 : current->parent->depth + 1;
        if (!current->isALeaf) {
            if (current->left.get() != nullptr) {
                visit.push_back(current->left.get());
            }
            if (current->right.get() != nullptr) {
                visit.push_back(current->right.get());
            }
        }
    }
}

void Node::explodeLeft() {
    if (!(isALeaf && left->isALeaf && right->isALeaf && depth >= 4)) {
        println("ERROR EXPLODE LEFT");
        return;
    }
    auto value = left->value;
    auto current = left.get();
    auto curParent = current->parent;
    while (parent) 

}

bool Tree::explode() {
    Node *current = root.get();
    std::deque<Node *> visit;
    visit.push_front(current);
    while (!visit.empty()) {
        current = visit.front();
        visit.pop_front();
        if (current == nullptr) {
            continue;
        }
/* 
    [
        [
            [
                [
                parent
                    [
                        5,
                        5
                    ],
                    4
                ],
                3
            ],
            2
        ],
        1
    ]
*/

        if (!current->isALeaf && current->left->isALeaf && current->right->isALeaf && current->depth >= 4) {
                // EXPLODE
                auto parent = current->parent;
                if (current == parent->left.get()) {
                    // Explode to left
                    current.explodeLeft();

                    // Explode to right
                    Node* pointer = parent->right.get();
                    while (pointer->isALeaf()) {
                        pointer = pointer->left.get();
                    }
                    pointer->value += current->right->value;

                    parent->left = makeLeaf(0, parent);
                }
                if (current == parent->right.get()) {

                }
                return true;
            
        }
        visit.push_front(current->left.get());
        visit.push_front(current->right.get());
    }
    return false;
}

bool Tree::split() {
    return false;
}

void Tree::reduce() {

}

void Tree::operator+(Tree *right) {
    auto newRoot = std::make_unique<Node>();
    newRoot->left = std::move(root);
    newRoot->right = std::move(right->root);
    root = std::move(newRoot);
    updateDepths();
    reduce();
} 
/*
This snailfish homework is about addition.
To add two snailfish numbers, form a pair from the left and right parameters of the addition operator. 
For example,
[1,2] + [[3,4],5] becomes [[1,2],[[3,4],5]].

There's only one problem: snailfish numbers must always be reduced, 
and the process of adding two snailfish numbers can result in snailfish numbers that need to be reduced.

To reduce a snailfish number, you must repeatedly do the first action in this list 
that applies to the snailfish number:

    If any pair is nested inside four pairs, the leftmost such pair explodes.
    If any regular number is 10 or greater, the leftmost such regular number splits.


*/

std::unique_ptr<Node> makeLeaf(int value, Node *parent)
{
    std::unique_ptr<Node> node = std::make_unique<Node>(parent);
    node->isALeaf = true;
    node->value = value;
    return node;
}

void convertLine(TreeList *treeList, std::string line)
{
    std::unique_ptr<Tree> tree = std::make_unique<Tree>();

    Node *current = tree->root.get();
    bool isLeft = true;
    // Skip first '['
    for (auto c : line.substr(1, line.size())) {
        println(">" << c);
        if (c >= '0' && c <= '9') {
            if (isLeft) {
                current->left = makeLeaf(c - '0', current);
            } else {
                current->right = makeLeaf(c - '0', current);
            }

        } else {
            switch (c) {
                case '[':
                    if (isLeft) {
                        current->left = std::make_unique<Node>(current);
                        current = current->left.get();
                    } else {
                        current->right = std::make_unique<Node>(current);
                        current = current->right.get();
                    }
                    isLeft = true;
                    break;
                case ',':
                    isLeft = false;
                    break;
                case ']':
                    current = current->parent;
                    // TODO: if is nullptr? impossibile
                    isLeft = false;
                    break;
            }
        }
    }
    treeList->push_back(std::move(tree));

    /*
    [1,2]
    [[1,2],3]
    [9,[8,7]]
    [[1,9],[8,5]]
    [[[[1,2],[3,4]],[[5,6],[7,8]]],9]
    [[[9,[3,8]],[[0,9],6]],[[[3,7],[4,9]],3]]
    [[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]
    */
}

uint64_t findSolution1(TreeList *treeList)
{
    return 0;
}

std::string process1(std::string file)
{
    std::unique_ptr<TreeList> treeList = std::make_unique<TreeList>();
    parse::read<TreeList *>(file, '\n', convertLine, treeList.get());
    auto res = findSolution1(treeList.get());
    return std::to_string(res);
}

std::string process2(std::string file)
{
    return "0";
}
