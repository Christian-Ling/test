// Autocomplete System: C++ Final Project
// Components: Splay Tree, Red-Black Tree (std::set), AVL Tree, Hash Table

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

//------------------------------------
// Hash Table for frequency and spelling check
unordered_map<string, int> wordFrequency;
unordered_map<string, bool> isValidWord;

//------------------------------------
// Red-Black Tree (std::set)
set<string> wordDictionary;

//------------------------------------
// AVL Tree (simplified version)
struct AVLNode {
    string word;
    int frequency;
    AVLNode *left, *right;
    int height;

    AVLNode(string w, int f) : word(w), frequency(f), left(nullptr), right(nullptr), height(1) {}
};

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLNode* insertAVL(AVLNode* node, string word, int freq) {
    if (!node) return new AVLNode(word, freq);
    if (word < node->word) node->left = insertAVL(node->left, word, freq);
    else if (word > node->word) node->right = insertAVL(node->right, word, freq);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && word < node->left->word) return rightRotate(node);
    if (balance < -1 && word > node->right->word) return leftRotate(node);
    if (balance > 1 && word > node->left->word) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && word < node->right->word) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//------------------------------------
// Splay Tree
struct SplayNode {
    string word;
    SplayNode *left, *right;
    SplayNode(string w) : word(w), left(nullptr), right(nullptr) {}
};

SplayNode* rightRotate(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* leftRotate(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* splay(SplayNode* root, const string& key) {
    if (!root || root->word == key) return root;
    if (key < root->word) {
        if (!root->left) return root;
        if (key < root->left->word) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (key > root->left->word) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }
        return (root->left == nullptr) ? root : rightRotate(root);
    } else {
        if (!root->right) return root;
        if (key > root->right->word) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        } else if (key < root->right->word) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

SplayNode* insertSplay(SplayNode* root, const string& key) {
    if (!root) return new SplayNode(key);
    root = splay(root, key);
    if (root->word == key) return root;

    SplayNode* newNode = new SplayNode(key);
    if (key < root->word) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    return newNode;
}

//------------------------------------
// Autocomplete System Integration
vector<string> getSuggestions(const string& prefix) {
    vector<string> suggestions;
    for (const auto& word : wordDictionary) {
        if (word.find(prefix) == 0) {
            suggestions.push_back(word);
        }
    }
    sort(suggestions.begin(), suggestions.end(), [](const string& a, const string& b) {
        return wordFrequency[a] > wordFrequency[b];
    });
    return suggestions;
}

//------------------------------------
// Main Function to Test System
int main() {
    vector<string> words = {"apple", "app", "application", "apt", "banana", "band", "bandana", "can", "candy", "cap", "dog", "dove", "elephant", "elephantine", "fish", "fishing", "goat", "goose", "grape", "grapefruit"};

    SplayNode* splayRoot = nullptr;
    AVLNode* avlRoot = nullptr;

    // Inserting words into all structures
    for (const string& word : words) {
        wordDictionary.insert(word);
        wordFrequency[word]++;
        isValidWord[word] = true;
        splayRoot = insertSplay(splayRoot, word);
        avlRoot = insertAVL(avlRoot, word, wordFrequency[word]);
    }

    string input;
    while (true) {
        cout << "\nEnter a prefix (or 'exit' to quit): ";
        cin >> input;
        if (input == "exit") break;

        if (!isValidWord[input]) {
            cout << "Note: This word is not in the dictionary.\n";
        }

        vector<string> suggestions = getSuggestions(input);
        if (suggestions.empty()) {
            cout << "No suggestions found.\n";
        } else {
            cout << "Suggestions:\n";
            for (const string& suggestion : suggestions) {
                cout << "- " << suggestion << "\n";
            }
        }
    }

    return 0;
}
