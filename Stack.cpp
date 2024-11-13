#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include "header.h"


void Stack::Clear() {
    while (head != nullptr) {
        SingleNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}
void Stack::SPUSH(string& cell) {
    SingleNode* node = new SingleNode;
    node->cell = cell;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }
}
void Stack::SPOP() {
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }
    SingleNode* current = head;

    while (current->next != tail) {
        current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
}
void Stack::SREAD() {
    SingleNode* current = head;
    cout << endl;
    while (current != nullptr) {
        cout << current->cell << " ";
        current = current->next;
    }
    cout << endl;
}

void ProcessingExpression(const string& oper, Stack &stackOper, Stack& stackNumb, string current) {
    stackOper.SPOP();
    int A = stoi(stackNumb.head->cell);
    int B = stoi(stackNumb.head->next->cell);
    stackNumb.SPOP();
    stackNumb.SPOP();
    int result;
    if (oper == "*") result = A * B;
    if (oper == "+") result = A + B;
    if (oper == "-") result = A - B;
    string temp = to_string(result);
    stackNumb.SPUSH(temp);
    stackOper.SPUSH(current);
}