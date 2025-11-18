#include"../include/huffman.h"
#include"../include/queue.h"


bool HoffQueue::is_empty() {
    return head == nullptr;
}

// вставка с сохранением сортировки по priority (по возрастанию)
void HoffQueue::push_sorted(NodeHoffQueue* node) {
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
NodeHoffQueue* HoffQueue::pop_min() {
    if (is_empty()) return nullptr;

    NodeHoffQueue* node = head;
    head = head->next;
    node->next = nullptr;
    return node;
}


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