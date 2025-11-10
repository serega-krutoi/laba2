#include"../include/OneLinked.h"
#include<stdexcept>
#include<iostream>

using namespace std;

// Конструктор узла односвязного списка, инициализирует данные и указатель на следующий элемент
NodeOneLinked::NodeOneLinked(string value) : data(value), pNext(nullptr) {}

// Конструктор односвязного списка, инициализирует голову и хвост как пустые указатели
listOneLinked::listOneLinked() : head(nullptr), tail(nullptr) {}

// Проверка, является ли список пустым
bool listOneLinked::is_empty() {
    return head == nullptr;
}

// Поиск узла с заданным значением в списке
NodeOneLinked* listOneLinked::find(string value) {
    NodeOneLinked* p = head;
    // Последовательный проход по списку до нахождения нужного значения или конца списка
    while (p && p->data != value) p = p->pNext;
    return p;
}

// Поиск предыдущего узла относительно узла с заданным значением
NodeOneLinked* listOneLinked::find_previous(string value) {
    // Если список пустой или искомый узел - голова, предыдущего узла не существует
    if (is_empty() || head->data == value) return nullptr;
    NodeOneLinked* prev = head;
    NodeOneLinked* cur = head->pNext;
    // Поиск узла, предшествующего целевому
    while (cur && cur->data != value) {
        prev = cur;
        cur = cur->pNext;
    }
    // Возврат предыдущего узла, если целевой узел найден
    return cur ? prev : nullptr;
}

// Поиск следующего узла после узла с заданным значением
NodeOneLinked* listOneLinked::find_next(string value) {
    NodeOneLinked* p = find(value);
    // Возврат следующего узла, если текущий узел найден
    return (p != nullptr) ? p->pNext : nullptr;
}

// Добавление элемента в конец списка
void listOneLinked::push_back(string value) {
    NodeOneLinked* p = new NodeOneLinked(value);
    // Если список пустой, новый элемент становится и головой и хвостом
    if (is_empty()) {
        head = tail = p;
        return;
    }
    // Связывание текущего хвоста с новым элементом
    tail->pNext = p;
    // Обновление хвоста списка на новый элемент
    tail = p;
}

// Добавление элемента в начало списка
void listOneLinked::push_forward(string value) {
    NodeOneLinked* p = new NodeOneLinked(value);
    // Если список пустой, новый элемент становится и головой и хвостом
    if (is_empty()) {
        head = tail = p;
        return;
    }
    // Связывание нового элемента с текущей головой
    p->pNext = head;
    // Обновление головы списка на новый элемент
    head = p;
}

// Добавление элемента перед узлом с указанным значением
void listOneLinked::push_beforeNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");
    NodeOneLinked* placed = find(placedData);
    if (!placed) throw runtime_error("Нет такого значения");

    // Если вставляем перед головой, используем добавление в начало
    if (placed == head) {
        push_forward(newValue);
        return;
    }

    // Поиск предыдущего узла и вставка нового элемента между ними
    NodeOneLinked* prev = find_previous(placedData);
    NodeOneLinked* node = new NodeOneLinked(newValue);
    prev->pNext = node;
    node->pNext = placed;
}

// Добавление элемента после узла с указанным значением
void listOneLinked::push_afterNode(string newValue, string placedData) {
    if (is_empty()) throw runtime_error("Список пуст");
    NodeOneLinked* placed = find(placedData);
    if (!placed) throw runtime_error("Нет такого значения");

    // Создание нового узла и вставка его после целевого узла
    NodeOneLinked* node = new NodeOneLinked(newValue);
    node->pNext = placed->pNext;
    placed->pNext = node;
    // Если вставляем после хвоста, обновляем указатель на хвост
    if (placed == tail) tail = node;
}

// Удаление первого элемента списка
void listOneLinked::delete_forward() {
    if (is_empty()) throw runtime_error("Список пуст");
    NodeOneLinked* p = head;
    head = head->pNext;
    delete p;
    // Если список стал пустым, обнуляем указатель на хвост
    if (!head) tail = nullptr;
}

// Удаление последнего элемента списка
void listOneLinked::delete_back() {
    if (is_empty()) throw runtime_error("Список пуст");
    // Если в списке только один элемент
    if (head == tail) {
        delete_forward();
        return;
    }
    // Поиск предпоследнего элемента
    NodeOneLinked* prev = head;
    while (prev->pNext != tail) prev = prev->pNext;
    // Удаление хвоста и обновление указателей
    delete tail;
    tail = prev;
    tail->pNext = nullptr;
}

// Удаление элемента, расположенного перед узлом с указанным значением
void listOneLinked::delete_beforeNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    NodeOneLinked* target = find(value);
    if (!target) throw runtime_error("Нет такого значения");
    // Проверка, что перед головой нет узла для удаления
    if (target == head) throw runtime_error("Перед головой нет узла");

    NodeOneLinked* prev = find_previous(value);
    // Если удаляемый узел - голова, используем удаление из начала
    if (prev == head) {
        delete_forward();
        return;
    }

    // Поиск узла, предшествующего удаляемому, и связывание его с целевым узлом
    NodeOneLinked* prevprev = find_previous(prev->data);
    prevprev->pNext = target;
    delete prev;
}

// Удаление элемента, расположенного после узла с указанным значением
void listOneLinked::delete_afterNode(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    NodeOneLinked* current = find(value);
    if (!current) throw runtime_error("Нет такого значения");
    // Проверка, что после указанного узла есть элемент для удаления
    if (!current->pNext) throw runtime_error("После указанного узла ничего нет");

    NodeOneLinked* victim = current->pNext;
    current->pNext = victim->pNext;
    // Если удаляемый узел был хвостом, обновляем хвост
    if (victim == tail) tail = current;
    delete victim;
}

// Удаление узла с указанным значением
void listOneLinked::delete_data(string value) {
    if (is_empty()) throw runtime_error("Список пуст");
    // Если удаляемый узел - голова, используем удаление из начала
    if (head->data == value) {
        delete_forward();
        return;
    }
    NodeOneLinked* prev = find_previous(value);
    if (!prev) throw runtime_error("Нет такого значения");
    NodeOneLinked* victim = prev->pNext;
    prev->pNext = victim->pNext;
    // Если удаляемый узел был хвостом, обновляем хвост
    if (victim == tail) tail = prev;
    delete victim;
}

// Рекурсивный вывод элементов списка
void listOneLinked::print_recursion() {
    print_recursion_impl(head);
    cout << endl;
}

// Вспомогательная функция для рекурсивного вывода
void listOneLinked::print_recursion_impl(NodeOneLinked* p) {
    if (!p) return;
    cout << p->data << " ";
    print_recursion_impl(p->pNext);
}

// Последовательный вывод элементов списка от головы к хвосту
void listOneLinked::print_sequentially() {
    NodeOneLinked* p = head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << endl;
}

// Очистка всего списка
void listOneLinked::clear() {
    while (!is_empty()) delete_forward();
}

// Деструктор списка - автоматически очищает память при уничтожении объекта
listOneLinked::~listOneLinked() {
    clear();
}