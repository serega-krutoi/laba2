#include "../include/stack.h"
#include "../include/dfs.h"  
#include <stdexcept>
#include <iostream>

using namespace std;

// Конструктор узла стека, инициализирует данные и указатель на следующий элемент
StackNode::StackNode(Node* v) : data(v), next(nullptr) {}

// Конструктор стека, инициализирует вершину как пустой указатель и размер как 0
Stack::Stack() : head(nullptr), sz(0) {}

// Проверка, является ли стек пустым
bool Stack::is_empty() { return head == nullptr; }

// Получение текущего размера стека
size_t Stack::size() { return sz; }

// Добавление элемента в вершину стека
void Stack::push(Node* value) {
    StackNode* p = new StackNode(value);
    p->next = head;
    head = p;
    ++sz;
}

// Удаление элемента из вершины стека
void Stack::pop() {
    if (is_empty()) throw runtime_error("Стек пуст");
    StackNode* p = head;
    head = head->next;
    delete p;
    --sz;
}

// Получение верхнего элемента стека
Node* Stack::top() {
    if (is_empty()) throw runtime_error("Стек пуст");
    return head->data;
}

// Очистка всего стека
void Stack::clear() {
    while (!is_empty()) pop();
}

// Деструктор стека - автоматически очищает память при уничтожении объекта
Stack::~Stack() { clear(); }