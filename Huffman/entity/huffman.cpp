#include "../include/huffman.h"
#include "../include/queue.h"

// Проверка: очередь пуста или нет
bool HoffQueue::is_empty() {
    return head == nullptr;
}

// Вставка узла в очередь Хаффмана с сохранением порядка по возрастанию приоритета
void HoffQueue::push_sorted(NodeHoffQueue* node) {
    // Если очередь пуста или приоритет нового узла меньше первого — ставим в начало
    if (head == nullptr || node->priority < head->priority) {
        node->next = head;
        head = node;
        return;
    }

    // Поиск позиции, где приоритет становится больше
    NodeHoffQueue* curr = head;
    while (curr->next != nullptr && curr->next->priority <= node->priority) {
        curr = curr->next;
    }

    // Вставка узла внутрь списка
    node->next = curr->next;
    curr->next = node;
}

// Извлечение узла с минимальным приоритетом (первого в очереди)
NodeHoffQueue* HoffQueue::pop_min() {
    if (is_empty()) return nullptr;

    NodeHoffQueue* node = head;
    head = head->next;
    node->next = nullptr;
    return node;
}

// Построение дерева Хаффмана на основе отсортированной очереди
NodeHoffQueue* buildHuffman(HoffQueue& hoff) {
    // Пока в очереди больше одного узла — объединяем два минимальных
    while (!hoff.is_empty() && hoff.head->next != nullptr) {

        // Извлекаются два узла с наименьшим приоритетом
        NodeHoffQueue* a = hoff.pop_min();
        NodeHoffQueue* b = hoff.pop_min();

        // Создаётся новый узел, приоритет равен сумме приоритетов двух дочерних
        NodeHoffQueue* parent = new NodeHoffQueue('*', a->priority + b->priority);
        parent->left = a;
        parent->right = b;

        // Новый узел возвращается в очередь на своё место по приоритету
        hoff.push_sorted(parent);
    }

    // В конце в очереди остаётся только корень дерева
    return hoff.head;
}

// Подсчёт частоты появления символов в строке
void search(char c, Queue& queue) {
    NodeQueue* curr = queue.head;
    bool found = false;

    // Поиск символа в очереди
    while (curr != nullptr) {  
        if (curr->data == c) {
            curr->priority += 1; // если найден — увеличивается частота
            found = true;
            break;
        }
        curr = curr->next;
    }

    // Если символ не встречался — он добавляется в конец очереди
    if (!found) {
        queue.enqueue(c);
    }
}
