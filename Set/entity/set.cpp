#include "../include/set.h"

Set::Set(int cap) {
    capacity = cap;
    data = new int[capacity];
    count = 0;
}

bool Set::is_empty() {
    return count == 0;
}

bool Set::contains(int value) {
    for (int i = 0; i < count; i++) {
        if (data[i] == value) return true;
    }
    return false;
}

bool Set::insert(int value) {
    if (contains(value)) return false;      // уже есть
    if (count >= capacity) return false;    // нет места

    data[count] = value;
    count++;
    return true;
}

bool Set::remove(int value) {
    for (int i = 0; i < count; i++) {
        if (data[i] == value) {
            data[i] = data[count - 1]; // затираем последним
            count--;
            return true;
        }
    }
    return false;
}

int Set::size() {
    return count;
}

void Set::print() {
    for (int i = 0; i < count; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

Set::~Set() {
    delete[] data;
}
