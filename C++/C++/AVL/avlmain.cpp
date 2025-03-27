#include "avl.h"

int main()
{
    AVLTree avl;

    avl.insert(7);
    avl.display();
    avl.insert(11);
    avl.display();
    avl.insert(23);
    avl.display();
    avl.insert(33);
    avl.display();
    avl.insert(20);
    avl.display();
    avl.insert(22);
    avl.display();
    avl.insert(2);
    avl.display();
    avl.insert(5);
    avl.display();
    avl.insert(30);
    avl.display();
    avl.insert(27);
    avl.display();
    avl.insert(25);
    avl.display();

    avl.remove(20);
    avl.remove(23);
    avl.remove(5);
    avl.remove(2);
    avl.display();

    return 0;
}