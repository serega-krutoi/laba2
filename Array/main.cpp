#include <iostream>
#include <string>
#include <sstream>
#include "include/array.h"

using namespace std;

// Вариант 2

//g++ main.cpp entity/array.cpp -o m 

static void print_subarray(const Array& arr, int l, int r) {
    cout << "[";
    for (int i = l; i <= r; ++i) {
        cout << listArray::get(arr, (size_t)i);
        if (i != r) cout << ", ";
    }
    cout << "]\n";
}

int main() {

    cout << "Введите элементы массива через пробел и нажмите Enter:\n";
    string line;
    // строку с элементами массива
    getline(cin, line);
    // Если первая попытка дала пустую строку, повторяем ввод
    while (line.size() == 0) getline(cin, line);

    // динамический массив строк с начальной ёмкостью 16
    Array arr = listArray::create(16);
    {
        // Разбираем введённую строку на подстроки по пробелам
        stringstream ss(line);
        string token;
        while (ss >> token) listArray::push_back(arr, token);
    }

    // Чтение целевой суммы, которую должны давать подмассивы
    cout << "Введите целевое значение суммы:\n";
    long long target = 0;
    cin >> target;

    const size_t n = listArray::length(arr);

    // Перегон элементы из строк в числовой массив
    long long* a = nullptr;
    if (n > 0) a = new long long[n];
    for (size_t i = 0; i < n; ++i) {
        a[i] = stoll(listArray::get(arr, i));
    }

    // Перебор всех подмассивов за O(n^2) без использования vector
    bool found = false;
    for (size_t l = 0; l < n; ++l) {
        long long sum = 0;
        for (size_t r = l; r < n; ++r) {
            sum += a[r]; // накапливаем сумму текущего подмассива [l..r]
            if (sum == target) {
                if (!found) {
                    cout << "Подмассивы:\n";
                    found = true;
                }
                // Выводим подмассив, который даёт нужную сумму
                print_subarray(arr, (int)l, (int)r);
            }
        }
    }

    // Если ни один подмассив не дал целевую сумму
    if (!found) {
        cout << "Подмассивов с суммой " << target << " не найдено.\n";
    }

    // Освобождаем память
    delete[] a;
    listArray::destroy(arr);
    return 0;
}
