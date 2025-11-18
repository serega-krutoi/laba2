#pragma once
#include<string>

using namespace std;

struct Node {
    string data;
    Node* left;
    Node* right;

    Node(string val) : data(val), left(nullptr), right(nullptr) {}
};

void dfs(Node* root);