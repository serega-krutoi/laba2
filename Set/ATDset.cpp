#include <iostream>
#include <fstream>
#include <string>
#include "include/set.h"

using namespace std;

int main(int argc, char* argv[]) {
    string dataFilePath;
    string queryFilePath;

    // Парсим аргументы командной строки
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

    // 1. Читаем начальное множество из файла --file
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

    // 2. Обрабатываем запросы из файла --query
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
        // если встретится другая команда — можно игнорировать или ругаться
    }

    queryFile.close();
    return 0;
}
