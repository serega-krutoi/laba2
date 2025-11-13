#include<iostream>
#include<string>
#include"include/queue.h"

using namespace std;

HoffQueue...



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

HoffTree makeTree(Queue& queue) {
    NodeQueue* curr = queue.head;
    while (!queue.is_empty() && curr->next != nullptr) {
        NodeHoffTree* n = new NodeHoffTree('*', 0);
        n->left = new NodeHoffTree(curr->data, curr->priority);
        curr = curr->next;
        queue.dequeue();
        n->right = new NodeHoffTree(curr->data, curr->priority);
        curr = curr->next;
        queue.dequeue();
        n->priority = n->left->priority + n->right->priority;
    }
}

void search(char c, Queue& queue) {
    NodeQueue* curr = queue.head;
    bool found = false;
    
    while (curr != nullptr) {  
        if (curr->data == c) {
            curr->priority += 1;
            found = true;
            break;
        }
        curr = curr->next; 
    }
    
    if (!found) {
        queue.enqueue(c);
    }
}



int main() {

    Queue queue;

    string ser = "poor mister evas";
    for (char c : ser) {
        search(c, queue);
    }

    queue.sort_by_priority();



    queue.print();

    return 0;
}