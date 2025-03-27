#include "bst.h"

int main(int argc, char *argv[])
{

 bstree t;
        int nn;

        nn = t.numNodes();
        cout << nn << endl;

        t.insert(7);
    t.insert(5);
    t.insert(9); // Attempt to insert a duplicate
    t.insert(20);
    t.insert(8);
    t.insert(0); // Attempt to insert a duplicate
    t.insert(13);
    t.insert(6);
    t.insert(3);
    t.insert(14);
    t.insert(11);
    t.search(7);
    t.search(20);
    t.search(11);
    t.remove(11);
    t.in();
    t.pre();
    t.post();
    t.printA();

    return 0;

}