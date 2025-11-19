#include "../include/TwoLinked.h"
#include <stdexcept>
#include <iostream>

using namespace std;

// Создание узла списка
TwoLinkedNode::TwoLinkedNode(string value)
    : data(value), pNext(nullptr), pPrevios(nullptr) {}

// Пустой список
listTwoLinked::listTwoLinked() : head(nullptr), tail(nullptr) {}

// Проверка пустоты
bool listTwoLinked::is_empty() {
    return head == nullptr;
}

// Поиск узла
TwoLinkedNode* listTwoLinked::find(string value) {
    TwoLinkedNode* p = head;
    while (p && p->data != value) {
        p = p->pNext;
    }
    return p;
}

// Вставка в конец
void listTwoLinked::push_back(string value) {
    TwoLinkedNode* p = new TwoLinkedNode(value);

    if (is_empty()) {
        head = tail = p;
        return;
    }

    tail->pNext = p;
    p->pPrevios = tail;
    tail = p;
}

// Вставка в начало
void listTwoLinked::push_forward(string value) {
    TwoLinkedNode* p = new TwoLinkedNode(value);

    if (is_empty()) {
        head = tail = p;
        return;
    }

    p->pNext = head;
    head->pPrevios = p;
    head = p;
}

// Вставка перед конкретным узлом
void listTwoLinked::push_beforeNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");

    TwoLinkedNode* currentNode = find(placedData);
    if (!currentNode) throw runtime_error("Нет такого значения");

    if (currentNode == head) {
        push_forward(newValue);
        return;
    }

    TwoLinkedNode* prev = currentNode->pPrevios;
    TwoLinkedNode* p = new TwoLinkedNode(newValue);

    p->pPrevios = prev;
    p->pNext = currentNode;
    prev->pNext = p;
    currentNode->pPrevios = p;
}

// Вставка после указанного узла
void listTwoLinked::push_afterNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");

    TwoLinkedNode* currentNode = find(placedData);
    if (!currentNode) throw runtime_error("Нет такого значения");

    if (currentNode == tail) {
        push_back(newValue);
        return;
    }

    TwoLinkedNode* next = currentNode->pNext;
    TwoLinkedNode* p = new TwoLinkedNode(newValue);

    p->pNext = next;
    p->pPrevios = currentNode;
    currentNode->pNext = p;
    next->pPrevios = p;
}

// Удаление узла в конце
void listTwoLinked::delete_back() {
    if (is_empty()) throw runtime_error("Список пуст");

    if (head == tail) {
        delete tail;
        head = tail = nullptr;
        return;
    }

    TwoLinkedNode* p = tail;
    tail = tail->pPrevios;
    tail->pNext = nullptr;
    delete p;
}

// Удаление узла в начале
void listTwoLinked::delete_forward() {
    if (is_empty()) throw runtime_error("Список пуст");

    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }

    TwoLinkedNode* p = head;
    head = head->pNext;
    head->pPrevios = nullptr;
    delete p;
}

// Удаление узла перед указанным
void listTwoLinked::delete_beforeNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");

    TwoLinkedNode* currentNode = find(value);
    if (!currentNode) throw runtime_error("Нет такого значения");

    if (currentNode == head) throw runtime_error("Перед данным узлом нет элемента");

    TwoLinkedNode* delNode = currentNode->pPrevios;

    if (delNode == head) {
        delete_forward();
        return;
    }

    TwoLinkedNode* prev = delNode->pPrevios;
    prev->pNext = currentNode;
    currentNode->pPrevios = prev;
    delete delNode;
}

// Удаление узла после указанного
void listTwoLinked::delete_afterNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");

    TwoLinkedNode* currentNode = find(value);
    if (!currentNode) throw runtime_error("Нет такого значения");

    if (!currentNode->pNext) throw runtime_error("После данного узла нет элемента");

    TwoLinkedNode* delNode = currentNode->pNext;
    TwoLinkedNode* next = delNode->pNext;

    currentNode->pNext = next;
    if (next) next->pPrevios = currentNode;
    else tail = currentNode;

    delete delNode;
}

// Удаление узла по значению
void listTwoLinked::delete_data(string value) {
    if (is_empty()) throw runtime_error("Список пуст");

    TwoLinkedNode* delNode = find(value);
    if (!delNode) throw runtime_error("Нет такого значения");

    if (delNode == head) {
        delete_forward();
        return;
    }

    if (delNode == tail) {
        delete_back();
        return;
    }

    TwoLinkedNode* prev = delNode->pPrevios;
    TwoLinkedNode* next = delNode->pNext;

    prev->pNext = next;
    next->pPrevios = prev;

    delete delNode;
}

// Вывод слева направо
void listTwoLinked::print_sequentially() {
    TwoLinkedNode* p = head;
    while (p) {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << endl;
}

// Вывод справа налево
void listTwoLinked::print_reverse() {
    TwoLinkedNode* p = tail;
    while (p) {
        cout << p->data << " ";
        p = p->pPrevios;
    }
    cout << endl;
}

// Полная очистка списка
void listTwoLinked::clear() {
    while (!is_empty()) {
        delete_forward();
    }
}

listTwoLinked::~listTwoLinked() {
    clear();
}

// Перенос узла в начало (для LRU)
void listTwoLinked::move_to_front(TwoLinkedNode* node) {
    if (!node || node == head) return;

    if (node == tail) {
        tail = tail->pPrevios;
        tail->pNext = nullptr;
    } else {
        node->pPrevios->pNext = node->pNext;
        node->pNext->pPrevios = node->pPrevios;
    }

    node->pPrevios = nullptr;
    node->pNext = head;
    head->pPrevios = node;
    head = node;
}
