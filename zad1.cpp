#include <iostream>
#include <string>
#include "include/stack.h" 
using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;

    Node(string val) : data(val), left(nullptr), right(nullptr) {}
};

void dfs(Node* root) {
    if (root == nullptr) return;

    Stack st;                     // твой стек
    st.push(root->data);          // начнем с корня
    StackNode* ptr = st.head;     // для поиска узла по имени

    // Чтобы соответствовать стеку узлов, создадим вспомогательный стек указателей
    StackNode* temp = nullptr;

    // Поскольку твой стек хранит только string, сделаем сопоставление вручную
    // Здесь вместо хранения указателей будем просто использовать логику обхода
    // Реализуем DFS "вручную" для дерева
    Stack nodeStack;
    nodeStack.push(root->data); // поместим значение корня

    // Вспомогательный стек для реальных указателей узлов
    struct NodeStack {
        Node* node;
        NodeStack* next;
        NodeStack(Node* n) : node(n), next(nullptr) {}
    };

    // Реализация собственного стека для Node*
    NodeStack* top = new NodeStack(root);

    while (top != nullptr) {
        Node* current = top->node;

        // "Pop" — удалить верхний элемент
        NodeStack* temp = top;
        top = top->next;
        delete temp;

        // Обработка узла
        cout << current->data << " ";

        // В стек сначала добавляем правый, потом левый,
        // чтобы левый обрабатывался первым (LIFO)
        if (current->right) {
            NodeStack* newNode = new NodeStack(current->right);
            newNode->next = top;
            top = newNode;
        }
        if (current->left) {
            NodeStack* newNode = new NodeStack(current->left);
            newNode->next = top;
            top = newNode;
        }
    }
}

int main() {
    /*
            A
           / \
          B   C
         / \   \
        D   E   F
    */

    Node* root = new Node("A");
    root->left = new Node("B");
    root->right = new Node("C");
    root->left->left = new Node("D");
    root->left->right = new Node("E");
    root->right->right = new Node("F");

    cout << "Обход дерева в глубину (DFS) с использованием стека:\n";
    dfs(root);
    cout << endl;

    return 0;
}
