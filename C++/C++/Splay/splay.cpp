#include "splay.h"

SplayTree::SplayTree() 
{
    root = nullptr; 
}


// aka Zig
SplayTree::Node* SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// aka Zag
SplayTree::Node* SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}



SplayTree::Node* SplayTree::splay(Node* root, int key) {
       
    if (!root || root->key == key)
    {
        return root; 
    }
    if (key < root->key) 
    { 
        if(!root->left) 
            return root;


        if (key < root->left->key) 
        { 
         
            root->left->left = splay(root->left->left, key); 
            root = rotateRight(root);

        } 
        else if (key > root->left->key )
        {  
            root->left->right = splay(root->left->right, key); 
            if (root->left->right) 
                root->left = rotateLeft(root->left); 
        } 
          

            if (root->left) {
                return rotateRight(root);
            } else {
                return root;
            }
            
    } 
    else
    { 
        if(!root->right)
            return root;


         if(key > root->right->key){
            root->right->right = splay(root->right->right,key);
            root = rotateLeft(root);

        }
        else if(key < root->right->key)
        {
            root->right->left = splay(root->right->left, key);

            if(root->right->left)
            {
              root->right = rotateRight(root->right); 
            }
        }
        if (root->right) {
            return rotateLeft(root);
        } else {
            return root;
        }
        
    }
    //return root;
}




SplayTree::Node* SplayTree::insertNode(Node* root, int key) {
    // complete this
    if (!root)
    {
        return new Node(key);
    }

        root = splay(root,key);

    if(root->key == key)
    {
        return root;
    }
    Node* newnode = new Node(key);

        if(key < root->key)
        {
            
            newnode->right = root;
            newnode->left = root->left;
            root->left = nullptr;
        }
        else 
        {
    
            newnode->left = root;
            newnode->right = root->right;
            root->right = nullptr;
  
        }
        return newnode;
    }



SplayTree::Node* SplayTree::deleteNode(Node* root, int key) {
    // complete this
    if (root == nullptr)
        return nullptr;

    root = splay(root, key);

    if (root->key != key)
        return root;

    if (root->left == nullptr)
    {
        Node* temp = root->right;
        delete root;
        return temp;
    } 


    Node* temp = root;
    root = splay(root->left, key);
    root->right = temp->right;
    return temp;

    delete root;

}



void SplayTree::insert(int key) {
    root = insertNode(root, key);
}


void SplayTree::remove(int key) {
    root = deleteNode(root, key);
}


bool SplayTree::search(int key) {
    root = splay(root, key);
    return (root && root->key == key);
}


void SplayTree::printTree(Node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr) {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child
    cout << endl;
    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->key << endl;

    // Print the left child
    printTree(root->left, space);
}

void SplayTree::display() {
    printTree(root, 0);
    cout << endl;
}
