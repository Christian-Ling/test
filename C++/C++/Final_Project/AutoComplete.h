#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

const int MAX_WORDS = 1000;

struct WordFreqEntry {
    char word[50];
    int frequency;
};

// Utility
bool strEqual(const char* a, const char* b);
bool strLess(const char* a, const char* b);
bool startsWith(const char* word, const char* prefix);
void copyStr(char* dest, const char* src);
int getFrequency(const char* word);
void addFrequency(const char* word, int freq);


// AVL
struct AVLNode {
    char word[50];
    int frequency;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(const char* w, int f);
};
AVLNode* insertAVL(AVLNode* root, const char* word, int freq);

// Splay
struct SplayNode {
    char word[50];
    SplayNode* left;
    SplayNode* right;
    SplayNode(const char* w);
};
SplayNode* insertSplay(SplayNode* root, const char* word);

// RBT
enum Color { RED, BLACK };

struct RBTNode {
    char word[50];
    Color color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
    RBTNode(const char* w);
};
RBTNode* insertRBT(RBTNode* root, const char* word);

// Suggestion
void getSuggestions(RBTNode* dict, const char* prefix);

#endif
