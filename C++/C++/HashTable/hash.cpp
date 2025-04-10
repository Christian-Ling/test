#include "hash.h"

HashTable::HashTable(int size, float loadFactorThreshold)
{
    tableSize = size;
    threshold = loadFactorThreshold;
    elementCount = 0;
    table = new vector<pair<string, int>>[tableSize];
}

HashTable::~HashTable()
{
    delete[] table;
}

int HashTable::hash(const string& key)
{
    int hashValue = 0;
    for( char c : key)
        hashValue = (hashValue * 31 + c) % tableSize;

    return hashValue;
}

void HashTable::insert(const string& key, int value)
{
    //do we have to resize the table?
    float alpha = (float)(elementCount + 1) / tableSize;
    if(alpha > threshold)
        resizeTable();

    int index = hash(key);
    table[index].push_back(make_pair(key, value));
    elementCount++;
}

bool HashTable::search(const string& key, int value)
{
    int index = hash(key);

    for(const auto& pair : table[index])
    {
        if(pair.first == key) {
            value == pair.second;
            return true;
        }
        
    }

    return false;
}