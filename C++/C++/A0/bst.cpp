
#include <iostream>
#include <fstream>
#include <cstdio>
#include "bst.h"
using namespace std;



// use 64 as size
bstree::bstree()
{
        tr = new int[64];
        LAST = 63;
        for ( int k = 1; k <= LAST; k++ )
                tr[k] = 0;
}

void bstree::pre(int r)
{
    if ( r > LAST || tr[r] == 0 )
        return;
    printf("%2d ", tr[r]);
    pre(r*2);
        pre(r*2+1);
}

void bstree::in(int r)
{
    if ( r > LAST || tr[r] == 0)
               return;
        in(r*2);
        printf("%2d ", tr[r]);
        in(r*2+1);
}

void bstree::in()
{
        cout << "Inorder: ";
        in(1);
        cout << endl;
}


void bstree::pre()
{
 cout << "preorder: ";
 pre(1);
 cout << endl;
}

void bstree::post()
{
       cout << "postorder: ";
        post(1);
        cout << endl;
}


void bstree::post(int r)
{

        if ( r > LAST || tr[r] == 0 )
                return;
        post(r*2);
        post(r*2+1);
        printf("%2d ", tr[r]);

}

// insert - recursive
void bstree::insertR( int r, int val )
{
    if (r > LAST)
        {
        cout << "Tree is full" << val << "cant be added." << endl;
        return;
    }
    if (tr[r] == 0)
        {
        tr[r] = val;
        return;
    }
    if (tr[r] == val) {
        cout << "same value " << val << " not added." << endl;
        return;
    }
    if (val < tr[r])
        insertR(r * 2, val);
        else
        insertR(r * 2 + 1, val);
}

int insertCount = 0;

void bstree::insertI(int val)
{
    if (search(val))
        {
        cout << "same value " << val << " not added" << endl;
        return;
    }

        int spot = 1;
while (tr[spot] != 0) {
        if (spot > LAST) {
            cout << "Tree is full, cannot insert " << val << endl;
            insertCount++; // Count failed insertion
            return;
        }
        if (val < tr[spot]) {
            spot = spot * 2; // Go left
        } else {
            spot = spot * 2 + 1; // Go right
        }
                }
        /* move down to open spot
        while ( tr[spot] != 0 )
        {
                if( val == tr[spot] )
                        return;

                if (val < tr[spot] )
                        spot = spot * 2;
            else
                        spot = spot * 2 + 1;

                if( spot > LAST )
                {
                        cout << "to big\n" << endl;
                        return;

                }
        }
        */
        // fill in the value
        tr[spot] = val;
}


void bstree::insert( int val )
{
        insertI( val );
}

void bstree::remove( int val )
{
        removeI ( val );
}

void bstree::removeI( int x )
{
        int r = 1;
        int par = 0;

        while ( r <= LAST && tr[r] != 0 && tr[r] != x)
        {
                par = r;
                if (x < tr[r])
                        r = r * 2;
                else
                        r = r * 2 + 1;
        }

        if (r > LAST || tr[r] == 0)
        {
                cout << x << " not found in tree \n";
                return;
        }

        if (r * 2 > LAST || (tr[r * 2] == 0 && tr[r * 2 + 1] == 0))
        {
                tr[r] = 0;
        }

        else if (tr[r * 2] == 0 )
        {
                tr[r] = tr[r * 2 + 1];
                tr[r * 2 + 1] == 0;
        } else if (tr[r * 2 + 1] == 0)
        {
                tr[r] = tr[r * 2];
                tr[r * 2] = 0;
        } else {
                int right = r * 2 + 1;
                int rightPar = r;

                while (right * 2 <= LAST && tr[right * 2] != 0)
                {
                        rightPar = right;
                        right = right * 2;
                }

                tr[r] = tr[right];

                if (rightPar == r)
                        tr[rightPar * 2 + 1] = tr[right * 2 + 1];
                else
                        tr[rightPar * 2] = tr[right * 2 + 1];

                tr[right] = 0;
        }

        cout << "Value " << x << " was removed.\n";
}

int bstree::search( int val )
{
        return searchI( val );
}


// search - iterative
int bstree::searchI( int val )
{
        int r = 1;

            while ( tr[r] != 0 )
    {
        if( val == tr[r] )
            return 1;

        if (val < tr[r] )
            r = r * 2;
        else
           r = r * 2 + 1;
        }

        return 0;
}




int bstree::searchR( int x, int r )
{

        if ( x == tr[r] )
                return 1;

        if (tr[r] == 0 )
                return 0;

        if ( x < tr[r] )
                return searchR( x, r*2 );
        else
                return searchR( x, r*2+1 );

}



void bstree::printA() {

    const int maxSize = LAST;

    for (int i = 1; i <= maxSize; i++) {
        cout << tr[i] << " ";
    }
    cout << endl;
}
    

int bstree::numNodes()
{
        return numNodes(1);
}

int bstree::numNodes( int myroot )
{
        if (tr[myroot] == 0 )
                return 0;
        int LTcount, RTcount, answer;

        LTcount = numNodes( myroot * 2 );
        RTcount = numNodes( myroot * 2 + 1 );
        answer = LTcount + RTcount + 1;
        return answer;

}

int bstree::height(int r){
    if (r > LAST || tr[r] == 0)
        {
        return -1;
    }
        int lHeight, rHeight, final;

     lHeight = height( r * 2 );
     rHeight = height( r * 2 + 1 );

        if (lHeight > rHeight)
                return 1 + lHeight;
        else
                return 1 + rHeight;
}


int bstree::height()
{
    return height(1); // Start from the root node
}

char bstree::bigger()
{

int lHeight = height(2);
int rHeight = height(3);

        if (lHeight > rHeight)
        return 'L';
        else if (rHeight > lHeight)
        return 'R';
        else
        return 'E';
}

/*
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
    /*

    t.pre();
    cout << endl;
    t.in();
    cout << endl;
        t.remove(30);
        t.remove(4);
        t.in();
        cout << endl;
    cout << "Height of tree: " << t.height() << endl;
    cout << "The taller side is: " << t.bigger() << endl;

return 0;
}
*/
