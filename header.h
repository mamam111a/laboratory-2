#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;


struct SingleNode {
    string cell;
    SingleNode* next;

};

struct Set {
    string value;
};

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

struct NodeHash {
    string key;
    string value;
    NodeHash* next;

    NodeHash(string& k, string& v) : key(k), value(v), next(nullptr) {}
};

struct Stack {
    int size;
    string cell;
    ~Stack();
    SingleNode* head;
    SingleNode* tail;
    void SPUSH(string& cell);
    void SPOP();
    void SREAD();
    void Clear();
    void DeleteTail();
    void DelElementValue(SingleNode* target);
    void AddTail(string& cell);

    Stack() : size(0), head(nullptr), tail(nullptr) {
    }
};
Stack::~Stack() {
    Clear();
}

struct SetNode {
    int size;
    Set** plenty;

    SetNode(int cap);
    ~SetNode();
    int HashSet(string itemKey);
    bool isFull();
    bool FindValue(string value, int& znach);
    void SETADD(string value);
    void SETDEL(string value);
    void SET_AT(string value);
};

SetNode::SetNode(int cap) : size(cap) {
    plenty = new Set * [size];
    for (int i = 0; i < size; i++) {
        plenty[i] = nullptr;
    }
}

SetNode::~SetNode() {
    for (int i = 0; i < size; ++i) {
        delete plenty[i];
    }
    delete[] plenty;
}

struct Array {
    string* data;
    int size;
    int maxSize;

    Array();
    ~Array();
    void MPUSHend(string& value);
    void MPUSHindex(const int& index, string& value);
    string MGETL(const int& index);
    void MDEL(const int& index);
    void MREPL(const int& index, string& value);
    int MSIZE();
    void MREAD();
};
Array::Array() : size(0), maxSize(100) {
    data = new string[maxSize];
}
Array::~Array() {
    delete[] data;
}

struct Tree {
    TreeNode* root;
    Tree() : root(nullptr) {};

    ~Tree();
    void Destroy(TreeNode* node);
    TreeNode* FindMin(TreeNode* node);
    TreeNode* DeleteNode(TreeNode* root, int key);
    TreeNode* InsertRecursive(TreeNode* node, int value);
    void Insert(int value);
    void Print(const string& prefix, TreeNode* node, bool isLeft);
};

Tree::~Tree() {
    Destroy(root);
}

struct HashTable {
    NodeHash** table; // массив указателей на узлы хеш-таблицы
    int size;
    int count;

    HashTable(int initialSize = 100);
    int HashFunc(string& str);
    void HPUSH(string& key, string& value);
    string HGET(string& key);
    void HDEL(string& key);
    void HREAD();

    void HDestroyTable(NodeHash* node);
    ~HashTable();
};

HashTable::~HashTable() {
    for (int i = 0; i < size; i++) {
        HDestroyTable(table[i]);
    }
    delete[] table;
}

void ProcessingExpression(const string& oper, Stack& stackOper, Stack& stackNumb, string current);
void findSumsSet(SetNode& set, int index, int currentSum, string currentElements, SetNode& sums);
void FindSubsets(SetNode& set);

