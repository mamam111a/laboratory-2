#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
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
bool SetNode::FindValue(string value, int &result) {
    int index = HashSet(value);  
    int newIndex = index; 

    for (int i = 0; i < size; i++) {
        if (plenty[index] == nullptr) {// элемент не найден
            result = -1;  
            return false;
        }
        if (plenty[index]->value == value) { //найден
            result = index;
            return true;
        }

        // если не найден, пробуем следующую ячейку с помощью второй хеш-функции
        index = (newIndex + i * HashSet(value)) % size;
    }

    result = -1;
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
        for (int i = 1; i < size; i++) {
            // Используем метод пробирования с другой хеш-функцией или методом
            int newIndex = (index + i * HashSet(value)) % size;  // Пробирование с шагом через вторичную хеш-функцию
            
            if (plenty[newIndex] == nullptr) {
                plenty[newIndex] = new Set{value};  
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


void findSumsSet(SetNode& set, int index, int currentSum, string currentElements, SetNode& sums) { // 2^10 - 1 (пустое множество)
    // Если мы дошли до конца множества
    if (index == set.size) {

        if (sums.plenty[currentSum] == nullptr) {
            sums.SETADD(currentElements);
            //cout << endl << "Sum: " << currentSum << " Elements: " << currentElements;
        }
        else {
            sums.SETADD(currentElements);
            //cout << endl << "Sum: " << currentSum << " Elements: " << currentElements;
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
    totalSum = totalSum/2;
    SetNode values(1000);
    stringstream ss(allElements);
    string token;
    while (getline(ss, token, ' ')) {
        values.SETADD(token);
    }
    int i = 0;
    SetNode sums(1000);
    findSumsSet(set, 0, 0, "", sums); //поиск всех вариаций сумм

    /*
    for (int i = 0; i < sums.size; i++) {
        if (sums.plenty[i] != nullptr && !sums.plenty[i]->value.empty()) {
            cout << "\t" << i << "\t" << sums.plenty[i]->value << endl;
        }
    }
    */
    int minSum = pow(10,9);
    ;
    SetNode sumVariants(1000);
    for (int i = 0; i < sums.size; i++) {
        if (sums.plenty[i] != nullptr && !sums.plenty[i]->value.empty()) {
            stringstream tempSS1(sums.plenty[i]->value);
            string tempToken;
            int tempSum = 0;
            while(getline(tempSS1, tempToken, ' ')) {
                tempSum+= stoi(tempToken);
            }
            if (abs(totalSum - tempSum) <= minSum) {  // -i так как мы ищем близость к общей сумме всех элементов,
                string tempNumbers;        // а i это ключ - сумма, где value это список элементов этой суммы
                stringstream tempSS2(sums.plenty[i]->value);
                int countNumbers = 0;
                while(getline(tempSS2, tempNumbers, ' ')) {
                    countNumbers++;
                }
                minSum = abs(totalSum - tempSum); 
                if (countNumbers != countElements) {
                    if ((totalSum-tempSum )== minSum) {
                    sumVariants.SETADD(sums.plenty[i]->value);
                    }
                }
                
            }  
        }
        else {
            continue;
        }
    }
    string subsetA = "";
    string subsetB = "";
    int minDiff = pow(10,9);    
    int sumA = 0;
    int sumB = 0;

    string finalSubSetA = "";
    string finalSubSetB = "";
    int finalDifference = 0;
    for(int i = 0; i < sumVariants.size; i++) {
        sumB = 0;
        sumA = 0;
        subsetB = "";
        if(sumVariants.plenty[i] != nullptr && !sumVariants.plenty[i]->value.empty()) {

            subsetA = sumVariants.plenty[i]->value;
            stringstream ssA(subsetA);
            string tokenA;

            while (getline(ssA, tokenA, ' ')) {
                if (tokenA != "") {
                    sumA += stoi(tokenA);
                }  
            }
            for (int i = 0; i < values.size; i++) {
                if (values.plenty[i] != nullptr && !values.plenty[i]->value.empty()) {
                    if (subsetA.find(values.plenty[i]->value) == string::npos) {
                        subsetB += " " + values.plenty[i]->value;
                        sumB += stoi(values.plenty[i]->value);
                    }
                }
            }
            if(abs(sumA-sumB) < minDiff) {
                finalSubSetA = subsetA;
                finalSubSetB = subsetB;
                finalDifference = abs(sumA-sumB);
                minDiff = abs(sumA-sumB);
            }
        }
        
    }

    cout << endl << "The maximum amount difference: " << finalDifference << endl;
    cout << endl << "The first subset: " << finalSubSetA << endl;
    cout << endl << "The second subset: " << finalSubSetB << endl;
}

