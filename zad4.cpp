#include <iostream>
#include <string>
#include <sstream>
#include "include/array.h"

using namespace std;

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
    getline(cin, line);
    while (line.size() == 0) getline(cin, line);

    Array arr = listArray::create(16);
    {
        stringstream ss(line);
        string token;
        while (ss >> token) listArray::push_back(arr, token);
    }

    // 2) Читаем целевую сумму
    cout << "Введите целевое значение суммы:\n";
    long long target = 0;
    cin >> target;

    const size_t n = listArray::length(arr);

    // 3) Перегоняем строки -> числа в сырой массив (без vector)
    long long* a = nullptr;
    if (n > 0) a = new long long[n];
    for (size_t i = 0; i < n; ++i) {
        a[i] = stoll(listArray::get(arr, i));
    }

    // 4) Перебор всех подмассивов O(n^2) без vector
    bool found = false;
    for (size_t l = 0; l < n; ++l) {
        long long sum = 0;
        for (size_t r = l; r < n; ++r) {
            sum += a[r];
            if (sum == target) {
                if (!found) {
                    cout << "Подмассивы:\n";
                    found = true;
                }
                print_subarray(arr, (int)l, (int)r);
            }
        }
    }

    if (!found) {
        cout << "Подмассивов с суммой " << target << " не найдено.\n";
    }

    delete[] a;
    listArray::destroy(arr);
    return 0;
}
