#include <iostream>
#include "include/set.h"

using namespace std;

// Вариант 2
//g++ main.cpp entity/set.cpp -o m

int main() {
    // Исходный набор
    Set S;
    S.insert(5);
    S.insert(8);
    S.insert(1);
    S.insert(14);
    S.insert(7);

    // 1. Копирование всех чисел из набора S в массив arr
    int n = S.size();
    int* arr = new int[n];
    int pos = 0;

    // Проход по всем цепочкам в таблице
    for (int i = 0; i < Set::TABLE_SIZE; ++i) {
        SetNode* p = S.table[i];
        while (p != nullptr) {
            arr[pos++] = p->key;
            p = p->next;
        }
    }

    // Сумма всех чисел
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += arr[i];

    // Нужна половина суммы (или ближе всего к ней)
    int target = sum / 2;

    // 2. dp[j] — можно ли набрать сумму j
    bool* dp = new bool[target + 1];
    for (int j = 0; j <= target; ++j) dp[j] = false;
    dp[0] = true;

    // заполнение массива dp
    for (int i = 0; i < n; ++i) {
        int x = arr[i];
        for (int j = target; j >= x; --j) {
            if (dp[j - x]) dp[j] = true;
        }
    }

    // 3. Поиск наибольшей суммы, не больше target
    int best = 0;
    for (int j = target; j >= 0; --j) {
        if (dp[j]) {
            best = j;
            break;
        }
    }

    // 4. Восстановление двух подмножеств A и B
    Set A, B;
    int curr = best;
    int sumA = 0, sumB = 0;

    // Идём по массиву с конца и решаем, куда идёт каждый x
    for (int i = n - 1; i >= 0; --i) {
        int x = arr[i];

        if (curr >= x) {
            // Проверка: достижима ли сумма curr - x при использовании первых i чисел
            bool* newdp = new bool[target + 1];
            for (int j = 0; j <= target; ++j) newdp[j] = false;
            newdp[0] = true;

            for (int k = 0; k < i; ++k) {
                int y = arr[k];
                for (int j = target; j >= y; --j) {
                    if (newdp[j - y]) newdp[j] = true;
                }
            }

            // Если curr - x достижимо, x идёт в A
            if (newdp[curr - x]) {
                A.insert(x);
                sumA += x;
                curr -= x;
            } else {
                // Иначе x идёт в B
                B.insert(x);
                sumB += x;
            }

            delete[] newdp;
        } else {
            // x не подходит под текущую curr, сразу в B
            B.insert(x);
            sumB += x;
        }
    }

    // Вывод результата
    cout << "Множество S = ";
    S.print(); cout << "\n";

    cout << "Подмножество A = ";
    A.print(); cout << "\n";

    cout << "Подмножество B = ";
    B.print(); cout << "\n";

    cout << "Сумма A = " << sumA << endl;
    cout << "Сумма B = " << sumB << endl;

    int diff = sumA - sumB;
    if (diff < 0) diff = -diff;
    cout << "Разница = " << diff << endl;

    delete[] dp;
    delete[] arr;

    return 0;
}
