#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "include/kashLRU.h"

using namespace std;

// Печать списка от head к tail
void printCacheState(listTwoLinked& lst) {
    TwoLinkedNode* p = lst.head;
    bool first = true;
    while (p != nullptr) {
        if (!first) cout << ", ";
        cout << p->data << " -> " << "(value in hash not printed here)";
        p = p->pNext;
        first = false;
    }
    cout << "\n";
}

// Печать кэша (ключ → значение)
void printCachePairs(listTwoLinked& lst, LRUHashNode* table[]) {
    TwoLinkedNode* p = lst.head;
    bool first = true;
    while (p != nullptr) {
        if (!first) cout << ", ";
        LRUHashNode* h = lru_hash_find(table, p->data);
        cout << p->data << " -> " << h->value;
        first = false;
        p = p->pNext;
    }
    cout << "\n";
}

int main() {

    int cap, Q;
    cin >> cap >> Q;

    LRUCache cache(cap);

    vector<string> commands;
    commands.reserve(Q);

    string cmd, x, y;

    for (int i = 0; i < Q; ++i) {
        string line;
        cin >> cmd;

        if (cmd == "SET") {
            cin >> x >> y;
            commands.push_back("SET " + x + " " + y);
        }
        else if (cmd == "GET") {
            cin >> x;
            commands.push_back("GET " + x);
        }
    }

    cout << "Cache Size = " << cap << "\n\n";

    for (string& line : commands) {
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "SET") {
            ss >> x >> y;

            cout << "SET " << x << " " << y << " : ";

            cache.put(x, y);

            printCachePairs(cache.order, cache.table);
        }
        else if (cmd == "GET") {
            ss >> x;

            string res = cache.get(x);

            cout << "GET " << x << " : ";

            if (res == "NOT_FOUND")
                cout << -1 << " ";
            else
                cout << res << " ";

            cout << "(";
            printCachePairs(cache.order, cache.table);
            cout << ")\n";
        }
    }

    return 0;
}

