#pragma once
#include<iostream>
#include<string>
#include"queue.h"

using namespace std;

struct NodeHoffQueue {
    char data;
    NodeHoffQueue* next;
    NodeHoffQueue* right;
    NodeHoffQueue* left;
    int priority;

    NodeHoffQueue(char value, int p) : data(value), next(nullptr), right(nullptr), left(nullptr), priority(p) {}
};

struct HoffQueue {
    NodeHoffQueue* head;
    HoffQueue() : head(nullptr) {}
    bool is_empty();
    void push_sorted(NodeHoffQueue* node);
    NodeHoffQueue* pop_min();
};

struct NodeHoffTree {
    char data;
    NodeHoffTree* left;
    NodeHoffTree* right;
    NodeHoffTree* parent;
    int priority;
    NodeHoffTree(char c, int value) : data(c), left(nullptr), right(nullptr), parent(nullptr), priority(value) {}
};

struct HoffTree {
    NodeHoffTree* root;
};

NodeHoffQueue* buildHuffman(HoffQueue& hoff);
void search(char c, Queue& queue);