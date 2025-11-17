#include<iostream>
#include<string>
#include"include/queue.h"

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
    // tail можно не хранить, нам важен только head для минимальных элементов

    HoffQueue() : head(nullptr) {}

    bool is_empty() {
        return head == nullptr;
    }

    // вставка с сохранением сортировки по priority (по возрастанию)
    void push_sorted(NodeHoffQueue* node) {
        if (head == nullptr || node->priority < head->priority) {
            node->next = head;
            head = node;
            return;
        }

        NodeHoffQueue* curr = head;
        while (curr->next != nullptr && curr->next->priority <= node->priority) {
            curr = curr->next;
        }

        node->next = curr->next;
        curr->next = node;
    }

    // забрать минимальный элемент (с головы)
    NodeHoffQueue* pop_min() {
        if (is_empty()) return nullptr;

        NodeHoffQueue* node = head;
        head = head->next;
        node->next = nullptr;
        return node;
    }
};

NodeHoffQueue* buildHuffman(HoffQueue& hoff) {
    // пока в очереди больше одного элемента — продолжаем слияние
    while (!hoff.is_empty() && hoff.head->next != nullptr) {
        // достаём два узла с минимальным priority
        NodeHoffQueue* a = hoff.pop_min();
        NodeHoffQueue* b = hoff.pop_min();

        // создаём родителя
        NodeHoffQueue* parent = new NodeHoffQueue('*', a->priority + b->priority);
        parent->left = a;
        parent->right = b;

        // кладём родителя обратно в очередь
        hoff.push_sorted(parent);
    }

    // остался один элемент — это корень дерева
    return hoff.head; // может быть nullptr, если очередь была пустой
}

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

void print_codes(NodeHoffQueue* node, string code = "") {
    if (node == nullptr) return;

    // лист (символ)
    if (node->left == nullptr && node->right == nullptr) {
        cout << node->data << ": " << code << endl;
        return;
    }

    print_codes(node->left,  code + "0");
    print_codes(node->right, code + "1");
}

int main() {

    HoffQueue hoff;
    Queue queue;

    string ser = "poor mister evas";
    for (char c : ser) {
        search(c, queue);
    }

    // просто для контроля:
    queue.sort_by_priority();
    queue.print();

    // Переносим элементы из Queue в HoffQueue
    NodeQueue* curr = queue.head;
    while (curr != nullptr) {
        NodeHoffQueue* node = new NodeHoffQueue(curr->data, curr->priority);
        hoff.push_sorted(node);
        curr = curr->next;
    }

    // Строим дерево Хаффмана
    NodeHoffQueue* root = buildHuffman(hoff);
    print_codes(root);

    // тут можно, например, вывести коды символов, если захочешь

    return 0;
}