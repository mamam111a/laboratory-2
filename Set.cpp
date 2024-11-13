#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include "header.h"



int SetNode::HashSet(string itemKey) {
    int result = 0;
    for (char i : itemKey) {
        result += static_cast<int>(i);
    }
    return abs(result) % size;
}

bool SetNode::isFull() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (plenty[i] != nullptr) {
            count++;
        }
    }
    return count >= size;
}
bool SetNode::FindValue(string value, int& znach) {
    int index = HashSet(value);
    for (int i = 0; i < size; i++) {
        if (plenty[i] == nullptr) {
            return false; 
        }
        if (plenty[i]->value == value) {
            znach = i;
            return true;
        }
    }
    return false;
}

void SetNode::SETADD(string value) {
    int index = HashSet(value);
    // наличие уже ТАКОГО же значения
    if (plenty[index] != nullptr && plenty[index]->value == value) {
        return;
    }
    // наличие уже ТАКОГО ключа, если колизия его передвинула
    int result = 0;
    bool isExist = FindValue(value, result);
    if (isExist) {
        return;
    }
    if (isFull()) {
        cout << endl << "The set is crowded!!!" << endl;
        return;
    }
    //если есть место - используем
    if (plenty[index] == nullptr) {
        plenty[index] = new Set{value}; 
    }
    else { //иначе ищем другое свободное место
        for (int i = 0; i < size; i++) {
            if (plenty[i] == nullptr) {
                plenty[i] = new Set{ value }; 
                break;
            }
        }
    }
}
void SetNode::SETDEL(string value) {
    int index = HashSet(value);
    if (plenty[index] == nullptr) {
        cout << endl << "The element does not exist!!!" << endl;
        return;
    }
    if (plenty[index]->value == value) { //Если было без коллизий
        delete plenty[index];
        plenty[index] = nullptr;
        return;
    }

    bool isExist = FindValue(value, index);
    if (isExist) {
        delete plenty[index];
        plenty[index] = nullptr;
        return;
    }
}

void SetNode::SET_AT(string value) {

    int index = HashSet(value);
    if (plenty[index] == nullptr) {
        cout << endl << "The element was not found!" << endl;
        return;
    }
    if (plenty[index]->value == value) { //Если было без коллизий
        cout << endl << "The element was found!!!" << endl;
        return;
    }
    bool isExist = FindValue(value, index);
    if (isExist) {
        cout << endl << "The element was found!!!" << endl;
        return;
    }
    
}



void findSumsSet(SetNode& set, int index, int currentSum, string currentElements, SetNode& sums) {
    // Если мы дошли до конца множества
    if (index == set.size) {

        if (sums.plenty[currentSum] == nullptr) {
            sums.plenty[currentSum] = new Set{ currentElements };
        }
        else {
            sums.plenty[currentSum]->value = (currentElements.empty() ? "" : " ") + currentElements;
        }
        return;
    }

    findSumsSet(set, index + 1, currentSum, currentElements, sums);

    if (set.plenty[index] != nullptr) {
        findSumsSet(set, index + 1, currentSum + stoi(set.plenty[index]->value), currentElements + (currentElements.empty() ? "" : " ") + set.plenty[index]->value, sums);
    }
}
void FindSubsets(SetNode& set) {

    int countElements = 0;
    int totalSum = 0;

    string allElements = "";
    for (int i = 0; i < set.size; i++) {
        string valueStr = "";
        if (set.plenty[i] != nullptr) {
            valueStr = set.plenty[i]->value;
            int value = stoi(valueStr);
            totalSum += value;
            allElements += " " + valueStr;
            countElements++;
        }
    }
    SetNode values(countElements + 1);
    stringstream ss(allElements);
    string token;
    while (getline(ss, token, ' ')) {
        values.SETADD(token);
    }
    int i = 0;
    SetNode sums(1000);
    findSumsSet(set, 0, 0, "", sums);

    /*
    for (int i = 0; i < sums.size; i++) {
        if (sums.plenty[i] != nullptr && !sums.plenty[i]->value.empty()) {
            cout << "\t" << i << "\t" << sums.plenty[i]->value << endl;
        }
    }
    */
    int maxRightSum = -1;
    string subsetA = "";
    for (int i = 0; i < sums.size; i++) {
        if (sums.plenty[i] != nullptr && !sums.plenty[i]->value.empty()) {
            if ((totalSum - i) > maxRightSum) {
                maxRightSum = i;
                subsetA = sums.plenty[i]->value;
            }  
        }
        else {
            continue;
        }
    }
    string subsetB = "";
    for (int i = 0; i < values.size; i++) {
        if (values.plenty[i] != nullptr && !values.plenty[i]->value.empty()) {
            if (subsetA.find(values.plenty[i]->value) == string::npos) {
                subsetB += " " + values.plenty[i]->value;
            }
        }
    }
    int sumA = 0;
    int sumB = 0;
    stringstream ssA(subsetA);
    stringstream ssB(subsetB);
    string tokenA;
    string tokenB;
    while (getline(ssA, tokenA, ' ')) {
        if (tokenA != "") {
            sumA += stoi(tokenA);
        }  
    }
    while (getline(ssB, tokenB, ' ')) {
        if (tokenB != "") {
            sumB += stoi(tokenB);
        }
    }
    cout << endl << "The maximum amount difference: " << abs(sumA - sumB) << endl;
    cout << endl << "The first subset: " << subsetA << endl;
    cout << endl << "The second subset: " << subsetB << endl;
}

