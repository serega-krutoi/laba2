#pragma once
#include <iostream>

using namespace std;

struct SetNode {
    int key;
    SetNode* next;

    SetNode(int k) : key(k), next(nullptr) {}
};

struct Set {
    static const int TABLE_SIZE = 101; // простое число, можно поменять
    SetNode* table[TABLE_SIZE];
    int count;

    Set();

    bool contains(int key) const;
    bool insert(int key);
    bool erase(int key);
    int size() const;
    void clear();
    void print() const;

    ~Set();

private:
    size_t hash(int key) const;
};
