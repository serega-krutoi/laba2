#include<string>
#pragma once

using namespace std;

struct Node{
    string key;
    string data;
    Node* next;
    Node(string k, string d) : key(k), data(d), next(nullptr) {}
};

size_t djb2_hash(const string& key);
void insert(const string& value, const string& key);
string search(const string& key);
void remove(const string& key);