#include<iostream>
#include"include/kashLRU.h"

int main() {
    LRUCache cache(3); // кэш на 3 элемента

    cache.put("a", "1");
    cache.put("b", "2");
    cache.put("c", "3");

    cout << cache.get("a") << endl; // 1  (a становится самым свежим)
    cache.put("d", "4");            // кэш полон → выкидывается самый старый (b)

    cout << cache.get("b") << endl; // NOT_FOUND
    cout << cache.get("c") << endl; // 3
    cout << cache.get("d") << endl; // 4

    return 0;
}
