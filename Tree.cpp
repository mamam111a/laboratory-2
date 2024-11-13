#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include "header.h"

void Tree::Destroy(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    Destroy(node->left);
    Destroy(node->right);
    delete node;
}


TreeNode* Tree::FindMin(TreeNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

void Tree::Insert(int value) {
    root = InsertRecursive(root, value);
}

TreeNode* Tree::InsertRecursive(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }

    if (value < node->value) {
        node->left = InsertRecursive(node->left, value);
    }
    else if (value > node->value) {
        node->right = InsertRecursive(node->right, value);
    }
    return node;
}


TreeNode* Tree::DeleteNode(TreeNode* root, int key) {
    if (!root) {
        return root;
    }
    // идем влево
    if (key < root->value) {
        root->left = DeleteNode(root->left, key);
    }
    // идем вправо
    else if (key > root->value) {
        root->right = DeleteNode(root->right, key);
    }
    else {// найден узел для удаления
        
        // нет правого поддерева
        if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // нет левого поддерева
        else if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        // есть оба поддерева
        else {
            TreeNode* temp = FindMin(root->right); //находим мин узел в правом поддереве
            root->value = temp->value; //копируем его значение и удаляем
            root->right = DeleteNode(root->right, temp->value);
        }
    }
    return root;
}



void Tree::Print(const string& prefix,TreeNode* node, bool isLeft) {
    if (node != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "L--");

        cout << node->value << endl;

        Print(prefix + (isLeft ? "|   " : "    "), node->right, true);
        Print(prefix + (isLeft ? "|   " : "    "), node->left, false);
    }
}