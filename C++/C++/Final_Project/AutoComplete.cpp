#include "AutoComplete.h"
#include <iostream>
using namespace std;

WordFreqEntry wordFreq[MAX_WORDS];
int wordFreqCount = 0;

//-------------- Helper functions  --------------
int myMax(int a, int b) {
    return (a > b) ? a : b;
}

bool strEqual(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        ++a; ++b;
    }
    return *a == '\0' && *b == '\0';
}

bool strLess(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        ++a; ++b;
    }
    return *a < *b;
}

bool startsWith(const char* word, const char* prefix) {
    while (*prefix) {
        if (*word != *prefix) return false;
        ++word; ++prefix;
    }
    return true;
}

void copyStr(char* dest, const char* src) {
    while (*src) *dest++ = *src++;
    *dest = '\0';
}

//-------------- Hash Table --------------  
void addFrequency(const char* word, int freq) {
    for (int i = 0; i < wordFreqCount; ++i) {
        if (strEqual(wordFreq[i].word, word)) {
            wordFreq[i].frequency += freq;
            return;
        }
    }
    copyStr(wordFreq[wordFreqCount].word, word);
    wordFreq[wordFreqCount].frequency = freq;
    ++wordFreqCount;
}

int getFrequency(const char* word) {
    for (int i = 0; i < wordFreqCount; ++i) {
        if (strEqual(wordFreq[i].word, word)) {
            return wordFreq[i].frequency;
        }
    }
    return 0;
}

//-------------- AVL Tree --------------
AVLNode::AVLNode(const char* w, int f) : frequency(f), height(1), left(nullptr), right(nullptr) {
    copyStr(word, w);
}

int getHeight(AVLNode* n) {
    return n ? n->height : 0;
}

int getBalance(AVLNode* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = myMax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = myMax(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = myMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = myMax(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLNode* insertAVL(AVLNode* node, const char* word, int freq) {
    if (!node) return new AVLNode(word, freq);
    if (strLess(word, node->word)) node->left = insertAVL(node->left, word, freq);
    else if (strLess(node->word, word)) node->right = insertAVL(node->right, word, freq);
    else return node;

    node->height = 1 + myMax(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && strLess(word, node->left->word)) return rotateRight(node);
    if (balance < -1 && strLess(node->right->word, word)) return rotateLeft(node);
    if (balance > 1 && strLess(node->left->word, word)) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && strLess(word, node->right->word)) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

//-------------- Splay Tree --------------
SplayNode::SplayNode(const char* w) : left(nullptr), right(nullptr) {
    copyStr(word, w);
}

SplayNode* rotateRight(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode* rotateLeft(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode* splay(SplayNode* root, const char* key) {
    if (!root || strEqual(root->word, key)) return root;

    if (strLess(key, root->word)) {
        if (!root->left) return root;
        if (strLess(key, root->left->word)) {
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        } else if (strLess(root->left->word, key)) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = rotateLeft(root->left);
        }
        return (root->left == nullptr) ? root : rotateRight(root);
    } else {
        if (!root->right) return root;
        if (strLess(root->right->word, key)) {
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        } else if (strLess(key, root->right->word)) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = rotateRight(root->right);
        }
        return (root->right == nullptr) ? root : rotateLeft(root);
    }
}

SplayNode* insertSplay(SplayNode* root, const char* key) {
    if (!root) return new SplayNode(key);
    root = splay(root, key);
    if (strEqual(root->word, key)) return root;

    SplayNode* newNode = new SplayNode(key);
    if (strLess(key, root->word)) {
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

//-------------- Autocomplete --------------
void sortSuggestions(char suggestions[][50], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (getFrequency(suggestions[i]) < getFrequency(suggestions[j])) {
                char temp[50];
                copyStr(temp, suggestions[i]);
                copyStr(suggestions[i], suggestions[j]);
                copyStr(suggestions[j], temp);
            }
        }
    }
}

void collectWordsRBT(RBTNode* root, char suggestions[][50], int& count, const char* prefix) {
    if (!root || count >= MAX_WORDS) return;
    collectWordsRBT(root->left, suggestions, count, prefix);
    if (startsWith(root->word, prefix)) {
        copyStr(suggestions[count++], root->word);
    }
    collectWordsRBT(root->right, suggestions, count, prefix);
}


void getSuggestions(RBTNode* dict, const char* prefix) {
    char suggestions[MAX_WORDS][50];
    int count = 0;
    collectWordsRBT(dict, suggestions, count, prefix);
    sortSuggestions(suggestions, count);

    for (int i = 0; i < count; ++i) {
        cout << suggestions[i] << " (freq: " << getFrequency(suggestions[i]) << ")\n";
    }
}
