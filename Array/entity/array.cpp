#include "../include/array.h"
#include <iostream>
#include <sstream>
using namespace std;

Array listArray::create(size_t capacity) {
    Array arr;
    arr.size = 0;

    if (capacity > 256*256){
        throw length_error("Объём превысил максимум");
    }
    
    arr.cap = (capacity < 16) ? 16 : capacity;
    arr.data = new string[arr.cap];
    return arr;
}

void listArray::destroy(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.cap = 0;
}

void listArray::increase_capacity(Array& arr) {
    size_t new_cap = arr.cap + 1;
    
    if (new_cap > 256*256){
        throw length_error("Объём превысил максимум");
    }
    
    string* new_arr = new string[new_cap];
    
    for (size_t i = 0; i < arr.size; i++) {
        new_arr[i] = arr.data[i];
    }
    
    delete[] arr.data;
    arr.data = new_arr;
    arr.cap = new_cap;
}

void listArray::test_capacity(Array& arr) {
    if (arr.size >= arr.cap) {
        increase_capacity(arr);
    }
}

void listArray::push_back(Array& arr, string value) {
    if (!arr.data){
        return;
    }
    
    test_capacity(arr);
    arr.data[arr.size++] = value;
}

void listArray::insert(Array& arr, size_t idx, string value) {
    if (idx > arr.size) return;
    
    test_capacity(arr);
    
    for (size_t i = arr.size; i > idx; i--) {
        arr.data[i] = arr.data[i - 1];
    }
    
    arr.data[idx] = value;
    arr.size++;
}

string listArray::get(const Array& arr, size_t idx) {
    if (idx >= arr.size) throw out_of_range("Array_get: index out of range");
    return arr.data[idx];
}

void listArray::erase(Array& arr, size_t idx) {
    if (idx >= arr.size) return;
    
    for (size_t i = idx; i < arr.size - 1; i++) {
        arr.data[i] = arr.data[i + 1];
    }
    
    arr.size--;
}

void listArray::set(Array& arr, size_t idx, string value) {
    if (idx >= arr.size) return;
    arr.data[idx] = value;
}

size_t listArray::length(const Array& arr) {
    return arr.size;
}

string listArray::read(const Array& arr){
    stringstream ss;
    
    for (int i = 0; i != length(arr); i++){
        ss << " ";
        ss << get(arr, i);
    }
    return ss.str();
}