#include <iostream>
#include <fstream>
#include <string>
#include "include/set.h"

using namespace std;

int main(int argc, char* argv[]) {
    string dataFilePath;
    string queryFilePath;

    // Парс аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            dataFilePath = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            queryFilePath = argv[++i];
        }
    }

    if (dataFilePath.empty() || queryFilePath.empty()) {
        cout << "Usage: " << argv[0]
             << " --file <data_file> --query <query_file>\n";
        return 1;
    }

    Set set;

    // 1. Чтение начального множества из файла --file
    ifstream dataFile(dataFilePath);
    if (!dataFile.is_open()) {
        cerr << "Cannot open data file: " << dataFilePath << endl;
        return 1;
    }

    int x;
    while (dataFile >> x) {
        set.insert(x); // повторы автоматически игнорируются
    }
    dataFile.close();

    // 2. Обработка запроса из файла --query
    ifstream queryFile(queryFilePath);
    if (!queryFile.is_open()) {
        cerr << "Cannot open query file: " << queryFilePath << endl;
        return 1;
    }

    string cmd;
    while (queryFile >> cmd >> x) {
        if (cmd == "SETADD") {
            set.insert(x);
        } else if (cmd == "SETDEL") {
            set.erase(x);
        } else if (cmd == "SET_AT") {
            if (set.contains(x)) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    queryFile.close();

    // 3. Запись обновленного множества обратно в файл data.txt
    ofstream out(dataFilePath);
    if (!out.is_open()) {
        cerr << "Cannot open file for writing: " << dataFilePath << endl;
        return 1;
    }

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
