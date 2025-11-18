#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 17; // маленькое простое число

struct Node {
    string key;
    string value;
    Node* next;

    Node(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};

size_t djb2_hash(const string& key) {
    size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    return hash % TABLE_SIZE;
}

// поиск узла по ключу в конкретной таблице
Node* find(Node* table[], const string& key) {
    size_t index = djb2_hash(key);
    Node* curr = table[index];
    while (curr != nullptr) {
        if (curr->key == key) return curr;
        curr = curr->next;
    }
    return nullptr;
}

// вставка (или перезапись) в конкретную таблицу
void insert(Node* table[], const string& key, const string& value) {
    size_t index = djb2_hash(key);
    Node* curr = table[index];

    while (curr != nullptr) {
        if (curr->key == key) {
            curr->value = value; // обновляем
            return;
        }
        curr = curr->next;
    }

    Node* node = new Node(key, value);
    node->next = table[index];
    table[index] = node;
}

bool areIsomorphic(const string& a, const string& b) {
    if (a.size() != b.size()) return false;

    // две хеш-таблицы: a→b и b→a
    Node* mapAB[TABLE_SIZE] = {nullptr};
    Node* mapBA[TABLE_SIZE] = {nullptr};

    for (size_t i = 0; i < a.size(); ++i) {
        char ca = a[i];
        char cb = b[i];

        string keyA(1, ca);
        string keyB(1, cb);

        Node* nodeAB = find(mapAB, keyA);
        Node* nodeBA = find(mapBA, keyB);

        // есть уже соответствие a->? и оно не совпадает с текущим b
        if (nodeAB != nullptr && nodeAB->value[0] != cb) {
            return false;
        }

        // есть уже соответствие ?->b и оно не совпадает с текущим a
        if (nodeBA != nullptr && nodeBA->value[0] != ca) {
            return false;
        }

        // если ещё не было, добавляем оба направления
        if (nodeAB == nullptr && nodeBA == nullptr) {
            insert(mapAB, keyA, keyB); // a[i] -> b[i]
            insert(mapBA, keyB, keyA); // b[i] -> a[i]
        }
    }

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
