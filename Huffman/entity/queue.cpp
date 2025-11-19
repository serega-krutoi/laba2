#include "../include/queue.h"
#include <stdexcept>
#include <iostream>

using namespace std;

// Создание узла очереди, частота нового символа по умолчанию равна 1
NodeQueue::NodeQueue(char value) : data(value), next(nullptr), priority(1) {}

// Инициализация пустой очереди
Queue::Queue() : head(nullptr), tail(nullptr) {}

// Проверка: очередь пуста или нет
bool Queue::is_empty() {
    return head == nullptr;
}

// Добавление элемента в конец очереди
void Queue::enqueue(char value) {
    NodeQueue* p = new NodeQueue(value);

    // Если очередь пуста — новый узел становится и головой, и хвостом
    if (is_empty()) {
        head = tail = p;
        return;
    }

    // Обычная вставка в конец списка
    tail->next = p;
    tail = p;
}

// Удаление элемента из начала очереди
void Queue::dequeue() {
    if (is_empty()) {
        throw runtime_error("Очередь пуста");
    }

    NodeQueue* p = head;
    head = head->next;
    delete p;

    if (head == nullptr) tail = nullptr;
}

// Вывод очереди: символ и его частота
void Queue::print() {
    NodeQueue* p = head;

    while (p != nullptr) {
        cout << p->data << "-" << p->priority << " ";
        p = p->next;
    }
    cout << endl;
}

// Полная очистка очереди
void Queue::clear() {
    while (!is_empty()) dequeue();
}

// Деструктор освобождает всю память очереди
Queue::~Queue() {
    clear();
}

// Сортировка очереди по возрастанию частоты символов
void Queue::sort_by_priority() {
    // Если в очереди 0 или 1 элемент — сортировать нечего
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;

    // Пузырьковая сортировка по частоте
    do {
        swapped = false;
        NodeQueue* curr = head;
        NodeQueue* prev = nullptr;

        while (curr->next != nullptr) {
            NodeQueue* next = curr->next;

            if (curr->priority > next->priority) {
                swapped = true;

                // Перестановка двух соседних узлов
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

        // Обновляем указатель на хвост
        tail = head;
        while (tail->next != nullptr) tail = tail->next;

    } while (swapped);
}
