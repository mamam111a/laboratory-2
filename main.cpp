
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include "header.h"

#include "HashTable.cpp"
#include "Tree.cpp"
#include "Array.cpp"
#include "Set.cpp"
#include "Stack.cpp"

int main()
{
    cout << endl << "HELLO!" << endl;
    while (true) {

        Stack stackOper;
        Stack stackNumb;
        SetNode set(15);
        Array array;
        Tree tree;
        cout << endl << "Select a task option -->> ";
        string numberTask;
        cin >> numberTask;

        if (numberTask == "EXIT") {
            cout << endl << "GOOD BYE!!!" << endl;
            break;
        }
        else if (numberTask == "1") {
            cout << endl << "LETS GO -->> ";
            cin.ignore();
            string expression;

            getline(cin, expression);
            string expressionTemp = expression;
            stringstream ss(expression);
            string part;
            int countBrackets = 0;;
            int countOperators = 0;
            int countNumbers = 0;

            bool isWrong = false;
            string prev = "";
            while (getline(ss, part, ' ')) {
                if (part == "(") {
                    if (prev != "oper" && prev != "" && prev != "bracket") {
                        isWrong = true;
                        break;
                    }
                    prev = "bracket";
                    countBrackets++;

                }
                else if (part == ")") {
                    if (prev != "number" && prev != "bracket") {
                        isWrong = true;
                        break;
                    }
                    prev = "bracket";
                    countBrackets++;
                }
                else if (part == "+" || part == "-" || part == "*") {

                    if (prev != "number" && prev != "bracket") {
                        isWrong = true;
                        break;
                    }
                    prev = "oper";
                    countOperators++;

                }
                else if (isdigit(part.at(0)) || part.at(0) == '-') {
                    if (part.at(0) == '0') {
                        isWrong = true;
                        break;
                    }
                    int i = 1;
                    while (i != part.size()) {
                        if (isdigit(part.at(i)) == false) {
                            isWrong = true;
                            break;
                        }
                        i++;
                    }
                    if (prev != "oper" && prev != "bracket") {
                        if (prev != "") {
                            isWrong = true;
                            break;
                        }
                    }
                    prev = "number";
                    countNumbers++;
                }

                else {
                    isWrong = true;
                    break;
                }
            }
            if (isWrong) {
                cout << endl << "Incorrect input!!!" << endl;
                continue;
            }
            if (countBrackets % 2 != 0 || countNumbers - countOperators != 1) {
                cout << endl << "Incorrect input!!!" << endl;
                continue;
            }
            stringstream sss(expressionTemp);
            string current = "";

            while (getline(sss, current, ' ')) {
                if (current == "+" || current == "-" || current == "*") {
                    if (stackOper.tail == nullptr) {
                        stackOper.AddTail(current);
                        continue;
                    }
                    if (current == "+" || current == "-") {
                        if (stackOper.tail->cell == "*") {
                            ProcessingExpression("*", stackOper, stackNumb, current, 0);
                        }
                        else {
                            if (stackOper.tail->cell == "+" && current == "+") {
                                ProcessingExpression("+", stackOper, stackNumb, current, 0);
                            }
                            else {
                                stackOper.AddTail(current);
                                continue;
                            }
                        }
                    }
                    else if (current == "*") {
                        if (stackOper.tail->cell == "*") {
                            ProcessingExpression("*", stackOper, stackNumb, current, 0);
                        }
                        else {
                            stackOper.AddTail(current);
                        }
                    }

                }

                else if (current == "(") {
                    stackOper.AddTail(current);
                }
                else if (current.at(0) == '-') {
                    if (stackOper.tail != nullptr) {
                        if (stackOper.tail->cell == "-") {
                            int temp = stoi(current);
                            temp = temp * (-1);
                            string strTemp = to_string(temp);
                            stackNumb.AddTail(strTemp);
                            stackOper.tail->cell = "+";
                        }
                    }
                    stackNumb.AddTail(current);
                    continue;
                }
                else if (isdigit(current.at(0))) {
                    if (stackOper.tail != nullptr) {
                        if (stackOper.tail->cell == "-") {
                            int temp = stoi(current);
                            temp = temp * (-1);
                            string strTemp = to_string(temp);
                            stackNumb.AddTail(strTemp);
                            stackOper.tail->cell = "+";
                        }
                        else {
                            stackNumb.AddTail(current);
                        }
                    }
                    else {
                        stackNumb.AddTail(current);
                    }
                }
                else {
                    while (stackOper.tail->cell != "(") { 
                        string tempOper = stackOper.tail->cell;
                        int B = stoi(stackNumb.tail->cell);
                        stackNumb.DeleteTail();
                        int A = stoi(stackNumb.tail->cell);
                        stackNumb.DeleteTail();

                        int result = 0;
                        if (tempOper == "*")  result = A * B;
                        else if (tempOper == "+") result = A + B;
                        else if (tempOper == "-") result = A - B;

                        string temp = to_string(result);
                        stackNumb.AddTail(temp);

                        stackOper.DeleteTail();
                    }
                    stackOper.DeleteTail();

                    if (stackOper.tail != nullptr) {
                        if (stackOper.tail->cell == "-") {
                            int temp = stoi(stackNumb.tail->cell);
                            temp = temp * (-1);
                            string strTemp = to_string(temp);
                            stackNumb.tail->cell = strTemp;
                            stackOper.tail->cell = "+";
                        }
                    }

                }
            }

            while (stackOper.head != nullptr) {
                if (stackOper.head->next != nullptr) {
                    if ((stackOper.head->cell == "-" && stackOper.head->next->cell == "*") || (
                        (stackOper.head->cell == "+" && stackOper.head->next->cell == "*"))) {
                        string oper = stackOper.head->next->cell;

                        int b = stoi(stackNumb.head->next->next->cell);
                        int a = stoi(stackNumb.head->next->cell);

                        int result;
                        result = a * b;
                        string resultStr = to_string(result);

                        stackNumb.DelElementValue(stackNumb.head->next);
                        stackOper.DelElementValue(stackOper.head->next);

                        stackNumb.head->next->cell = resultStr;

                    }
                }
                string oper = stackOper.head->cell;
                stackOper.SPOP();

                int b = stoi(stackNumb.head->next->cell);
                int a = stoi(stackNumb.head->cell);
                stackNumb.SPOP();
                stackNumb.SPOP();

                int result;
                if (oper == "+") result = a + b;
                else if (oper == "-") result = a - b;
                else if (oper == "*") result = a * b;

                string resultStr = to_string(result);
                stackNumb.SPUSH(resultStr);//////////

            }
            cout << endl << "RESULT: " << stackNumb.tail->cell << endl;

        }
        else if (numberTask == "2") {
            string command;
            string commandWord;
            cout << endl << "Enter the command -->> ";
            cin.ignore();
            getline(cin, command);
            stringstream ss(command);
            string fileName;
            string element;
            ss >> commandWord;
            ss >> fileName;
            ss >> element;

            ifstream FileRead(fileName + ".txt");
            string token;
            while (getline(FileRead, token, ' ')) {
                set.SETADD(token);
            }
            FileRead.close();
            if (commandWord == "SETADD") {
                set.SETADD(element);
            }
            else if (commandWord == "SETDEL") {
                set.SETDEL(element);
            }
            else if (commandWord == "SET_AT") {
                set.SET_AT(element);
                continue;
            }
            else {
                cout << endl << "INCORRECT INPUT!!!" << endl;
                continue;
            }
            ofstream FileWrite(fileName + ".txt");
            for (int i = 0; i < set.size; i++) {
                if (set.plenty[i] != nullptr && !set.plenty[i]->value.empty()) {
                    FileWrite << set.plenty[i]->value << " ";
                }
            }
            FileWrite.close();
        }
        else if (numberTask == "3") {

            cout << endl << "WARNING!!! The set should not contain duplicate elements!!!" << endl;
            cout << endl << "LETS GO -->> ";
            cin.ignore();
            string elements;
            getline(cin, elements);
            string temp;
            stringstream ss(elements);
            while (getline(ss, temp, ' ')) {
                set.SETADD(temp);
            }
            FindSubsets(set);
        }
        else if (numberTask == "4") {
            cout << endl << "LETS GO -->> ";
            cin.ignore();
            string elements;
            string sumStr;
            getline(cin, elements);
            string temp;
            stringstream ss(elements);
            cout << endl << "Sum -> ";
            cin >> sumStr;
            int sum = stoi(sumStr);
            while (getline(ss, temp, ' ')) {
                array.MPUSHend(temp);
            }
            cout << endl;
            Array sums;
            for(int i = 0; i < array.size; i++) {
                string subArray = array.data[i];
                string tempArray1;
                stringstream ss1(subArray);
                int sumValues1 = 0;
                while(getline(ss1, tempArray1, ' ')) {
                        sumValues1 += stoi(tempArray1);
                    }
                if(sumValues1 == sum) {
                    sums.MPUSHend(subArray);
                }
                for(int j = i+1; j < array.size; j++) {
                    subArray+= " " + array.data[j];
                    string tempArray2;
                    stringstream ss2 (subArray);
                    int sumValues2 = 0;
                    while(getline(ss2, tempArray2, ' ')) {
                        sumValues2 += stoi(tempArray2);
                    }
                    if(sumValues2 == sum) {
                        sums.MPUSHend(subArray);
                    }
                }

            }
            sums.MREAD();
            
        }
        else if (numberTask == "5") {
            tree.Insert(15);
            tree.Insert(17);
            tree.Insert(23);
            tree.Insert(13);
            tree.Insert(19);
            tree.Insert(135);
            tree.Insert(5);
            tree.Print("", tree.root, false);
            int key;
            cout << endl << "Choose the element to delete -->> ";
            cin.ignore();
            cin >> key;
            tree.DeleteNode(tree.root, key);
            cout << endl;
            tree.Print("", tree.root, false);
        }
        else if (numberTask == "6") {
            string elements;
            string strA;
            string strB;
            cout << endl << "LETS GO -->> ";
            cin >> strA >> strB;
            if (isIsomorphic(strA, strB)) {
                cout << endl << "They are isomorphic!!!" << endl;
            }
            else {
                cout << endl << "They are NOT isomorphic!!!" << endl;
            }
        }
        else if (numberTask == "EXIT") {
            cout << endl << "GOOD BYE!!!" << endl;
            return 0;
        }
        else {
            cout << endl << "INCORRECT INPUT!!!" << endl;
            continue;
        }
    }
}
