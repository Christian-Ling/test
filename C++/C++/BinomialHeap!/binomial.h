#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <iostream>
#include <iomanip>

using namespace std;

struct binomialNode
{
    int key;
    int degree;
    binomialNode* sibling;
    binomialNode* child;
    binomialNode* parent;

    binomialNode(int k);
};

class BinomialHeap
{
    private:
        binomialNode* head;

        binomialNode* unionHeap(binomialNode* heap1, binomialNode* heap2);
        binomialNode* mergeTrees(binomialNode* tree1, binomialNode* tree2);
        void linkTrees(binomialNode*& prev, binomialNode*& cur, binomialNode*& next);

    public:
        BinomialHeap();

        void insert(int key);
        void merge(BinomialHeap& other);
        int findMin();

        void deleteMin();
        void deleteKey(int key);
        void decreaseKey(int oldKey, int newKey);
        binomialNode* findNode(binomialNode* node, int key); //heaper function

        void printHeap();
        void printTree(binomialNode* node, int space);
};

#endif