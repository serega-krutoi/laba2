#include <iostream>
#include <string>
#include "include/ChainHashTable.h"

using namespace std;

//const int TABLE_SIZE = 5;
//Node* hashTable[TABLE_SIZE];

// Проверка, являются ли две строки изоморфными
bool areIsomorphic(const string& a, const string& b) {
    // При различной длине строк изоморфия невозможна
    if (a.size() != b.size()) return false;

    // Две хеш-таблицы:
    // mapAB: символ из a отображается в символ из b
    // mapBA: символ из b отображается в символ из a
    
    // Инициализируем хеш-таблицы
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashTable[i] = nullptr;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        char ca = a[i];
        char cb = b[i];

        // Оборачиваем символ в строку длины 1
        string keyA(1, ca);
        string keyB(1, cb);

        string mappedB = search(keyA);  // что отображается на a[i]
        string mappedA = search(keyB);  // что отображается на b[i]

        // Если для символа из a уже есть пара, но текущий символ b не совпадает,
        // изоморфия нарушается
        if (mappedB != "Not found" && mappedB[0] != cb) {
            return false;
        }

        // Аналогичная проверка для отображения b → a
        if (mappedA != "Not found" && mappedA[0] != ca) {
            return false;
        }

        // Новое соответствие с обеих сторон отсутствует — создаём его
        if (mappedB == "Not found" && mappedA == "Not found") {
            insert(keyB, keyA); // a[i] → b[i]
            insert(keyA, keyB); // b[i] → a[i]
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