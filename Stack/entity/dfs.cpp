#include "../include/dfs.h"
#include "../include/stack.h"
#include <iostream>
using namespace std;

void dfs(Node* root) {
    if (root == nullptr) return;

    Stack stack;  // Стек для указателей на Node
    Node* current = root;

    // Центрированный обход: левый подузел, корень, правый подузел
    while (current != nullptr || !stack.is_empty()) {

        // Движение к левому подузлу, узлы по пути кладутся в стек
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        // Снятие верхушки стека
        current = stack.top();
        stack.pop();

        // Обработка узла в центре
        cout << current->data << " ";

        // Переход к правому подузлу
        current = current->right;
    }
}