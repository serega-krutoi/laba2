#include"../include/kashLRU.h"

LRUCache::LRUCache(int cap) : capacity(cap), size(0) {
    for (int i = 0; i < LRU_TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

string LRUCache::get(const string& key) {
    LRUHashNode* hnode = lru_hash_find(table, key);
    if (!hnode) return "NOT_FOUND";

    // ключ использован – перенос узла в голову списка
    order.move_to_front(hnode->listNode);
    return hnode->value;
}

void LRUCache::put(const string& key, const string& value) {
    LRUHashNode* hnode = lru_hash_find(table, key);

    if (hnode) {
        // уже есть: обновить значение и сделать самым свежим
        hnode->value = value;
        order.move_to_front(hnode->listNode);
        return;
    }

    // если нет и кэш полон – выбросить LRU (узел в хвосте)
    if (size == capacity) {
        if (order.tail) {
            string oldKey = order.tail->data; // в data храним ключ
            lru_hash_remove(table, oldKey);   // удалить из хэша
            order.delete_back();              // удалить из списка
            size--;
        }
    }

    // новый узел в голове списка
    order.push_forward(key);           // ключ в data
    TwoLinkedNode* node = order.head;  // только что добавленный узел

    // добавление в хэш-таблицу
    lru_hash_insert(table, key, value, node);

    size++;
}
