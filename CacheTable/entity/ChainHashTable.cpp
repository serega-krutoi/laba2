#include "ChainHashTable.h"
#include<iostream>

using namespace std;

// Размер хеш-таблицы для метода цепочек
const int TABLE_SIZE = 5;

// Массив указателей на начала списков (корзины хеш-таблицы)
Node* hashTable[TABLE_SIZE];

// Хеш-функция djb2 для строкового ключа
size_t djb2_hash(const string& key) {
    size_t hash = 5381; 
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<size_t>(c); // hash * 33 + c
    }

    return hash % TABLE_SIZE; // индекс корзины в диапазоне [0, TABLE_SIZE)
}

// Вставка пары (key, value) в хеш-таблицу с цепочками
void insert(const string& value, const string& key) {
    int index = djb2_hash(key);           // номер корзины
    
    // Проверка, не существует ли уже такой ключ
    Node* current = hashTable[index];
    while (current != nullptr) {
        if (current->key == key) {
            // Ключ уже существует - выводим сообщение
            cout << "Ошибка: ключ '" << key << "' уже занят!" << endl;
            return; // выходим без добавления
        }
        current = current->next;
    }
    
    // Если ключ не найден, добавляем новый узел
    Node* newNode = new Node(key, value); // новый узел
    // Новый узел идёт в начало списка по индексу index
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    
    cout << "Ключ '" << key << "' успешно добавлен." << endl;
}

// Поиск значения по ключу в хеш-таблице
string search(const string& key) {
    int index = djb2_hash(key);          // номер корзины
    Node* current = hashTable[index];
    // Просмотр списка в выбранной корзине
    while (current != nullptr) {
        if (current->key == key) {
            return current->data;        // найден нужный ключ
        }
        current = current->next;
    }
    // Ключ отсутствует
    return "Not found";
}

// Удаление узла по ключу из хеш-таблицы
void remove(const string& key) {
    int index = djb2_hash(key);          // номер корзины
    Node* current = hashTable[index];
    Node* prev = nullptr;

    // Поиск узла с нужным ключом, хранится указатель на предыдущий узел
    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    // Ключ отсутствует
    if (current == nullptr) return;

    // Удаление узла из списка
    if (prev == nullptr) {
        // удаляется первый узел в цепочке
        hashTable[index] = current->next;
    } else {
        prev->next = current->next;
    }

    delete current; // освобождение памяти узла
}
