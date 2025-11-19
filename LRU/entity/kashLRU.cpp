#include "../include/kashLRU.h"

// Создание кэша: задаётся объём и пустая таблица
LRUCache::LRUCache(int cap) : capacity(cap), size(0) {
    for (int i = 0; i < LRU_TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

string LRUCache::get(const string& key) {
    // Поиск пары по ключу
    LRUHashNode* hnode = lru_hash_find(table, key);
    if (!hnode) return "NOT_FOUND";

    // Ключ используется, значит узел переносится в начало списка
    order.move_to_front(hnode->listNode);
    return hnode->value;
}

void LRUCache::put(const string& key, const string& value) {
    // Поиск пары по ключу
    LRUHashNode* hnode = lru_hash_find(table, key);

    if (hnode) {
        // Ключ уже существует: новое значение и узел — в начало
        hnode->value = value;
        order.move_to_front(hnode->listNode);
        return;
    }

    // Если объём заполнен — удаляется наиболее старый элемент
    if (size == capacity) {
        if (order.tail) {
            string oldKey = order.tail->data;
            lru_hash_remove(table, oldKey); // убрать из таблицы
            order.delete_back();            // убрать из списка
            size--;
        }
    }

    // Новый ключ — в начало
    order.push_forward(key);
    TwoLinkedNode* node = order.head;

    // Запись в таблицу
    lru_hash_insert(table, key, value, node);

    size++;
}
