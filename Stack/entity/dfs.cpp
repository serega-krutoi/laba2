#include "../include/dfs.h"
#include <iostream>
using namespace std;

void dfs(Node* root) {
    if (root == nullptr) return;

    // Внутренняя структура: простой стек для указателей на узлы
    struct NodeStack {
        Node* node;
        NodeStack* next;
        NodeStack(Node* n) : node(n), next(nullptr) {}
    };

    NodeStack* top = nullptr;   // вершина стека
    Node* current = root;       // указатель на текущий узел

    // Центрированный обход: левый подузел, корень, правый подузел
    while (current != nullptr || top != nullptr) {

        // Движение к левому подузлу, узлы по пути кладутся в стек
        while (current != nullptr) {
            NodeStack* newNode = new NodeStack(current);
            newNode->next = top;
            top = newNode;

            current = current->left;
        }

        // Снятие верхушки стека
        NodeStack* temp = top;
        top = top->next;
        current = temp->node;
        delete temp;

        // Обработка узла в центре
        cout << current->data << " ";

        // Переход к правому подузлу
        current = current->right;
    }
}
