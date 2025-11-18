#include<string>
#include<iostream>
#pragma once

using namespace std;

struct Entry {
    string key;
    string data;
    bool isDelete;
    Entry(string k, string d) : key(k), data(d), isDelete(false) {}
};

size_t djb2_hash(const string& key);
void insert(const string& key, const string& value);
string search(const string& key);
void remove(const string& key);