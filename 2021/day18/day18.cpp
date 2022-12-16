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

constexpr uint64_t ExplodeDepth = 4;

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
void Node::explodeLeft()
{
    if (!(!isALeaf && left->isALeaf && right->isALeaf && depth >= ExplodeDepth)) {
        println("ERROR EXPLODE LEFT");
        return;
    }
    auto val = left->value;
    auto current = left.get();
    auto curParent = current->parent;
    while (curParent && curParent->left.get() == current) {
        current = curParent;
        curParent = current->parent;
    }
    // CHECK root
    if (curParent) {
        current = curParent->left.get();
        while (current && !current->isALeaf) {
            if (current->right.get()) {
                current = current->right.get();
            } else {
                current = current->left.get();
            }
        }
        if (current) {
            current->value += val;
        }
    }
}

void Node::explodeRight()
{
    if (!(!isALeaf && left->isALeaf && right->isALeaf && depth >= ExplodeDepth)) {
        println("ERROR EXPLODE RIGHT");
        return;
    }
    auto val = right->value;
    auto current = right.get();
    auto curParent = current->parent;
    while (curParent && curParent->right.get() == current) {
        current = curParent;
        curParent = current->parent;
    }
    // CHECK root
    if (curParent) {
        current = curParent->right.get();
        while (current && !current->isALeaf) {
            if (current->left.get()) {
                current = current->left.get();
            } else {
                current = current->right.get();
            }
        }
        if (current) {
            current->value += val;
        }
    }
}

void Node::split(Node *cur)
{
    if (!(isALeaf && value >= 10)) {
        println("ERROR SPLIT");
        return;
    }
    isALeaf = false;
    left = makeLeaf(value / 2, cur);
    right = makeLeaf((value + 1) / 2, cur);
    value = -1;
}

std::unique_ptr<Node> makeLeaf(int value, Node *parent)
{
    std::unique_ptr<Node> node = std::make_unique<Node>(parent);
    node->isALeaf = true;
    node->value = value;
    return node;
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
        {
            if (current->left.get() != nullptr) {
                visit.push_back(current->left.get());
            }
            if (current->right.get() != nullptr) {
                visit.push_back(current->right.get());
            }
        }
    }
}

bool Tree::explode()
{
    Node *current = root.get();
    std::deque<Node *> visit;
    visit.push_front(current);
    while (!visit.empty()) {
        current = visit.front();
        visit.pop_front();
        if (current == nullptr) {
            // Leaf's right and left
            continue;
        }
        if (!current->isALeaf && current->left->isALeaf && current->right->isALeaf && current->depth >= ExplodeDepth) {
            current->explodeLeft();
            current->explodeRight();
            auto parent = current->parent;
            if (current == parent->left.get()) {
                parent->left = makeLeaf(0, parent);
            }
            if (current == parent->right.get()) {
                parent->right = makeLeaf(0, parent);
            }
            return true;
        }
        visit.push_front(current->right.get());
        visit.push_front(current->left.get());
    }
    return false;
}

bool Tree::split()
{
    Node *current = root.get();
    std::deque<Node *> visit;
    visit.push_front(current);
    while (!visit.empty()) {
        current = visit.front();
        visit.pop_front();
        if (current == nullptr) {
            continue;
        }

        if (current->isALeaf && current->value >= 10) {
            current->split(current);
            return true;
        }
        visit.push_front(current->right.get());
        visit.push_front(current->left.get());
    }
    return false;
}

void Tree::reduce()
{
    bool done = false;
    while (!done) {
        if (explode()) {
            continue;
        }
        if (split()) {
            continue;
        }
        done = true;
    }
}

void Tree::operator+(Tree *right)
{
    auto newRoot = std::make_unique<Node>();
    newRoot->depth = 0;
    newRoot->isALeaf = false;
    newRoot->parent = nullptr;
    root->parent = newRoot.get();
    newRoot->left = std::move(root);
    right->root->parent = newRoot.get();
    newRoot->right = std::move(right->root);
    root = std::move(newRoot);
    updateDepths();
    reduce();
}

void convertLine(TreeList *treeList, std::string line)
{
    std::unique_ptr<Tree> tree = std::make_unique<Tree>();

    Node *current = tree->root.get();
    bool isLeft = true;
    // Skip first '['
    for (auto c : line.substr(1, line.size())) {
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
}

uint64_t findSolution1(TreeList *treeList)
{
    Tree *sum = treeList->at(0).get();
    for (size_t i = 1, n = treeList->size(); i < n; ++i) {
        *sum + treeList->at(i).get();
    }
    return sum->magnitude();
}

uint64_t findSolution2(std::vector<std::string> *input)
{
    uint64_t maxValue = 0;
    for (size_t i = 0, n = input->size(); i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                auto iTree = std::make_unique<TreeList>();
                convertLine(iTree.get(), input->at(i));
                auto jTree = std::make_unique<TreeList>();
                convertLine(jTree.get(), input->at(j));
                Tree *sum = iTree->at(0).get();
                *sum + jTree->at(0).get();
                auto magnitude = sum->magnitude();
                if (magnitude > maxValue) {
                    maxValue = magnitude;
                }
            }
        }
    }
    return maxValue;
}

std::string day18::process1(std::string file)
{
    std::unique_ptr<TreeList> treeList = std::make_unique<TreeList>();
    parse::read<TreeList *>(file, '\n', convertLine, treeList.get());
    auto res = findSolution1(treeList.get());
    return std::to_string(res);
}

std::string day18::process2(std::string file)
{
    std::vector<std::string> input;
    parse::read_all(file, &input);
    auto res = findSolution2(&input);
    return std::to_string(res);
}
