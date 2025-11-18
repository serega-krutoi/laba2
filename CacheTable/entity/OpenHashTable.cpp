#include"OpenHashTable.h"

using namespace std;

const int TABLE_SIZE = 7;
Entry* table[TABLE_SIZE];

size_t djb2_hash(const string& key) {
    size_t hash = 5381; 
    for (char c : key) hash = ((hash << 5) + hash) + static_cast<size_t>(c);

    return hash % TABLE_SIZE;
}

void insert(const string& key, const string& value) {
    int index = djb2_hash(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (index + i) % TABLE_SIZE;
        if (table[probe] == nullptr || table[probe]->isDelete) {
            table[probe] = new Entry(key, value);
            return;
        }
        
    }
    cout << "Таблица заполнена!\n";
}

string search(const string& key) {
    int index = djb2_hash(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (index + i) % TABLE_SIZE;
        if (table[probe] == nullptr) return "Не найдено!\n";
        if (!table[probe]->isDelete && table[probe]->key == key) return table[probe]->data;
    }
    return "Не найдено!\n";
}

void remove(const string& key) {
    int index = djb2_hash(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (index + i) % TABLE_SIZE;
        if (table[probe] == nullptr) return;
        if (!table[probe]->isDelete && table[probe]->key == key) {
            table[probe]->isDelete = true;
            return;
        }
    }
}