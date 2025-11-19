#include <iostream>
#include <string>
#include "include/queue.h"
#include "include/huffman.h"

using namespace std;

//g++ main.cpp entity/huffman.cpp entity/queue.cpp -o m 

// Вывод кодов Хаффмана для каждого символа
void print_codes(NodeHoffQueue* node, string code = "") {
    if (node == nullptr) return;

    // Если узел — лист, то здесь хранится символ
    if (node->left == nullptr && node->right == nullptr) {
        cout << node->data << ": " << code << endl;
        return;
    }

    // Рекурсивный обход левого и правого поддерева
    print_codes(node->left,  code + "0");
    print_codes(node->right, code + "1");
}

int main() {
    HoffQueue hoff; 
    Queue queue;

    // Исходная строка для построения кодов
    string ser = "abracadabra";

    // Подсчёт количества каждого символа
    for (char c : ser) {
        search(c, queue);
    }

    // Сортировка символов по частоте
    queue.sort_by_priority();
    queue.print();

    // Перенос частот в очередь Хаффмана
    NodeQueue* curr = queue.head;
    while (curr != nullptr) {
        NodeHoffQueue* node = new NodeHoffQueue(curr->data, curr->priority);
        hoff.push_sorted(node);
        curr = curr->next;
    }

    // Построение дерева Хаффмана
    NodeHoffQueue* root = buildHuffman(hoff);

    // Вывод бинарных кодов для всех символов строки
    print_codes(root);

    return 0;
}
