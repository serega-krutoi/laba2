#include<stdexcept>
#include<iostream>
#pragma once

using namespace std;

struct NodeQueue {
    string data;
    NodeQueue* next;
    NodeQueue(string value);
};

struct Queue {
    NodeQueue* head;
    NodeQueue* tail;

    Queue();
    bool is_empty();
    void enqueue(string value);
    void dequeue();
    void print();
    void clear();
    ~Queue();
};