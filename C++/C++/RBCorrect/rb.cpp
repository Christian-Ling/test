#include "rb.h"

// ++++++++++++++++++++++++++++++ PUBLIC +++++++++++++++++++++++++++++++++++++++

RBTREE::RBTREE()
{
    
        TNULL = new Node(0);
        TNULL->color = BLACK;
        // TNULL->left = nullptr;
        // TNULL->right = nullptr;
        // TNULL->parent = nullptr;
    
        root = TNULL;
 //   } catch(const bad_alloc&) {
 //       throw MyException("Memory allocation failed for TNULL node.");
   

}

RBTREE::~RBTREE()
{
    deleteSubtree(root);
    delete TNULL;
}

void RBTREE::insert(int key)
{
    Node* node = nullptr;
        node = new Node(key);
    
    // node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    // node->parent = nullptr;
    // node->color = RED;

    if(root == TNULL)
    {
        root = node;
        root->color = BLACK;
        return;
    }

    insertR(root, node);
    insertFix(node);
}

void RBTREE::remove(int key)
{

        root = removeR(root, key);
   
}

void RBTREE::printTree()
{
    if(root == TNULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    print(root, 0);
}

// ++++++++++++++++++++++++++++++ PRIVATE +++++++++++++++++++++++++++++++++++++++++++++

void RBTREE::leftRotate(Node* y)
{
    Node* x = y->right;
    y->right = x->left;  // adoption

    if(x->left != TNULL) // updating parent of adopted left child
        x->left->parent = y; 

    // update parent of x
    x->parent = y->parent;
    if(y->parent == nullptr)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->left = y;
    y->parent = x;
}

void RBTREE::rightRotate(Node* y)
{
    Node* x = y->left;
    y->left = x->right;  // adoption

    if(x->right != TNULL) // updating parent of adopted left child
        x->right->parent = y; 

    // update parent of x
    x->parent = y->parent;
    if(y->parent == nullptr)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void RBTREE::insertR(Node*& root, Node*& node)
{
    if(root == TNULL)
    {
        root = node;
        return;
    }

    if(node->data < root->data)
    {
        if(root->left == TNULL)
        {
            root->left = node;
            node->parent = root;
        } else {
            insertR(root->left, node);
        }
    } else {
        if(root->right == TNULL)
        {
            root->right = node;
            node->parent = root;
        } else {
            insertR(root->right, node);
        }
    }
}

void RBTREE::insertFix(Node* k)
{
    Node* uncle;

    // always when Parent is RED - violates property 3
    while(k->parent->color == RED)
    {
        // Parent is right child
        if(k->parent == k->parent->parent->right)
        {
            uncle = k->parent->parent->left;
            // CASE 2 - Red Uncle
            if(uncle->color == RED){
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                // update k if there are any new violations up the tree
                k = k->parent->parent;
            } else { // uncle is black
                if(k == k->parent->left) {// CASE 3 - triangle case
                    k = k->parent;
                    rightRotate(k);
                }
                // CASE 4 - line case
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }

        } else { // Parent is left child (Mirror image of the prev one)
            uncle = k->parent->parent->right;
            // CASE 2: RED uncle
            if(uncle->color == RED)
            {
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else { // case 3
                if(k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                // case 4
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if(k == root){
            break;
        }

    }
    root->color = BLACK;
}


Node* RBTREE::removeR(Node* node, int key)
{


    if(key < node->data)
        node->left = removeR(node->left, key);
    else if (key > node->data)
        node->right = removeR(node->right, key);
    else {
        Node* y = node; // node to be deleted
        Node* x; // our replacement for deleted node
        Color y_original_color = y->color;

        if(node->left == TNULL) // CASE 1
        {
            x = node->right; 
            transplant(node, node->right);
        } else if(node->right == TNULL) // CASE 2
        {
            x = node->left;
            transplant(node, node->left);
        } else { // CASE 3
            y = successor(node->right);
            y_original_color = y->color;
            x = y->right; // right child of successor

            if(y->parent != node) {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }

            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
        delete node;
        if(y_original_color == BLACK) {
            deleteFix(x);
        }
    }

    return root;
}

void RBTREE::deleteFix(Node* x) {
    Node* sibling;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            sibling = x->parent->right;
            if (sibling->color == RED) { // case 1
                sibling->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                sibling = x->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) { // case 2
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->right->color == BLACK) { // case 3
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(sibling);
                    sibling = x->parent->right;
                }  // case 4
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            sibling = x->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                sibling = x->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(sibling);
                    sibling = x->parent->left;
                }
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RBTREE::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

Node* RBTREE::successor(Node* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

void RBTREE::deleteSubtree(Node* node) {
    if (node != TNULL) {
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
}

// // Print helper function
// void RBTREE::print(Node* root, int space) {
//     const int COUNT = 10;

//     if (root == TNULL) {
//         return;
//     }

//     space += COUNT;
//     print(root->right, space);

//     for (int i = COUNT; i < space; i++) {
//         cout << " ";
//     }
//     cout << root->data << (root->color == RED ? " [R]" : " [B]") << endl;

//     print(root->left, space);
// }

void RBTREE::print(Node* root, int space) {
    if (root == TNULL)
        return;

    space += 10;
    print(root->right, space);

    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    
    string color_code = (root->color == RED) ? RED_COLOR : BLACK_COLOR;
    cout << color_code << root->data << RESET_COLOR;
    cout << endl;
    print(root->left, space);
}
