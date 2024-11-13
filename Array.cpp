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
        if(i != size - 1)
        cout << "[ " << data[i] << " ]" << endl;
    }
    cout << endl;
}


void Array::FindSumsArray(Array& arr, int index, int currentSum, string currentElements, int targetSum, Array& sums) {
    if (index == arr.size) {
        if (currentSum == targetSum) {
            sums.MPUSHend(currentElements);
        }
        return;
    }

    FindSumsArray(arr, index + 1, currentSum, currentElements, targetSum, sums);

    FindSumsArray(arr, index + 1, currentSum + stoi(arr.data[index]), currentElements + (currentElements.empty() ? "" : " ") + arr.data[index], targetSum, sums);
}
void Array::RemoveDuplicates() {
    int newSize = 0;

    for (int i = 0; i < size; ++i) {
        bool isDuplicate = false;

        for (int j = 0; j < newSize; ++j) {
            if (data[i] == data[j]) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            data[newSize] = data[i];
            newSize++;
        }
    }
    size = newSize;
}