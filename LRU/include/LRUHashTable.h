#pragma once
#include<string>
#include"TwoLinked.h"

using namespace std;

const int LRU_TABLE_SIZE = 17; // простое число, можно любое

struct LRUHashNode {
    string key;
    string value;
    TwoLinkedNode* listNode;   // указатель на узел в двусвязном списке
    LRUHashNode* next;

    LRUHashNode(const string& k, const string& v, TwoLinkedNode* node) : key(k), value(v), listNode(node), next(nullptr) {}
};

size_t lru_djb2_hash(const string& key);
LRUHashNode* lru_hash_find(LRUHashNode* table[], const string& key);
void lru_hash_insert(LRUHashNode* table[], const string& key, const string& value, TwoLinkedNode* node);
void lru_hash_remove(LRUHashNode* table[], const string& key);
