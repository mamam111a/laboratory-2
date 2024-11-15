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
    size = 0;
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
    size++;
}
void Stack::SPOP() {
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        size--;
        return;
    }
    SingleNode* current = head;

    while (current->next != tail) {
        current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
    size--;
}
void Stack::DeleteHead() {
    if (head == nullptr) {
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    }
    else {
        SingleNode* temp = head;
        head = head->next;
        delete temp;
    }
    size--;
}
void Stack::AddHead(string& cell) {
    SingleNode* node = new SingleNode;
    node->cell = cell;
    node->next = head;

    head = node;
    if (tail == nullptr) {
        tail = node;
    }
    size++;
}
void Stack::DeleteElement(SingleNode* target) {
    if (head == nullptr) {
        return;
    }
    if (head == target) {
        size--;
        DeleteHead();
        return;
    }

    SingleNode* current = head;
    while (current != nullptr && current->next != target) {
        current = current->next;
    }
    if (current != nullptr && current->next == target) {
        SingleNode* temp = current->next;
        if (current->next != nullptr) {
            current->next = current->next->next;
        }
        else {
            current->next = nullptr;
        }

        delete temp;
    }
    size--;
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

void ProcessingExpression(const string& oper, Stack& stackOper, Stack& stackNumb, string current, bool parameter) {

    stackOper.SPOP();
    int A = 0;
    int B = stoi(stackNumb.tail->cell);
    stackNumb.SPOP();
    if (parameter == 1) {
        A = stoi(stackNumb.tail->cell);
        A = A * (-1);
    }
    else {
        A = stoi(stackNumb.tail->cell);
    }

    stackNumb.SPOP();

    int result;
    if (oper == "*") result = A * B;
    if (oper == "+") result = A + B;
    if (oper == "-") result = A - B;
    if (result < 0 && parameter == 1) {
        result = result * (-1);
    }
    string temp = to_string(result);
    stackNumb.SPUSH(temp);
    stackOper.SPUSH(current);

}
