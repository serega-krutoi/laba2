#include"../include/dfs.h"
#include"../include/stack.h"

void dfs(Node* root) {
    if (root == nullptr) return;

    Stack st;                    
    st.push(root->data);         
    StackNode* ptr = st.head;     // для поиска узла по имени

    // вспомогательный стек указателей
    StackNode* temp = nullptr;

    // сопоставление
    Stack nodeStack;
    nodeStack.push(root->data); //значение корня

    // Вспомогательный стек для реальных указателей узлов
    struct NodeStack {
        Node* node;
        NodeStack* next;
        NodeStack(Node* n) : node(n), next(nullptr) {}
    };

    // Реализация стека для Node*
    NodeStack* top = new NodeStack(root);

    while (top != nullptr) {
        Node* current = top->node;

        // удалить верхний элемент
        NodeStack* temp = top;
        top = top->next;
        delete temp;

        // Обработка узла
        cout << current->data << " ";

        // В стек сначала добавляется правый, потом левый,
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