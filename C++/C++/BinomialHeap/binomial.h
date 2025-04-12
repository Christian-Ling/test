#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <iostream>

using namespace std;

struct binomialNode {
    int key;
    int degree;
    binomialNode* parent;
    binomialNode* child;
    binomialNode* sibling;

    binomialNode(int k);
};

class BinomialHeap {
private:
    binomialNode* head; // Pointer to the root of the heap

    // Helper functions
    binomialNode* unionHeap(binomialNode* heap1, binomialNode* heap2);
    binomialNode* mergeTrees(binomialNode* tree1, binomialNode* tree2);
    void linkTrees (binomialNode*& prev, binomialNode*& cur, binomialNode*& next);
    void printTree(binomialNode* node, int space);

public:
    BinomialHeap();

    void insert(int key);
    void merge(BinomialHeap* other);
    int findMin();

    //deleteMin()
    //deleteKey( int key);
    //decreaseKey(oldKey, newKey);

    void printHeap();
    void printTree(binomialNode*node, int space)
};

#endif