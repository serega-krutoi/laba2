#include "../include/array.h"
#include <iostream>
#include <sstream>
using namespace std;

// Создание нового массива с указанной начальной емкостью
Array listArray::create(size_t capacity) {
    Array arr;
    arr.size = 0;

    // Проверка, что запрошенная емкость не превышает максимально допустимую
    if (capacity > 256*256){
        throw length_error("Объём превысил максимум");
    }
    
    // Установка емкости: минимум 16 элементов, либо запрошенное значение
    arr.cap = (capacity < 16) ? 16 : capacity;
    
    // Выделение памяти под массив строк
    arr.data = new string[arr.cap];
    return arr;
}

// Уничтожение массива и освобождение занимаемой памяти
void listArray::destroy(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.cap = 0;
}

// Увеличение емкости массива на один элемент
void listArray::increase_capacity(Array& arr) {
    size_t new_cap = arr.cap + 1;
    
    // Проверка новой емкости на превышение максимального размера
    if (new_cap > 256*256){
        throw length_error("Объём превысил максимум");
    }
    
    // Создание нового массива с увеличенной емкостью
    string* new_arr = new string[new_cap];
    
    // Копирование всех существующих элементов в новый массив
    for (size_t i = 0; i < arr.size; i++) {
        new_arr[i] = arr.data[i];
    }
    
    // Освобождение памяти старого массива и обновление указателя
    delete[] arr.data;
    arr.data = new_arr;
    arr.cap = new_cap;
}

// Проверка необходимости увеличения емкости массива
void listArray::test_capacity(Array& arr) {
    if (arr.size >= arr.cap) {
        increase_capacity(arr);
    }
}

// Добавление элемента в конец массива
void listArray::push_back(Array& arr, string value) {
    // Проверка, что массив был корректно создан
    if (!arr.data){
        return;
    }
    
    // Проверка и увеличение емкости при необходимости
    test_capacity(arr);
    
    // Добавление элемента и увеличение счетчика размера
    arr.data[arr.size++] = value;
}

// Вставка элемента в произвольную позицию массива
void listArray::insert(Array& arr, size_t idx, string value) {
    // Проверка корректности индекса для вставки
    if (idx > arr.size) return;
    
    // Проверка и увеличение емкости при необходимости
    test_capacity(arr);
    
    // Сдвиг элементов вправо для освобождения места под новый элемент
    for (size_t i = arr.size; i > idx; i--) {
        arr.data[i] = arr.data[i - 1];
    }
    
    // Вставка нового элемента и увеличение размера массива
    arr.data[idx] = value;
    arr.size++;
}

// Получение элемента массива по индексу
string listArray::get(const Array& arr, size_t idx) {
    // Проверка выхода индекса за границы массива
    if (idx >= arr.size) throw out_of_range("Array_get: index out of range");
    return arr.data[idx];
}

// Удаление элемента из массива по индексу
void listArray::erase(Array& arr, size_t idx) {
    // Проверка корректности индекса для удаления
    if (idx >= arr.size) return;
    
    // Сдвиг элементов влево для заполнения образовавшейся пустоты
    for (size_t i = idx; i < arr.size - 1; i++) {
        arr.data[i] = arr.data[i + 1];
    }
    
    // Уменьшение размера массива
    arr.size--;
}

// Изменение значения элемента массива по индексу
void listArray::set(Array& arr, size_t idx, string value) {
    // Проверка корректности индекса для изменения
    if (idx >= arr.size) return;
    arr.data[idx] = value;
}

// Получение текущего размера массива (количество элементов)
size_t listArray::length(const Array& arr) {
    return arr.size;
}

// Чтение всех элементов массива в виде строки с разделителями
string listArray::read(const Array& arr){
    stringstream ss;
    
    // Проход по всем элементам массива и добавление их в строковый поток
    for (int i = 0; i != length(arr); i++){
        ss << " ";
        ss << get(arr, i);
    }
    return ss.str();
}