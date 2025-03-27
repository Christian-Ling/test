#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val)
    {
        key = val;
        left = nullptr;
        right = nullptr;
        height = 0;
    }
};

class AVLTree
{
    private:
        Node* root;

        

        Node* insert(Node* node, int key);
        Node* remove(Node* node, int key);
        Node* minValueNode(Node* node); // helper for remove and finds successor

        int height(Node* node);
        int balanceFactor(Node* node);

        Node* rotateRight(Node* y);
        Node* rotateLeft(Node* y);

        void printTree(Node* root, int space);
        void destroyTree(Node* Node);

    public:
        AVLTree();
        ~AVLTree();


        void insert(int key);
        void remove(int key);

        void display();
};


#endif