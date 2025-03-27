#ifndef DSW_H
#define DSW_H

#include <iostream>
#include <math.h>

using namespace std;

struct Node
{
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

class BST
{
    private:
        Node* root;

        //Helper functions
        void rotateRight(Node*& node);
        void rotateLeft(Node*& node);

        void createVine(); // Phase 1
        void rebuildTree(int size); //Phase 2
        void preformRotation(int count); //Helper for Phase 2 (rebuild tree)
        void printTree(Node* root, int space);
        
    public:
        BST();
        ~BST();
        // helper for the destructor
        void deleteTree(Node*& node);

        void insert(int val);
        void dswBalance();

        void display();
};

#endif