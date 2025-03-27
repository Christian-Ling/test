#include "dsw.h"

//-----------------------Private-----------------//


// when left-heavy tree
void BST::rotateRight(Node*& node)
{
    if(node == nullptr || node->left == nullptr)
        return;

    //get the node to rotate right
    Node* leftChild = node->left;
    // 1) left node's right child is going to become the parents left child
    node->left = leftChild->right;
    // 2) parent is going to be right child of node that is rotated
    leftChild->right = node;
    // 3)
    node = leftChild;

}

//right heave tree
void BST::rotateLeft(Node*& node)
{
    if (node == nullptr || node->right == nullptr)
        return;
    

    // get the node to rotate L
    Node* rightChild = node->right;
    // 1) right nodes left child becomes the parents right child
    node->right = rightChild->left;
    // 2)parent is going to be left child of the node rotated
    rightChild->left = node;

    node = rightChild;
}

// Phase 1 - riht skewed linked list tree
void BST::createVine()
{
    if(root == nullptr)
        return;

    Node* grandparent = nullptr;
    Node* parent = root;
    Node* child = root->left;

    while(parent != nullptr)
    {
        if(child != nullptr) //there is left child
        {
            rotateRight(parent);
            if(grandparent == nullptr)
                root = parent;
            else
                grandparent->right = parent;
            child = parent->left;
        } else { // no left child so keep moving right
            grandparent = parent;

            parent = parent->right;
            if (parent != nullptr)
                 child = parent->left;
        }
    }
}

void BST::rebuildTree(int size)
{
    // how many left rotations
    // initial rotation
    int highestPowerof2 = (int)pow(2, log2(size+1));
    int m = (size + 1) - highestPowerof2; // number of extra nodes

    preformRotation(m);

    // subsequent rotations
    for(size = (size - m) / 2; size > 0; size /= 2)
        preformRotation(size);
}


//left rotate every second node nased on count
void BST::preformRotation(int count)
{
    Node* grandparent = nullptr;
    Node* parent = root;
    Node* child = root->right;

    for(int i = 0; i < count; i++)
    {
        if(child == nullptr)
            break;

        rotateLeft(parent);
        if(grandparent == nullptr)
            root = parent;
        else
            grandparent->right = parent;

        grandparent = parent;

        parent = parent->right;
        if(parent != nullptr)
            child = parent->right;
    }
}

void BST::printTree(Node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr) {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->data << endl;

    // Print the left child
    printTree(root->left, space);
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    deleteTree(root);

}

void BST::deleteTree(Node*& node)
{
    if ( node == nullptr)
        return;
    
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void BST::insert(int val)
{
    Node* newNode = new Node(val);
    if (root = nullptr)
    {
        root = newNode;
        return;
    }

    Node* curr = root;
    Node* parent = nullptr;

    while(curr != nullptr)
    {
        parent = curr;
        if (val < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if ( val < parent->data)
        parent->left = newNode;
    else   
        parent->right = newNode;
}

void BST::dswBalance()
{
    if (root == nullptr)
        return;

    createVine();

    cout << "After phase 1: ";
    display();

    int size = 0;
    Node* temp = root;
    while(temp != nullptr)
    {
        size++;
        temp = temp->right;
    }
    rebuildTree(size);

}

void BST::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}