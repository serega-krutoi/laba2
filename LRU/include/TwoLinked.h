#include<stdexcept>
#include<iostream>
#include<string>
#pragma once

using namespace std;

struct TwoLinkedNode {
    string data;
    TwoLinkedNode* pNext;
    TwoLinkedNode* pPrevios; 
    TwoLinkedNode(string value);
};

struct listTwoLinked {
    TwoLinkedNode* head;
    TwoLinkedNode* tail;

    listTwoLinked();
    bool is_empty();
    TwoLinkedNode* find(string value);
    void push_back(string value);
    void push_forward(string value);
    void push_beforeNode(string newValue, string placedData);
    void push_afterNode(string newValue, string placedData);
    void delete_back();
    void delete_forward();
    void delete_beforeNode(string value);
    void delete_afterNode(string value);
    void delete_data(string value);
    void print_sequentially();
    void print_reverse();
    void clear();
    void move_to_front(TwoLinkedNode* node);   
    ~listTwoLinked();
};
