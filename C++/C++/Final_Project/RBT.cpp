#include "AutoComplete.h"
#include <cstring>

RBTNode::RBTNode(const char* w) : color(RED), left(nullptr), right(nullptr), parent(nullptr) {
    copyStr(word, w);
}

void leftRotate(RBTNode*& root, RBTNode* x) {
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(RBTNode*& root, RBTNode* y) {
    RBTNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(RBTNode*& root, RBTNode* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTNode* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            RBTNode* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

RBTNode* insertRBT(RBTNode* root, const char* word) {
    RBTNode* z = new RBTNode(word);
    RBTNode* y = nullptr;
    RBTNode* x = root;

    while (x) {
        y = x;
        if (strLess(z->word, x->word)) x = x->left;
        else if (strLess(x->word, z->word)) x = x->right;
        else return root;
    }

    z->parent = y;
    if (!y) root = z;
    else if (strLess(z->word, y->word)) y->left = z;
    else y->right = z;

    fixInsert(root, z);
    return root;
}