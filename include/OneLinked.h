#include<stdexcept>
#include<iostream>
#include<string>
#pragma once

using namespace std;

struct NodeOneLinked {
    string data;
    NodeOneLinked *pNext;
    NodeOneLinked(string value);
};

struct listOneLinked {
    NodeOneLinked* head;
    NodeOneLinked* tail;

    listOneLinked();
    bool is_empty();
    NodeOneLinked* find(string value);
    NodeOneLinked* find_previous(string value);
    NodeOneLinked* find_next(string value);
    void push_back(string value);
    void push_forward(string value);
    void push_beforeNode(string newValue, string placedData);
    void push_afterNode(string newValue, string placedData);
    void delete_forward();
    void delete_back();
    void delete_beforeNode(string value);
    void delete_afterNode(string value);
    void delete_data(string value);
    void print_recursion();
    void print_recursion_impl(NodeOneLinked* p);
    void print_sequentially();
    void clear();
    ~listOneLinked();
};