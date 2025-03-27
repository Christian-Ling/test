#include "uf.h"

int main()
{
    WeightedQuickUnion uf(10);

    uf.Union(1,2);
    uf.Union(1,3);
    uf.Union(2,6);
    uf.Union(3,9);
    uf.Union(0,7);

    uf.print();

    return 0;
}