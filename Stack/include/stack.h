#include<stdexcept>
#include<iostream>
#pragma once

using namespace std;

struct StackNode {
    string data;
    StackNode* next;
    StackNode(string v);
};

struct Stack {
    StackNode* head;
    size_t sz;

    Stack();
    bool is_empty();
    size_t size();
    void push(string value);
    void pop();
    void print();
    void clear();
    ~Stack();
};