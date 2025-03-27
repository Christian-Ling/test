#include "splay.h"
#include <iostream>
int main() {
    SplayTree tree;



    tree.insert(54);
    tree.insert(36);
    tree.insert(52);
    tree.insert(21);
    tree.insert(29);
    tree.insert(6);
    tree.insert(79);
    tree.insert(88);
    tree.insert(72);
    tree.insert(75);
    tree.insert(63);
    tree.insert(66);
    tree.insert(55);
    tree.insert(59);

    cout << "Tree after insertions: ";
    tree.display();

    tree.remove(21);
    cout << "Tree after splaying 44: ";
    tree.display();

    tree.insert(90);
    cout << "Tree after deleting 31: ";
    tree.display();

    tree.search(66);
    cout << "Tree after searching 66: ";

    tree.display();

    return 0;
}
