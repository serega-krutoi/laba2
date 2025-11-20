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

// Кодирование строки с использованием дерева Хаффмана
string encode_string(NodeHoffQueue* node, const string& text, string code = "") {
    if (node == nullptr) return "";

    // Если узел — лист, возвращаем код для этого символа
    if (node->left == nullptr && node->right == nullptr) {
        if (node->data == text[0]) {
            return code;
        }
        return "";
    }

    // Рекурсивный поиск символа в левом и правом поддереве
    string left_code = encode_string(node->left, text, code + "0");
    string right_code = encode_string(node->right, text, code + "1");
    
    return left_code + right_code;
}

// Рекурсивная функция для получения кода одного символа
string get_char_code(NodeHoffQueue* node, char target, string code = "") {
    if (node == nullptr) return "";
    
    if (node->left == nullptr && node->right == nullptr) {
        if (node->data == target) {
            return code;
        }
        return "";
    }
    
    string left_code = get_char_code(node->left, target, code + "0");
    if (!left_code.empty()) return left_code;
    
    string right_code = get_char_code(node->right, target, code + "1");
    return right_code;
}

// Кодирование всей строки
string encode_full_string(NodeHoffQueue* root, const string& text) {
    string encoded = "";
    for (char c : text) {
        string char_code = get_char_code(root, c);
        if (!char_code.empty()) {
            encoded += char_code;
        } else {
            cout << "Ошибка: символ '" << c << "' не найден в дереве" << endl;
        }
    }
    return encoded;
}

// Декодирование строки с использованием дерева Хаффмана
string decode_string(NodeHoffQueue* root, const string& encoded) {
    string decoded = "";
    NodeHoffQueue* current = root;
    
    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            cout << "Ошибка: недопустимый бит '" << bit << "'" << endl;
            return "";
        }
        
        if (current->left == nullptr && current->right == nullptr) {
            decoded += current->data;
            current = root;
        }
    }
    
    return decoded;
}

int main() {
    HoffQueue hoff; 
    Queue queue;

    // Исходная строка для построения кодов
    string original_text = "abracadabra";
    cout << "Исходная строка: " << original_text << endl;

    // Подсчёт количества каждого символа
    for (char c : original_text) {
        search(c, queue);
    }

    // Сортировка символов по частоте
    queue.sort_by_priority();
    cout << "Отсортированные символы по частоте: ";
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
    cout << "\nКоды Хаффмана:" << endl;
    print_codes(root);

    // Кодирование исходной строки
    string encoded_text = encode_full_string(root, original_text);
    cout << "\nЗакодированная строка: " << encoded_text << endl;
    cout << "Длина закодированной строки: " << encoded_text.length() << " бит" << endl;

    // Декодирование обратно
    string decoded_text = decode_string(root, encoded_text);
    cout << "Декодированная строка: " << decoded_text << endl;

    // Проверка корректности
    if (original_text == decoded_text) {
        cout << "Декодирование выполнено" << endl;
    } else {
        cout << "Ошибка при декодировании" << endl;
    }

    return 0;
}