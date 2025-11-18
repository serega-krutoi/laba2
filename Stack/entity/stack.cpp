#include"../include/stack.h"
#include<stdexcept>
#include<iostream>

using namespace std;

StackNode::StackNode(string v) : data(v), next(nullptr) {}

Stack::Stack() : head(nullptr), sz(0) {}

bool Stack::is_empty() { return head == nullptr; }

size_t Stack::size() { return sz; }

void Stack::push(string value) {
    StackNode* p = new StackNode(value);
    p->next = head;
    head = p;
    ++sz;
}

void Stack::pop() {
    if (is_empty()) throw runtime_error("Стек пуст");
    StackNode* p = head;
    head = head->next;
    delete p;
    --sz;
}

void Stack::print() {
    StackNode* p = head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
}

void Stack::clear() {
    while (!is_empty()) pop();
}

Stack::~Stack() { clear(); }