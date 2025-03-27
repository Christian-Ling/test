#include "avl.h"

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{
    destroyTree(root);
}

void AVLTree::destroyTree(Node* node)
{
    if(node)
    {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::height(Node* node)
{
    if(node)
        return node->height;
    else
        return -1;
}

int AVLTree::balanceFactor(Node* node)
{
    if(node)
        return height(node->left) - height(node->right);
    else
        return 0;
}

Node* AVLTree::rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* AVLTree::rotateLeft(Node* y)
{
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

void AVLTree::printTree(Node* root, int space) {
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
    cout << root->key << endl;

    // Print the left child
    printTree(root->left, space);
}



Node* AVLTree::insert(Node* node, int key)
{
    if(node == nullptr)
    {
    cout << "inserting key: " << key << endl;
        return new Node(key);
    }

    if(key > node->key)
        node->right = insert(node->right, key);
    else if (key < node->key)
        node->left = insert(node->left, key);
    else 
        return node;
    
        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if ( balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;

}

Node* AVLTree::remove(Node* node, int key)
{
    if (node == nullptr)
        return node;
    
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        if ((node->left == nullptr) || (node->right == nullptr))
        {
            Node* temp = node->left ? node->left : node->right;
            if (temp == nullptr)
            {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr)
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);
    if (balance > 1 && balanceFactor(node->left) < 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);
    if (balance < -1 && balanceFactor(node->right) > 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


Node* AVLTree::minValueNode(Node* node) // helper for remove and finds successor
{
    Node* current = node;
    while ( current->left != nullptr)
        current = current->left;
    return current;
}

//****************************public ********************************/

void AVLTree::insert(int key)
{

   root = insert(root, key);
    
}

void AVLTree::remove(int key)
{
    cout << "removing key: " << key << endl;
    root = remove(root, key);
}

void AVLTree::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}