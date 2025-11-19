#include "../include/set.h"

// Конструктор: пустой набор, таблица вся из null
Set::Set() : count(0) {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table[i] = nullptr;
}

size_t Set::hash(int key) const {
    // Хеш для int: остаток от деления на размер таблицы
    unsigned int x = static_cast<unsigned int>(key);
    return x % TABLE_SIZE;
}

bool Set::contains(int key) const {
    // Поиск ключа в цепочке по индексу
    size_t idx = hash(key);
    SetNode* curr = table[idx];
    while (curr != nullptr) {
        if (curr->key == key) return true; // ключ найден
        curr = curr->next;
    }
    return false; // ключ отсутствует
}

bool Set::insert(int key) {
    // Дубликат не нужен
    if (contains(key)) return false;

    size_t idx = hash(key);
    // Новый узел для набора
    SetNode* node = new SetNode(key);
    // Узел ставится в начало цепочки
    node->next = table[idx];
    table[idx] = node;
    ++count;
    return true;
}

bool Set::erase(int key) {
    // Удаление узла с заданным значением
    size_t idx = hash(key);
    SetNode* curr = table[idx];
    SetNode* prev = nullptr;

    // Поиск нужного узла
    while (curr != nullptr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    // Нет такого ключа
    if (curr == nullptr) return false;

    // Удаление из цепочки
    if (prev == nullptr) {
        // Узел в голове
        table[idx] = curr->next;
    } else {
        prev->next = curr->next;
    }
    delete curr;
    --count;
    return true;
}

int Set::size() const {
    // Число ключей в наборе
    return count;
}

void Set::clear() {
    // Полная очистка всех цепочек
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
    // Вывод всех ключей из таблицы
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
    // Освобождение памяти при разрушении набора
    clear();
}
