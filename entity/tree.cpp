#include"../include/tree.h"
#include<stdexcept>
#include<sstream>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

// Конструктор узла дерева, инициализирует данные, высоту и указатели на потомков
Node::Node(int k) : data(k), left(nullptr), right(nullptr), height(1) {}

// Конструктор элемента очереди, хранящего указатель на узел дерева
NodePtrQueue::NodePtrQueue(Node* value) : data(value), next(nullptr) {}

// Конструктор очереди указателей на узлы дерева
QueueNodePtr::QueueNodePtr() : head(nullptr), tail(nullptr) {}

// Проверка, является ли очередь пустой
bool QueueNodePtr::is_empty() {
    return head == nullptr;
}

// Добавление элемента в конец очереди
void QueueNodePtr::enqueue(Node* value) {
    NodePtrQueue* p = new NodePtrQueue(value);
    if (is_empty()) {
        head = tail = p;
        return;
    }
    tail->next = p;
    tail = p;
}

// Извлечение элемента из начала очереди
Node* QueueNodePtr::dequeue() {
    if (is_empty()) throw runtime_error("Очередь пуста");
    NodePtrQueue* p = head;
    Node* value = p->data;
    head = head->next;
    delete p;
    if (head == nullptr) tail = nullptr;
    return value;
}

// Очистка всей очереди
void QueueNodePtr::clear() {
    while (!is_empty()) dequeue();
}

// Деструктор очереди - автоматически очищает память
QueueNodePtr::~QueueNodePtr() {
    clear();
}

// Конструктор AVL-дерева, инициализирует корень как пустой указатель
AVLtree::AVLtree() : root(nullptr) {};

// Получение высоты узла (для пустого узла высота равна 0)
int AVLtree::getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Вычисление баланс-фактора узла (разница высот левого и правого поддеревьев)
int AVLtree::getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Обновление высоты узла на основе высот его потомков
void AVLtree::updateHeight(Node* node) {
    if (node != nullptr) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Правый поворот для балансировки дерева
Node* AVLtree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    // Выполнение поворота
    x->right = y;
    y->left = T2;
    
    // Обновление высот после поворота
    updateHeight(y);
    updateHeight(x);
    
    return x;
}

// Левый поворот для балансировки дерева
Node* AVLtree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    
    // Выполнение поворота
    y->left = x;
    x->right = T2;
    
    // Обновление высот после поворота
    updateHeight(x);
    updateHeight(y);
    
    return y;
}

