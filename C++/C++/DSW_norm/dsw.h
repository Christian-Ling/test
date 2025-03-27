#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) 
    {
        data = val;
        left = nullptr; 
        right = nullptr;
    }
};

class BST {

private:
    Node* root;

    // Helper functions
    void rotateRight(Node*& node);
    void rotateLeft(Node*& node);
    void createVine();
    void rebuildTree(int size);
    void performRotations(int count);
    void printTree(Node* root, int space);

public:
    BST();
    ~BST();

    void insert(int val);
    void deleteTree(Node* node);
    void dswBalance();

    void display();
};

#endif
