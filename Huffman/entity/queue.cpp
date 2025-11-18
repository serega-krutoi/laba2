#include"../include/queue.h"
#include<stdexcept>
#include<iostream>

using namespace std;


NodeQueue::NodeQueue(char value) : data(value), next(nullptr), priority(1) {}

Queue::Queue() : head(nullptr), tail(nullptr) {}

bool Queue::is_empty() {
    return head == nullptr;
}

void Queue::enqueue(char value) {
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
        cout << p->data << "-" << p->priority << " ";
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

void Queue::sort_by_priority() {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    do {
        swapped = false;
        NodeQueue* curr = head;
        NodeQueue* prev = nullptr;

        while (curr->next != nullptr) {
            NodeQueue* next = curr->next;

            if (curr->priority > next->priority) {
                swapped = true;

                if (prev == nullptr) {
                    head = next;
                } else {
                    prev->next = next;
                }

                curr->next = next->next;
                next->next = curr;

                prev = next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        tail = head;
        while (tail->next != nullptr) tail = tail->next;

    } while (swapped);
}

