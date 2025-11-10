#include"../include/TwoLinked.h"
#include<stdexcept>
#include<iostream>

using namespace std;

// Конструктор узла двусвязного списка, инициализирует данные и указатели на следующий и предыдущий элементы
TwoLinkedNode::TwoLinkedNode(string value) : data(value), pNext(nullptr), pPrevios(nullptr) {}

// Конструктор двусвязного списка, инициализирует голову и хвост как пустые указатели
listTwoLinked::listTwoLinked() : head(nullptr), tail(nullptr) {}

// Проверка, является ли список пустым
bool listTwoLinked::is_empty() {
    return head == nullptr;
}

// Поиск узла с заданным значением в списке
TwoLinkedNode* listTwoLinked::find(string value) {
    TwoLinkedNode* p = head;
    // Последовательный проход по списку до нахождения нужного значения или конца списка
    while (p && p->data != value) p = p->pNext;
    return p;
}

// Добавление элемента в конец списка
void listTwoLinked::push_back(string value) {
    TwoLinkedNode* p = new TwoLinkedNode(value);
    // Если список пустой, новый элемент становится и головой и хвостом
    if (is_empty()) {
        head = tail = p;
        return;
    }
    // Связывание текущего хвоста с новым элементом
    tail->pNext = p;
    p->pPrevios = tail;
    // Обновление хвоста списка на новый элемент
    tail = p;
}

// Добавление элемента в начало списка
void listTwoLinked::push_forward(string value) {
    TwoLinkedNode* p = new TwoLinkedNode(value);
    // Если список пустой, новый элемент становится и головой и хвостом
    if (is_empty()) {
        head = tail = p;
        return;
    }
    // Связывание нового элемента с текущей головой
    p->pNext = head;
    head->pPrevios = p;
    // Обновление головы списка на новый элемент
    head = p;
}

// Добавление элемента перед узлом с указанным значением
void listTwoLinked::push_beforeNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(placedData);
    if (!currentNode) throw runtime_error("Нет такого значения");

    // Если целевой узел - голова, используем добавление в начало
    if (currentNode == head) { 
        push_forward(newValue);
        return;
    }

    // Создание нового узла и связывание его с соседними узлами
    TwoLinkedNode* previosNode = currentNode->pPrevios;
    TwoLinkedNode* p = new TwoLinkedNode(newValue);
    p->pPrevios = previosNode;
    p->pNext = currentNode;
    previosNode->pNext = p;
    currentNode->pPrevios = p;
}

// Добавление элемента после узла с указанным значением
void listTwoLinked::push_afterNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(placedData);
    if (!currentNode) throw runtime_error("Нет такого значения");

    // Если целевой узел - хвост, используем добавление в конец
    if (currentNode == tail) { 
        push_back(newValue);
        return;
    }

    // Создание нового узла и связывание его с соседними узлами
    TwoLinkedNode* nextNode = currentNode->pNext; 
    TwoLinkedNode* p = new TwoLinkedNode(newValue);
    p->pNext = nextNode;
    p->pPrevios = currentNode;
    currentNode->pNext = p;
    nextNode->pPrevios = p;
}

// Удаление последнего элемента списка
void listTwoLinked::delete_back() {
    if (is_empty()) throw runtime_error("Список пуст");
    // Если в списке только один элемент
    if (head == tail) { 
        delete tail;
        head = tail = nullptr;
        return;
    }
    // Удаление хвоста и обновление указателей
    TwoLinkedNode* p = tail;
    tail = tail->pPrevios;
    tail->pNext = nullptr;
    delete p;
}

// Удаление первого элемента списка
void listTwoLinked::delete_forward() {
    if (is_empty()) throw runtime_error("Список пуст");
    // Если в списке только один элемент
    if (head == tail) { 
        delete head;
        head = tail = nullptr;
        return;
    }
    // Удаление головы и обновление указателей
    TwoLinkedNode* p = head;
    head = head->pNext;
    head->pPrevios = nullptr;
    delete p;
}

// Удаление элемента, расположенного перед узлом с указанным значением
void listTwoLinked::delete_beforeNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(value);
    if (!currentNode) throw runtime_error("Нет такого значения");
    // Проверка, что перед головой нет узла для удаления
    if (currentNode == head) throw runtime_error("Перед головой нет узла");

    TwoLinkedNode* deletingNode = currentNode->pPrevios; 
    // Если удаляемый узел - голова, используем удаление из начала
    if (deletingNode == head) { 
        delete_forward();
        return;
    }

    // Связывание узлов вокруг удаляемого элемента
    TwoLinkedNode* previosNode = deletingNode->pPrevios; 
    previosNode->pNext = currentNode;
    currentNode->pPrevios = previosNode;
    delete deletingNode;
}

// Удаление элемента, расположенного после узла с указанным значением
void listTwoLinked::delete_afterNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* currentNode = find(value);
    if (!currentNode) throw runtime_error("Нет такого значения");
    // Проверка, что после указанного узла есть элемент для удаления
    if (!currentNode->pNext) throw runtime_error("После указанного узла ничего нет");

    TwoLinkedNode* deletingNode = currentNode->pNext;
    TwoLinkedNode* nextNode = deletingNode->pNext; 

    // Связывание текущего узла со следующим после удаляемого
    currentNode->pNext = nextNode;
    if (nextNode) {
        nextNode->pPrevios = currentNode;
    } else {
        // Если удаляемый узел был хвостом, обновляем хвост
        tail = currentNode; 
    }
    delete deletingNode;
}

// Удаление узла с указанным значением
void listTwoLinked::delete_data(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    TwoLinkedNode* deletingNode = find(value);
    if (!deletingNode) throw runtime_error("Нет такого значения");

    // Если удаляемый узел - голова или хвост, используем специализированные методы
    if (deletingNode == head) {
        delete_forward();
        return;
    }
    if (deletingNode == tail) {
        delete_back();
        return;
    }

    // Связывание соседних узлов вокруг удаляемого элемента
    TwoLinkedNode* prevNode = deletingNode->pPrevios; 
    TwoLinkedNode* nextNode = deletingNode->pNext;    
    prevNode->pNext = nextNode;
    nextNode->pPrevios = prevNode;
    delete deletingNode;
}

// Прямой вывод элементов списка от головы к хвосту
void listTwoLinked::print_sequentially() {
    TwoLinkedNode* p = head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << endl;
}

// Обратный вывод элементов списка от хвоста к голове
void listTwoLinked::print_reverse() {
    TwoLinkedNode* p = tail;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->pPrevios;
    }
    cout << endl;
}

// Очистка всего списка
void listTwoLinked::clear() {
    while (!is_empty()) delete_forward();
}

// Деструктор списка - автоматически очищает память при уничтожении объекта
listTwoLinked::~listTwoLinked() {
    clear();
}