#include "../include/set.h"

Set::Set() : count(0) {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table[i] = nullptr;
}

size_t Set::hash(int key) const {
    // простая хэш-функция для int
    // можно взять abs(key) % TABLE_SIZE
    unsigned int x = static_cast<unsigned int>(key);
    return x % TABLE_SIZE;
}

bool Set::contains(int key) const {
    size_t idx = hash(key);
    SetNode* curr = table[idx];
    while (curr != nullptr) {
        if (curr->key == key) return true;
        curr = curr->next;
    }
    return false;
}

bool Set::insert(int key) {
    if (contains(key)) return false; // уже есть

    size_t idx = hash(key);
    SetNode* node = new SetNode(key);
    node->next = table[idx];   // вставка в голову цепочки
    table[idx] = node;
    ++count;
    return true;
}

bool Set::erase(int key) {
    size_t idx = hash(key);
    SetNode* curr = table[idx];
    SetNode* prev = nullptr;

    while (curr != nullptr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false; // нет такого

    if (prev == nullptr) {
        table[idx] = curr->next;
    } else {
        prev->next = curr->next;
    }
    delete curr;
    --count;
    return true;
}

int Set::size() const {
    return count;
}

void Set::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        SetNode* curr = table[i];
        while (curr != nullptr) {
            SetNode* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        table[i] = nullptr;
    }
    count = 0;
}

void Set::print() const {
    cout << "{ ";
    for (int i = 0; i < TABLE_SIZE; ++i) {
        SetNode* curr = table[i];
        while (curr != nullptr) {
            cout << curr->key << " ";
            curr = curr->next;
        }
    }
    cout << "}";
}

Set::~Set() {
    clear();
}
