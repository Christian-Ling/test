#include "dsw.h"

int main()
{

    BST bst;

    bst.insert(10);
    bst.insert(14);
    bst.insert(23);
    bst.insert(8);
    bst.insert(7);
    bst.insert(9);
    bst.insert(20);
    bst.insert(25);

    cout << "Original BST: ";
    bst.display();

    bst.dswBalance();

    cout<< "DSW balancedBST:";
    bst.display();

    return 0;
}