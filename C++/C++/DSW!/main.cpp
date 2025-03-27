#include "dsw.h"

int main() {
    BST bst;

    // Insert values into the BST
    bst.insert(10);
    bst.insert(14);
    bst.insert(23);
    bst.insert(8);
    bst.insert(7);
    bst.insert(9);
    bst.insert(20);
    bst.insert(25);

    cout << "Original tree";
    bst.display();


    // Balance the tree using DSW algorithm
    bst.dswBalance();

    cout << "DSW Balanced tree";

    bst.display();


    return 0;
}
