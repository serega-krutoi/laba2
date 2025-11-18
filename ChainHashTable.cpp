#include"ChainHashTable.h"

using namespace std;

const int TABLE_SIZE = 5;
Node* hashTable[TABLE_SIZE];

size_t djb2_hash(const string& key) {
    size_t hash = 5381; 
    for (char c : key) hash = ((hash << 5) + hash) + static_cast<size_t>(c);

    return hash % TABLE_SIZE;
}

void insert(const string& value, const string& key) {
    int index = djb2_hash(key);
    Node* newNode = new Node(key, value);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

string search(const string& key) {
    int index = djb2_hash(key);
    Node* current = hashTable[index];
    while (current != nullptr) {
        if (current->key == key) return current->data;
        current = current->next;
    }
    return "Not found";
}

void remove(const string& key) {
    int index = djb2_hash(key);
    Node* current = hashTable[index];
    Node* prev = nullptr;

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) return;
    if (prev == nullptr) hashTable[index] = current->next;
    else prev->next = current->next;

    delete current;
}  
