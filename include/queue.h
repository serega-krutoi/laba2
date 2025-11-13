#include<stdexcept>
#include<iostream>
#pragma once

using namespace std;

struct NodeQueue {
    char data;
    NodeQueue* next;
    NodeQueue(char value);
    int priority;
};

struct Queue {
    NodeQueue* head;
    NodeQueue* tail;

    Queue();
    bool is_empty();
    void enqueue(char value);
    void dequeue();
    void print();
    void clear();
    void sort_by_priority();
    ~Queue();
};