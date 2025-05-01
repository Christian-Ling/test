#include "AutoComplete.h"
#include <iostream>
#include <cstring>
#include "Words.cpp"

using namespace std;

int main() {
    const int numWords = sizeof(words) / sizeof(words[0]);

    RBTNode* dictionary = nullptr;
    SplayNode* splayRoot = nullptr;
    AVLNode* avlRoot = nullptr;

    for (int i = 0; i < numWords; ++i) {
        dictionary = insertRBT(dictionary, words[i]);
        addFrequency(words[i], 1);
        splayRoot = insertSplay(splayRoot, words[i]);
        avlRoot = insertAVL(avlRoot, words[i], getFrequency(words[i]));
    }

    char input[50];
    while (true) {
        cout << "\nEnter a prefix (or 'exit' to quit): ";
        cin >> input;
        if (strcmp(input, "exit") == 0) break;

        int found = 0;
        for (int i = 0; i < numWords; ++i) {
            if (strcmp(words[i], input) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            cout << "Note: This word is not in the dictionary.\n";
        }

        cout << "Suggestions:\n";
        getSuggestions(dictionary, input);  
    }

    return 0;
}
