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

    // 1. Соберём элементы во вспомогательный массив
    vector<int> arr;
    for (int i = 0; i < S.size(); i++)
        arr.push_back(S.data[i]);

    int n = arr.size();
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

    // 4. Восстанавливаем подмножество A
    Set A, B;
    A.capacity = B.capacity = 100;

    int curr = best;
    for (int i = n - 1; i >= 0; i--) {
        if (curr >= arr[i]) {
            // проверяем, использован ли arr[i] в сумме
            vector<bool> newdp(target + 1, false);
            newdp[0] = true;
            for (int k = 0; k < i; k++)
                for (int j = target; j >= arr[k]; j--)
                    if (newdp[j - arr[k]]) newdp[j] = true;

            if (newdp[curr - arr[i]]) {
                A.insert(arr[i]);
                curr -= arr[i];
            } else {
                B.insert(arr[i]);
            }
        } else {
            B.insert(arr[i]);
        }
    }

    // 5. Вывод результата
    cout << "Множество S = ";
    S.print(); cout << "\n";

    cout << "Подмножество A = ";
    A.print(); cout << "\n";

    cout << "Подмножество B = ";
    B.print(); cout << "\n";

    int sumA = 0, sumB = 0;
    for (int i = 0; i < A.size(); i++) sumA += A.data[i];
    for (int i = 0; i < B.size(); i++) sumB += B.data[i];

    cout << "Сумма A = " << sumA << endl;
    cout << "Сумма B = " << sumB << endl;
    cout << "Разница = " << abs(sumA - sumB) << endl;

    return 0;
}
