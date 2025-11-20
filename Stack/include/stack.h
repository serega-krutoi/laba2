#include <stdexcept>
#include <iostream>
#pragma once

using namespace std;

struct Node;

struct StackNode {
    Node* data;  
    StackNode* next;
    StackNode(Node* v);
};

struct Stack {
    StackNode* head;
    size_t sz;

    Stack();
    bool is_empty();
    size_t size();
    void push(Node* value);
    void pop();
    Node* top();  
    void clear();
    ~Stack();
};