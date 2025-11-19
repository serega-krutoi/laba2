#include <iostream>
#include <string>
#include "include/kashLRU.h"

using namespace std;

//g++ main.cpp entity/kashLRU.cpp entity/LRUHashTable.cpp entity/TwoLinked.cpp -o m

// Задание 7: LRU-кэш, вариант 1
// Формат ввода:
// cap Q
// далее Q строк:
//   SET x y
//   GET x
// Вывод: значения GET через пробел, вместо отсутствующих — -1.

int main() {

    int cap, Q;
    cin >> cap >> Q;

    LRUCache cache(cap);

    string cmd, x, y;
    bool firstOutput = true;

    for (int i = 0; i < Q; ++i) {
        cin >> cmd;

        if (cmd == "SET") {
            cin >> x >> y;
            cache.put(x, y);
        }
        else if (cmd == "GET") {
            cin >> x;
            string res = cache.get(x);

            if (!firstOutput) cout << " ";
            firstOutput = false;

            if (res == "NOT_FOUND")
                cout << -1;
            else
                cout << res;
        }
    }

    cout << endl;
    return 0;
}
