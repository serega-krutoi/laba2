#pragma once
#include <iostream>

using namespace std;

struct Set {
    int* data;     // массив значений
    int capacity;  // максимум элементов
    int count;     // текущий размер множества

    Set(int cap = 100);
    bool is_empty();
    bool contains(int value);
    bool insert(int value);
    bool remove(int value);
    int size();
    void print();
    ~Set();
};
