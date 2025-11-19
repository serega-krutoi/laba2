#include <iostream>
#include <string>
#include "include/dfs.h" 
using namespace std;

//g++ main.cpp entity/dfs.cpp -o m

int main() {
    /*
            A
           / \
          B   C
         / \   \
        D   E   F
    */

    // Ручное построение дерева для примера
    Node* root = new Node("A");
    root->left = new Node("B");
    root->right = new Node("C");
    root->left->left = new Node("D");
    root->left->right = new Node("E");
    root->right->right = new Node("F");

    cout << "Обход дерева в глубину (DFS) через собственный стек:\n";
    dfs(root);
    cout << endl;

    return 0;
}
