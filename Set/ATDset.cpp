#include <iostream>
#include <fstream>
#include <string>
#include "include/set.h"

using namespace std;

//g++ ATDset.cpp entity/set.cpp -o atd

int main(int argc, char* argv[]) {
    string dataFilePath;
    string queryFilePath;

    // Разбор аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            dataFilePath = argv[++i];     // путь к файлу с набором
        } else if (arg == "--query" && i + 1 < argc) {
            queryFilePath = argv[++i];    // путь к файлу с запросами
        }
    }

    // Проверка, что оба пути заданы
    if (dataFilePath.empty() || queryFilePath.empty()) {
        cout << "Usage: " << argv[0]
             << " --file <data_file> --query <query_file>\n";
        return 1;
    }

    Set set;

    // 1. Чтение исходного набора из файла
    ifstream dataFile(dataFilePath);
    if (!dataFile.is_open()) {
        cerr << "Cannot open data file: " << dataFilePath << endl;
        return 1;
    }

    int x;
    // Все числа из файла идут в набор, повторы не влияют
    while (dataFile >> x) {
        set.insert(x);
    }
    dataFile.close();

    // 2. Обработка запросов из второго файла
    ifstream queryFile(queryFilePath);
    if (!queryFile.is_open()) {
        cerr << "Cannot open query file: " << queryFilePath << endl;
        return 1;
    }

    string cmd;
    // Каждый ряд: команда и число
    while (queryFile >> cmd >> x) {
        if (cmd == "SETADD") {
            set.insert(x);        // добавление ключа
        } else if (cmd == "SETDEL") {
            set.erase(x);         // удаление ключа
        } else if (cmd == "SET_AT") {
            // Проверка наличия ключа
            if (set.contains(x)) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    queryFile.close();

    // 3. Запись обновлённого набора обратно в исходный файл
    ofstream out(dataFilePath);
    if (!out.is_open()) {
        cerr << "Cannot open file for writing: " << dataFilePath << endl;
        return 1;
    }

    // Вывод всех чисел из хеш-таблицы в файл
    for (int i = 0; i < Set::TABLE_SIZE; ++i) {
        SetNode* p = set.table[i];
        while (p != nullptr) {
            out << p->key << " ";
            p = p->next;
        }
    }
    out.close();

    return 0;
}
