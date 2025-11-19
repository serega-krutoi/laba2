#include<iostream>
#include<string>
#include"include/queue.h"
#include"include/huffman.h"

using namespace std;

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

    string ser = "abracadabra";
    for (char c : ser) {
        search(c, queue);
    }

    queue.sort_by_priority();
    queue.print();

    // Перенос элементов из Queue в HoffQueue
    NodeQueue* curr = queue.head;
    while (curr != nullptr) {
        NodeHoffQueue* node = new NodeHoffQueue(curr->data, curr->priority);
        hoff.push_sorted(node);
        curr = curr->next;
    }

    // дерево Хаффмана
    NodeHoffQueue* root = buildHuffman(hoff);
    print_codes(root);

    return 0;
}