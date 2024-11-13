
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
                    if (prev != "oper" && prev != "") {
                        isWrong = true;
                        break;
                    }
                    prev = "bracket";
                    countBrackets++;

                }
                else if (part == ")") {
                    if (prev != "number") {
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
                else if (isdigit(part.at(0))) {
                    if (part.at(0) == '0') {
                        isWrong = true;
                        break;
                    }
                    int i = 0;
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
                if (isdigit(current.at(0))) {
                    stackNumb.SPUSH(current);
                }
                else if (current == "+" || current == "-" || current == "*") {
                    if (stackOper.tail == nullptr) {
                        stackOper.SPUSH(current);
                        continue;
                    }
                    
                    if (current == "+" || current == "-") {//
                        if (stackOper.tail->cell == "*") {
                            ProcessingExpression("*", stackOper, stackNumb, current);
                        }
                        else {
                            if (stackOper.tail->cell == "+") {
                                ProcessingExpression("+", stackOper, stackNumb, current);
                            }
                            else if (stackOper.tail->cell == "-") {
                                ProcessingExpression("-", stackOper, stackNumb, current);
                            }
                            else {
                                stackOper.SPUSH(current);
                                continue;
                            }
                        }
                    }
                    else if (current == "*") {
                        if (stackOper.tail->cell == "*") {
                            ProcessingExpression("*", stackOper, stackNumb, current);
                        }
                        else {
                            stackOper.SPUSH(current);
                        }
                    }
                    
                }
                else if (current == "(") {
                    stackOper.SPUSH(current);
                }
                else {
                    while (stackOper.tail->cell != "(") {
                        string tempOper = stackOper.tail->cell;
                        int B = stoi(stackNumb.tail->cell);
                        stackNumb.SPOP();
                        int A = stoi(stackNumb.tail->cell);
                        stackNumb.SPOP();

                        int result = 0;
                        if (tempOper == "*")  result = A * B;
                        else if (tempOper == "+") result = A + B;
                        else if (tempOper == "-") result = A - B;
                        
                        string temp = to_string(result);
                        stackNumb.SPUSH(temp);
                        stackOper.SPOP();
                    }
                    stackOper.SPOP();
                }
            }
            while (stackOper.head != nullptr) {
                string oper = stackOper.tail->cell;
                stackOper.SPOP();

                int b = stoi(stackNumb.tail->cell);
                stackNumb.SPOP();
                int a = stoi(stackNumb.tail->cell);
                stackNumb.SPOP();

                int result;
                if (oper == "+") result = a + b;
                else if (oper == "-") result = a - b;
                else if (oper == "*") result = a * b;

                string resultStr = to_string(result);
                stackNumb.SPUSH(resultStr);
            }
            cout << endl << "RESULT: " << stackNumb.tail->cell << endl;

        }
        else if (numberTask == "2") {
            string command;
            string commandWord;
            cout << endl << "Enter the command -->> ";
            cin.ignore();
            getline(cin,command);
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
            while (getline(ss,temp, ' ')) {
                set.SETADD(temp);
            }
            FindSubsets(set);
        }
        else if(numberTask == "4") {
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
            array.FindSumsArray(array, 0, 0, "", sum, sums);
            Array duplicates;
            for (int i = 0; i < sums.size; i++) {
                Array sorted;
                stringstream sss(sums.data[i]);
                string token;
                while (getline(sss, token, ' ')) {
                    sorted.MPUSHend(token);
                }
                sort(sorted.data, sorted.data + sorted.size, [](const std::string& a, const std::string& b) {
                    return stoi(a) < stoi(b);
                    });
                string temp = "";
                for (int i = 0; i < sorted.size; i++) {
                    if (i == sorted.size - 1) {
                        temp += sorted.data[i];
                    }
                    else {
                        temp += sorted.data[i] + " ";
                    }
                    
                }
                duplicates.MPUSHend(temp);
                duplicates.RemoveDuplicates();

            }
            duplicates.MREAD();
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
        else {
            cout << endl << "INCORRECT INPUT!!!" << endl;
            continue;
        }
    }
}