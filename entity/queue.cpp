#include"../include/queue.h"
#include<stdexcept>
#include<iostream>

using namespace std;


NodeQueue::NodeQueue(string value) : data(value), next(nullptr) {}

Queue::Queue() : head(nullptr), tail(nullptr) {}

bool Queue::is_empty() {
    return head == nullptr;
}

void Queue::enqueue(string value) {
    NodeQueue* p = new NodeQueue(value);
    
    if (is_empty()) {
        head = tail = p;
        return;
    }

    tail->next = p;
    tail = p;
}

void Queue::dequeue() {
    if (is_empty()) throw runtime_error("Очередь пуста");

    NodeQueue* p = head;
    head = head->next;
    delete p;

    if (head == nullptr) tail = nullptr;
}

void Queue::print() {
    NodeQueue* p = head;

    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void Queue::clear() {
    while (!is_empty()) dequeue();
}

Queue::~Queue() {
    clear();
}