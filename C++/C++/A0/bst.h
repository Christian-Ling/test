#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;



class bstree
{
 public:
        bstree();
        void in( );
        void pre( );
        void post( );
        void insert( int x );
        int search( int x );
        void remove( int x );
        void printA();
        int height();
        char bigger();
        int numNodes();
 private:
        void insertR( int t, int x );
        void insertI( int x );
        int searchI( int x );
        int searchR( int x, int r );
        void removeI( int x );
        void pre(int r);
        void in(int r);
        void post(int r);
        int numNodes(int r);
        int height(int r);
        int *tr;    // array
        int LAST;   // last valid location

};

#endif