#include "binomial.h"

binomialNode::binomialNode(int k) {
    key = k;
    degree = 0;
    parent = nullptr;
    sibling = nullptr;
    child = nullptr;
}

binomialNode* BinomialHeap::unionHeap(binomialNode* heap1, binomialNode* heap2) {
    if (!heap1)
        return heap2;
    if (!heap2)
        return heap1;

    binomialNode* newHead = nullptr;
    binomialNode** pos = &newHead;

    while (heap1 && heap2) {
        if (heap1->degree <= heap2->degree) {
            *pos = heap1;
            heap1 = heap1->sibling;
        } else {
            *pos = heap2;
            heap2 = heap2->sibling;
        }
        pos = &((*pos)->sibling);
    }

    *pos = (heap1) ? heap1 : heap2;

    return newHead;
}

binomialNode* BinomialHeap::mergeTrees(binomialNode* tree1, binomialNode* tree2) {
    if (tree1->key > tree2->key)
        swap(tree1, tree2);

    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->degree++;

    return tree1;
}

void BinomialHeap::linkTrees(binomialNode*& prev, binomialNode*& cur, binomialNode*& next) {
    if (prev->degree != next->degree || (next->sibling->degree == cur->degree))
    {
        prev = cur;
        cur = next;
    } else {
      if (cur->key <= next->key) {
        cur->sibling = next->sibling;
        mergeTrees(cur, next);
      } else {
        if (!prev) {
            head = next;
        } else {
            prev->sibling = next;
        }
        mergeTrees(next, cur);
        cur = next;
      }
    } 
}

//---------------------------------- PUBLIC FUNCTIONS --------------------------------

BinomialHeap::BinomialHeap() 
{
    head = nullptr;
}

void BinomialHeap::insert(int key) {
    binomialHeap tempHeap;

    head = unionHeap(head, tempHeap.new);

    binomialNode* prev = nullptr;
    binomialNode* cur = head;
    binomialNode* next = head->sibling;

    while (next)
    {
        linkTrees(prev, cur, next);
        prev = cur->sibling;
    }
}

void BiomialHeap::merge(BinomialHeap* other)
{
    head = unionHeap(head, other->head);
    other.head = nullptr;

    if (!head || !head->sibling)
        return;

    binomialNode* prev = nullptr;
    binomialNode* cur = head;
    binomialNode* next = head->sibling;

    while (next)
    {
        linkTrees(prev, cur, next);
        prev = cur->sibling;
    }
}

int BinomialHeap::findMin() {
    if (!head) 
        return -1;

    binomialNode* minNode = head;
    int minKey = head->key;

    binomialNode* temp = head->sibling;
    while (temp) {
        if (temp->key < minKey) 
        {
            minKey = temp->key;
            minNode = temp;
        }
        temp = temp->sibling;
    }
    return minKey;
}