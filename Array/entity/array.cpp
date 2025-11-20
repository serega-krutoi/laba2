#include "../include/array.h"
#include <iostream>
#include <sstream>
using namespace std;

// Создание динамического массива строк заданной ёмкости
Array listArray::create(size_t capacity) {
    Array arr;
    arr.size = 0;

    // Защита от слишком большого запрашиваемого размера
    if (capacity > 256*256){
        throw length_error("Объём превысил максимум");
    }
    
    // Минимальная ёмкость 16, даже если передали меньше
    arr.cap = (capacity < 16) ? 16 : capacity;
    // Выделение памяти под массив строк
    arr.data = new string[arr.cap];
    return arr;
}

// Освобождение памяти, занимаемой массивом, и обнуление полей
void listArray::destroy(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.cap = 0;
}

// Увеличение ёмкости массива на один элемент
void listArray::increase_capacity(Array& arr) {
    size_t new_cap = arr.cap + 1;
    
    // Проверка на превышение максимального ограничения
    if (new_cap > 256*256){
        throw length_error("Объём превысил максимум");
    }
    
    // Выделение нового буфера увеличенного размера
    string* new_arr = new string[new_cap];
    
    // Копирование существующих элементов в новый массив
    for (size_t i = 0; i < arr.size; i++) {
        new_arr[i] = arr.data[i];
    }
    
    // Освобждение старого буфера
    delete[] arr.data;
    arr.data = new_arr;
    arr.cap = new_cap;
}

// Проверка, достаточно ли ёмкости, и её увеличение при необходимости
void listArray::test_capacity(Array& arr) {
    if (arr.size >= arr.cap) {
        increase_capacity(arr);
    }
}

// Добавление элемента в конец массива
void listArray::push_back(Array& arr, string value) {
    // Если массив не был создан или уже уничтожен
    if (!arr.data){
        return;
    }
    
    // При необходимости увеличение ёмкости
    test_capacity(arr);
    // запись значения в конец
    arr.data[arr.size++] = value;
}

// Вставка элемента по индексу с сдвигом хвоста вправо
void listArray::insert(Array& arr, size_t idx, string value) {
    // Если индекс больше текущего размера, вставка невозможна
    if (idx > arr.size) return;
    
    test_capacity(arr);
    
    // Сдвиг элементы вправо, начиная с конца, чтобы освободить место
    for (size_t i = arr.size; i > idx; i--) {
        arr.data[i] = arr.data[i - 1];
    }
    
    // Запись новое значение на нужную позицию
    arr.data[idx] = value;
    arr.size++;
}

// Получение элемента по индексу с проверкой границ
string listArray::get(const Array& arr, size_t idx) {
    if (idx >= arr.size) throw out_of_range("Array_get: index out of range");
    return arr.data[idx];
}

// Удаление элемента по индексу со сдвигом оставшихся элементов влево
void listArray::erase(Array& arr, size_t idx) {
    if (idx >= arr.size) return;
    
    for (size_t i = idx; i < arr.size - 1; i++) {
        arr.data[i] = arr.data[i + 1];
    }
    
    arr.size--;
}

// Изменение значения по индексу без изменения размера массива
void listArray::set(Array& arr, size_t idx, string value) {
    if (idx >= arr.size) return;
    arr.data[idx] = value;
}

// Получение текущего количества элементов
size_t listArray::length(const Array& arr) {
    return arr.size;
}

// Формирование строки из всех элементов массива через пробел
string listArray::read(const Array& arr){
    stringstream ss;
    
    for (int i = 0; i != length(arr); i++){
        ss << " ";
        ss << get(arr, i);
    }
    return ss.str();
}
