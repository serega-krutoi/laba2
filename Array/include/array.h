
#pragma once
#include <string>
#include <cstddef>
using namespace std;

struct Array {
    string* data;
    size_t size;
    size_t cap;
};

struct listArray {
    static Array create(size_t capacity);
    static void destroy(Array& arr);
    static void increase_capacity(Array& arr);
    static void test_capacity(Array& arr);
    static void push_back(Array& arr, string value);
    static void insert(Array& arr, size_t idx, string value);
    static string get(const Array& arr, size_t idx);
    static void erase(Array& arr, size_t idx);
    static void set(Array& arr, size_t idx, string value);
    static size_t length(const Array& arr);
    static string read(const Array& arr);
};