// Балансировка узла после операций вставки или удаления
Node* AVLtree::balance(Node* node) {
    if (!node) return node;
    
    updateHeight(node);
    int balanceFactor = getBalance(node);
    
    // Случай правый - требуется один правый поворот
    if (balanceFactor > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    
    // Случай левый - требуется один левый поворот
    if (balanceFactor < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    
    // Случай левый-правый - требуется левый поворот левого потомка, затем правый поворот текущего узла
    if (balanceFactor > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Случай правый-левый - требуется правый поворот правого потомка, затем левый поворот текущего узла
    if (balanceFactor < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

// Рекурсивная вставка значения в дерево с последующей балансировкой
Node* AVLtree::insert(Node* root, int value) {
    if (root == nullptr) return new Node(value);

    // Рекурсивный поиск места для вставки
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        // Значение уже существует в дереве
        return root;
    }

    // Балансировка дерева после вставки
    return balance(root);
}

// Публичный метод для вставки значения в дерево
void AVLtree::insert(int value) {
    root = insert(root, value);
}

// Поиск узла с максимальным значением в поддереве
Node* AVLtree::find_max(Node* node) {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}

// Рекурсивное удаление значения из дерева с последующей балансировкой
Node* AVLtree::del(Node* node, int value) {
    if (!node) return nullptr;

    // Поиск удаляемого узла
    if (value < node->data) {
        node->left = del(node->left, value);
    } else if (value > node->data) {
        node->right = del(node->right, value);
    } else {
        
        // Случай 1: узел без потомков (лист)
        if (!node->left && !node->right) { 
            delete node;
            return nullptr;
        } 
        // Случай 2: узел с одним потомком (правым)
        else if (!node->left) {         
            Node* temp = node->right;
            delete node;
            return temp;                  
        } 
        // Случай 3: узел с одним потомком (левым)
        else if (!node->right) {        
            Node* temp = node->left;
            delete node;
            return temp;                  
        }

        // Случай 4: узел с двумя потомками
        // Замена значения на максимальное из левого поддерева
        Node* temp = find_max(node->left);
        node->data = temp->data;
        // Рекурсивное удаление узла с максимальным значением из левого поддерева
        node->left = del(node->left, temp->data);
    }

    // Балансировка дерева после удаления
    return balance(node);
}  

// метод для удаления значения из дерева
void AVLtree::del(int value) {
    root = del(root, value); 
}

// Поиск значения в дереве и вывод его высоты
void AVLtree::find(int value) {
    Node* currentNode = root;
    while (currentNode && currentNode->data != value) {  
        if (value < currentNode->data) currentNode = currentNode->left;
        else currentNode = currentNode->right;
    }
    if (currentNode) cout << currentNode->height;
    else cout << "Элемент отсутствует";
}

// Прямой обход дерева (корень-левый-правый)
void AVLtree::printPreOrder(Node* root) {
    if (!root) {
        cout << "Дерево пустое";
        return;
    }
    
    cout << root->data << " ";
    if (root->left) printPreOrder(root->left);
    if (root->right) printPreOrder(root->right);
}

void AVLtree::printPreOrder() {
    printPreOrder(root);
}

// Симметричный обход дерева (левый-корень-правый)
void AVLtree::printInOrder(Node* root) {
    if (!root) {
        cout << "Дерево пустое";
        return;
    }

    if (root->left) printInOrder(root->left);
    cout << root->data << " ";
    if (root->right) printInOrder(root->right);
}

void AVLtree::printInOrder() {
    printInOrder(root);
}

// Обратный обход дерева (левый-правый-корень)
void AVLtree::printPostOrder(Node* root) {
    if (!root) {
        cout << "Дерево пустое";
        return;
    }

    if (root->left) printPostOrder(root->left);
    if (root->right) printPostOrder(root->right);
    cout << root->data << " ";
}

void AVLtree::printPostOrder() {
    printPostOrder(root);
}

// Обход дерева в ширину (по уровням)
void AVLtree::printLevelOrder(Node* root) {
    if (!root) {
        cout << "Дерево пустое";
        return;
    }

    QueueNodePtr q;
    q.enqueue(root);

    while (!q.is_empty()) {
        Node* curr = q.dequeue();
        cout << curr->data << " ";

        // Добавление потомков в очередь для обработки на следующих уровнях
        if (curr->left) q.enqueue(curr->left);
        if (curr->right) q.enqueue(curr->right);
    }
    cout << endl;
}

void AVLtree::printLevelOrder() {
    printLevelOrder(root);
}

// Рекурсивный вывод дерева с визуализацией структуры и высот узлов
void AVLtree::printTreeWithHeights(Node* node, const string& prefix, bool isLeft) {
    if (node != nullptr) {
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        cout << node->data << "(h:" << node->height << ")" << endl;
        
        // Рекурсивный вывод левого и правого поддеревьев
        printTreeWithHeights(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printTreeWithHeights(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

// метод для вывода структуры дерева
void AVLtree::printTree() {
    cout << "Структура дерева:" << endl;
    printTreeWithHeights(root);
}

// Сохранение дерева в файл в виде последовательности команд вставки
void AVLtree::saveToFile(ofstream& file, Node* node) {
    if (node == nullptr) return;
    saveToFile(file, node->left);
    file << "TREE_INSERT " << std::to_string(node->data) << "\n";
    saveToFile(file, node->right);
}

void AVLtree::saveToFile(ofstream& file) {
    saveToFile(file, root);
}

// Сохранение значений дерева в отсортированном порядке
void AVLtree::saveValues(std::ostream& out, Node* node) {
    if (!node) return;
    saveValues(out, node->left);
    out << node->data << ' ';
    saveValues(out, node->right);
}

void AVLtree::saveValues(std::ostream& out) {
    saveValues(out, root);
}