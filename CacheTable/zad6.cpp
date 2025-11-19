#include <iostream>
#include <string>

// Вариант 7

//g++ zad6.cpp -o m 

using namespace std;

// Размер хеш-таблицы для отображения символов
const int TABLE_SIZE = 17;

// Узел связного списка для реализации хеш-таблицы с цепочками
struct Node {
    string key;     // ключ (один символ в строке)
    string value;   // значение (тоже один символ в строке)
    Node* next;

    Node(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

// Хеш-функция djb2 для строкового ключа
size_t djb2_hash(const string& key) {
    size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c); // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

// Поиск узла по ключу в конкретной хеш-таблице (с цепочками)
Node* find(Node* table[], const string& key) {
    size_t index = djb2_hash(key); // индекс корзины
    Node* curr = table[index];

    // Просмотр списка на этом индексе
    while (curr != nullptr) {
        if (curr->key == key) {
            return curr;          // найден узел с совпадающим ключом
        }
        curr = curr->next;
    }
    return nullptr;               // ключ отсутствует
}

// Вставка пары (key, value) в хеш-таблицу
// При наличии такого ключа значение перезаписывается
void insert(Node* table[], const string& key, const string& value) {
    size_t index = djb2_hash(key);
    Node* curr = table[index];

    // Поиск узла с указанным ключом
    while (curr != nullptr) {
        if (curr->key == key) {
            curr->value = value; // обновление значения
            return;
        }
        curr = curr->next;
    }

    // Новый ключ: создаём узел и добавляем его в начало списка
    Node* node = new Node(key, value);
    node->next = table[index];
    table[index] = node;
}

// Проверка, являются ли две строки изоморфными
bool areIsomorphic(const string& a, const string& b) {
    // При различной длине строк изоморфия невозможна
    if (a.size() != b.size()) return false;

    // Две хеш-таблицы:
    // mapAB: символ из a отображается в символ из b
    // mapBA: символ из b отображается в символ из a
    Node* mapAB[TABLE_SIZE] = {nullptr};
    Node* mapBA[TABLE_SIZE] = {nullptr};

    for (size_t i = 0; i < a.size(); ++i) {
        char ca = a[i];
        char cb = b[i];

        // Оборачиваем символ в строку длины 1
        string keyA(1, ca);
        string keyB(1, cb);

        Node* nodeAB = find(mapAB, keyA);
        Node* nodeBA = find(mapBA, keyB);

        // Если для символа из a уже есть пара, но текущий символ b не совпадает,
        // изоморфия нарушается
        if (nodeAB != nullptr && nodeAB->value[0] != cb) {
            return false;
        }

        // Аналогичная проверка для отображения b → a
        if (nodeBA != nullptr && nodeBA->value[0] != ca) {
            return false;
        }

        // Новое соответствие с обеих сторон отсутствует — создаём его
        if (nodeAB == nullptr && nodeBA == nullptr) {
            insert(mapAB, keyA, keyB); // a[i] → b[i]
            insert(mapBA, keyB, keyA); // b[i] → a[i]
        }
    }

    // Все пары символов удовлетворяют условиям изоморфии
    return true;
}

int main() {
    string a, b;
    cout << "Введите первую строку: ";
    cin >> a;
    cout << "Введите вторую строку: ";
    cin >> b;

    if (areIsomorphic(a, b)) {
        cout << "Строки изоморфны\n";
    } else {
        cout << "Строки НЕ изоморфны\n";
    }

    return 0;
}
