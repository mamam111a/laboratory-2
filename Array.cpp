#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include "header.h"


void Array::MPUSHend(string& value) {
    data[size++] = value;
}

void Array::MPUSHindex(const int& index, string& value) {
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value + " ";
    size++;
}

string Array::MGETL(const int& index) {
    return data[index];
}

void Array::MDEL(const int& index) {
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

void Array::MREPL(const int& index, string& value) {
    data[index] = " " + value + " ";
}

int Array::MSIZE() {
    return size;
}

void Array::MREAD() {
    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << "[ " << data[i] << " ]" << endl;
    }
    cout << endl;
}
