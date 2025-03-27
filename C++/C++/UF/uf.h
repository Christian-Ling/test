#ifndef UF_H
#define UF_H

#include <iostream>
using namespace std;

class WeightedQuickUnion
{
    private:
        int* parent;
        int* size;
        int n;

    public:
        WeightedQuickUnion(int n);
        ~WeightedQuickUnion();
        
        int find(int p);
        void Union(int p, int q);
        bool connected(int p, int q);

        void print();
};

#endif