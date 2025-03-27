#include "rb.h"


int main() {
    RBTREE rb;


        cout << "Inserting 10:" << endl;
        rb.insert(7);
        rb.printTree();

        cout << "Inserting 20:" << endl;
        rb.insert(11);
        rb.printTree();

        cout << "Inserting 30:" << endl;
        rb.insert(23);
        rb.printTree();

        cout << "Inserting 15:" << endl;
        rb.insert(33);
        rb.printTree();

        cout << "Inserting 25:" << endl;
        rb.insert(20);
        rb.printTree();

        cout << "Inserting 10:" << endl;
        rb.insert(2);
        rb.printTree();
        cout << "Inserting 10:" << endl;
        rb.insert(5);
        rb.printTree();
        cout << "Inserting 10:" << endl;
        rb.insert(30);
        rb.printTree();
        cout << "Inserting 10:" << endl;
        rb.insert(27);
        rb.printTree();
        cout << "Inserting 10:" << endl;
        rb.insert(25);
        rb.printTree();
        cout << "Inserting 10:" << endl;
        rb.remove(30);
        rb.printTree();

        cout << "remove 10:" << endl;
        rb.printTree();



        // rb.insert(10);
        // rb.insert(5);
        // rb.insert(15);
        // rb.insert(3);
        // rb.insert(7);
        // rb.insert(12);
        // rb.insert(18);
        // rb.insert(1);
        // rb.insert(6);
        // rb.insert(11);
        // rb.insert(20);
        // rb.insert(4);
        // rb.insert(14);
        // rb.insert(16);
        // rb.insert(8);
        // rb.remove(10);
        // rb.printTree();

    
    
    return 0;
}
