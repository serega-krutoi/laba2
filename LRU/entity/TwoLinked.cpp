#include"../include/TwoLinked.h"
#include<stdexcept>
#include<iostream>

using namespace std;

TwoLinkedNode::TwoLinkedNode(string value) : data(value), pNext(nullptr), pPrevios(nullptr) {}

listTwoLinked::listTwoLinked() : head(nullptr), tail(nullptr) {}

bool listTwoLinked::is_empty() {
    return head == nullptr;
}

TwoLinkedNode* listTwoLinked::find(string value) {
    TwoLinkedNode* p = head;
    while (p && p->data != value) p = p->pNext;
    return p;
}

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

void listTwoLinked::push_beforeNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(placedData);
    if (!currentNode) throw runtime_error("Нет такого значения");

    if (currentNode == head) { 
        push_forward(newValue);
        return;
    }

    TwoLinkedNode* previosNode = currentNode->pPrevios;
    TwoLinkedNode* p = new TwoLinkedNode(newValue);
    p->pPrevios = previosNode;
    p->pNext = currentNode;
    previosNode->pNext = p;
    currentNode->pPrevios = p;
}

void listTwoLinked::push_afterNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(placedData);
    if (!currentNode) throw runtime_error("Нет такого значения");

    if (currentNode == tail) { 
        push_back(newValue);
        return;
    }

    TwoLinkedNode* nextNode = currentNode->pNext; 
    TwoLinkedNode* p = new TwoLinkedNode(newValue);
    p->pNext = nextNode;
    p->pPrevios = currentNode;
    currentNode->pNext = p;
    nextNode->pPrevios = p;
}

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

void listTwoLinked::delete_beforeNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(value);
    if (!currentNode) throw runtime_error("Нет такого значения");
    if (currentNode == head) throw runtime_error("Перед головой нет узла");

    TwoLinkedNode* deletingNode = currentNode->pPrevios; 
    if (deletingNode == head) { 
        delete_forward();
        return;
    }

    TwoLinkedNode* previosNode = deletingNode->pPrevios; 
    previosNode->pNext = currentNode;
    currentNode->pPrevios = previosNode;
    delete deletingNode;
}

void listTwoLinked::delete_afterNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(value);
    if (!currentNode) throw runtime_error("Нет такого значения");
    if (!currentNode->pNext) throw runtime_error("После указанного узла ничего нет");

    TwoLinkedNode* deletingNode = currentNode->pNext;
    TwoLinkedNode* nextNode = deletingNode->pNext; 

    currentNode->pNext = nextNode;
    if (nextNode) {
        nextNode->pPrevios = currentNode;
    } else {
        tail = currentNode; 
    }
    delete deletingNode;
}

void listTwoLinked::delete_data(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* deletingNode = find(value);
    if (!deletingNode) throw runtime_error("Нет такого значения");

    if (deletingNode == head) {
        delete_forward();
        return;
    }
    if (deletingNode == tail) {
        delete_back();
        return;
    }

    TwoLinkedNode* prevNode = deletingNode->pPrevios; 
    TwoLinkedNode* nextNode = deletingNode->pNext;    
    prevNode->pNext = nextNode;
    nextNode->pPrevios = prevNode;
    delete deletingNode;
}

void listTwoLinked::print_sequentially() {
    TwoLinkedNode* p = head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << endl;
}

void listTwoLinked::print_reverse() {
    TwoLinkedNode* p = tail;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->pPrevios;
    }
    cout << endl;
}

void listTwoLinked::clear() {
    while (!is_empty()) delete_forward();
}

listTwoLinked::~listTwoLinked() {
    clear();
}

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