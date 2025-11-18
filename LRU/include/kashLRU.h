#pragma once
#include<string>
#include"TwoLinked.h"
#include"LRUHashTable.h"

using namespace std;

struct LRUCache {
    int capacity;
    int size;
    listTwoLinked order;                // порядок ключей: head – самый свежий, tail – самый старый
    LRUHashNode* table[LRU_TABLE_SIZE]; // хэш-таблица: key -> {value, указатель на узел списка}

    LRUCache(int cap);

    string get(const string& key);                  // вернуть значение или "NOT_FOUND"
    void put(const string& key, const string& value); // вставить / обновить
};
