#include "../include/LRUHashTable.h"

// Хеш-функция для строк
size_t lru_djb2_hash(const string& key) {
    size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    return hash % LRU_TABLE_SIZE;
}

// Поиск узла по ключу
LRUHashNode* lru_hash_find(LRUHashNode* table[], const string& key) {
    size_t index = lru_djb2_hash(key);
    LRUHashNode* curr = table[index];

    while (curr) {
        if (curr->key == key) return curr;
        curr = curr->next;
    }
    return nullptr;
}

// Вставка новой пары или обновление существующей
void lru_hash_insert(LRUHashNode* table[], const string& key,
                     const string& value, TwoLinkedNode* node)
{
    size_t index = lru_djb2_hash(key);
    LRUHashNode* curr = table[index];

    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            curr->listNode = node;
            return;
        }
        curr = curr->next;
    }

    LRUHashNode* n = new LRUHashNode(key, value, node);
    n->next = table[index];
    table[index] = n;
}

// Удаление пары по ключу
void lru_hash_remove(LRUHashNode* table[], const string& key) {
    size_t index = lru_djb2_hash(key);
    LRUHashNode* curr = table[index];
    LRUHashNode* prev = nullptr;

    while (curr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) return;

    if (!prev) table[index] = curr->next;
    else prev->next = curr->next;

    delete curr;
}
