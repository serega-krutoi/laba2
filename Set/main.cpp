#include <iostream>
#include <vector>
#include "include/set.h"

using namespace std;

// Вариант 2

int main() {
    // Исходное множество
    Set S;
    S.insert(5);
    S.insert(8);
    S.insert(1);
    S.insert(14);
    S.insert(7);

    // 1. Соберём элементы множества S во вспомогательный массив arr
    vector<int> arr;
    for (int i = 0; i < Set::TABLE_SIZE; ++i) {
        SetNode* p = S.table[i];   // пробегаем по цепочкам
        while (p != nullptr) {
            arr.push_back(p->key);
            p = p->next;
        }
    }

    int n = (int)arr.size();
    int sum = 0;
    for (int x : arr) sum += x;

    int target = sum / 2;

    // 2. Динамическое программирование: dp[j] — можно ли набрать сумму j
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int x : arr) {
        for (int j = target; j >= x; j--) {
            if (dp[j - x]) dp[j] = true;
        }
    }

    // 3. Находим максимальную достижимую сумму ≤ target
    int best = 0;
    for (int j = target; j >= 0; j--) {
        if (dp[j]) {
            best = j;
            break;
        }
    }

    // 4. Восстанавливаем подмножества A и B
    Set A, B;
    int curr = best;
    int sumA = 0, sumB = 0;

    for (int i = n - 1; i >= 0; i--) {
        if (curr >= arr[i]) {
            // проверяем, можно ли набрать curr - arr[i] из первых i элементов
            vector<bool> newdp(target + 1, false);
            newdp[0] = true;
            for (int k = 0; k < i; k++) {
                for (int j = target; j >= arr[k]; j--) {
                    if (newdp[j - arr[k]]) newdp[j] = true;
                }
            }

            if (newdp[curr - arr[i]]) {
                A.insert(arr[i]);
                sumA += arr[i];
                curr -= arr[i];
            } else {
                B.insert(arr[i]);
                sumB += arr[i];
            }
        } else {
            B.insert(arr[i]);
            sumB += arr[i];
        }
    }

    // 5. Вывод результата
    cout << "Множество S = ";
    S.print(); cout << "\n";

    cout << "Подмножество A = ";
    A.print(); cout << "\n";

    cout << "Подмножество B = ";
    B.print(); cout << "\n";

    cout << "Сумма A = " << sumA << endl;
    cout << "Сумма B = " << sumB << endl;
    cout << "Разница = " << abs(sumA - sumB) << endl;

    return 0;
}
