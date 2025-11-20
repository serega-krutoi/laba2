#include "OpenHashTable.h"

using namespace std;

// Размер хеш-таблицы при открытой адресации
const int TABLE_SIZE = 7;

// Глобальный массив указателей на записи
// Пустая ячейка обозначается значением nullptr
Entry* table[TABLE_SIZE];

// Хеш-функция djb2 для строкового ключа
size_t djb2_hash(const string& key) {
    size_t hash = 5381; 
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<size_t>(c); // hash * 33 + c
    }

    return hash % TABLE_SIZE;
}

// Вставка пары (key, value) в хеш-таблицу с линейным пробированием
void insert(const string& key, const string& value) {
    int index = djb2_hash(key);

    // Сначала проверяем, нет ли уже такого ключа в таблице
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (index + i) % TABLE_SIZE;
        
        // Если нашли существующий ключ (не удалённый)
        if (table[probe] != nullptr && !table[probe]->isDelete && table[probe]->key == key) {
            cout << "Ошибка: ключ '" << key << "' уже существует!" << endl;
            return;
        }
    }

    // Линейное пробирование по таблице
    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (index + i) % TABLE_SIZE; // переход к следующей позиции

        // Ячейка свободна или помечена как удалённая — сюда можно записать запись
        if (table[probe] == nullptr || table[probe]->isDelete) {
            table[probe] = new Entry(key, value);
            return;
        }
    }

    // В таблице нет подходящей позиции
    cout << "Таблица заполнена!\n";
}

// Поиск значения по ключу в хеш-таблице с открытой адресацией
string search(const string& key) {
    int index = djb2_hash(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (index + i) % TABLE_SIZE;

        // Пустая ячейка означает отсутствие нужного ключа
        if (table[probe] == nullptr) {
            return "Не найдено!\n";
        }

        // Ячейка содержит активную запись с нужным ключом
        if (!table[probe]->isDelete && table[probe]->key == key) {
            return table[probe]->data;
        }
    }

    // Полный проход без совпадений
    return "Не найдено!\n";
}

// Логическое удаление записи по ключу
void remove(const string& key) {
    int index = djb2_hash(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int probe = (index + i) % TABLE_SIZE;

        // Пустая ячейка — дальше ключ не встречается
        if (table[probe] == nullptr) {
            return;
        }

        // Найдена активная запись с искомым ключом
        if (!table[probe]->isDelete && table[probe]->key == key) {
            table[probe]->isDelete = true; // отметка о логическом удалении
            return;
        }
    }
}
