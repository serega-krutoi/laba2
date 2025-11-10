#include<stdexcept>
#include<iostream>
#include<sstream>
#pragma once

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int k);
};

struct NodePtrQueue {
    Node* data;          
    NodePtrQueue* next;

    NodePtrQueue(Node* value);
};

struct QueueNodePtr {
    NodePtrQueue* head;
    NodePtrQueue* tail;

    QueueNodePtr();
    bool is_empty();
    void enqueue(Node* value);
    Node* dequeue();
    void clear();
    ~QueueNodePtr();
};

struct AVLtree {
    Node* root;
    AVLtree();
    int getHeight(Node* node);
    int getBalance(Node* node);
    void updateHeight(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    Node* insert(Node* root, int value);
    void insert(int value);
    Node* find_max(Node* node);
    Node* del(Node* node, int value); 
    void del(int value);
    void find(int value);
    void printPreOrder(Node* root);
    void printPreOrder();
    void printInOrder(Node* root);
    void printInOrder();
    void printPostOrder(Node* root);
    void printPostOrder();
    void printLevelOrder(Node* root);
    void printLevelOrder();
    void printTreeWithHeights(Node* node, const string& prefix = "", bool isLeft = true);
    void printTree();

    void saveToFile(ofstream& file, Node* node);
    void saveToFile(ofstream& file);

    void saveValues(std::ostream& out, Node* node);
    void saveValues(std::ostream& out);
};