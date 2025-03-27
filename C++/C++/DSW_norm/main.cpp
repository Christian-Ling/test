#include "dsw.h"

int main() {
    BST bst;

    // Insert values into the BST
    cout << "Original tree";
    bst.insert(2);
    bst.display();

    cout << "Original tree";
    bst.insert(3);
    bst.display();
    cout << "Original tree";
    bst.insert(19);
    bst.display();

    cout << "Original tree";
    bst.insert(27);
    bst.display();

    cout << "Original tree";
    bst.insert(20);
    bst.display();

    cout << "Original tree";
    bst.insert(30);
    bst.display();
    
    cout << "Original tree";
    bst.insert(36);
    bst.display();

    cout << "Original tree";
    bst.insert(59);
    bst.display();

    cout << "Original tree";
    bst.insert(43);
    bst.display();

    cout << "Original tree";
    bst.insert(40);
    bst.display();

    //cout << "Original tree";
    //bst.display();

    // Balance the tree using DSW algorithm
    bst.dswBalance();

    cout << "DSW Balanced tree";
    bst.display();

    return 0;
}
