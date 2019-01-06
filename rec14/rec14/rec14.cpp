//
//  rec14.cpp
//  rec14
//
//  Created by Kevin J. Zheng on 12/13/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {};
    int data;
    Node* next;
};

// Task 1
bool evenBin(int num) {
    if (num == 0) {
        return true;
    }
    else if (num == 1) {
        return false;
    }
    if (num % 2 == 0) {
        return evenBin(num / 2);
    }
    return !evenBin(num / 2);
}

// Task 2
Node* combLists(const Node* lst1, const Node* lst2) {
    Node* newNode = nullptr;
    if (lst1 == nullptr && lst2 == nullptr) {
        return nullptr;
    }
    else if (lst1 != nullptr && lst2 == nullptr) {
        newNode = new Node(lst1->data);
        newNode->next = combLists(lst1->next, lst2);
        return newNode;
    }
    else if (lst1 == nullptr && lst2 != nullptr) {
        newNode = new Node(lst2->data);
        newNode->next = combLists(lst1, lst2->next);
        return newNode;
    }
    newNode = new Node(lst1->data+lst2->data);
    newNode->next = combLists(lst1->next, lst2->next);
    return newNode;
}

void printList(Node* currNode) {
    while (currNode != nullptr) {
        cout << currNode->data << ' ';
        currNode = currNode->next;
    }
    cout << endl;
}

// Task 3
int maxBinTree(TNode* root) {
    if (root == nullptr) {
        throw invalid_argument("Passed empty tree!");
    }
    // Provide this code
    if (root->right == nullptr && root->left == nullptr) {
        return root->data;
    }
    else if(root->right == nullptr && root->left != nullptr) {
        return max(maxBinTree(root->left), root->data);
    }
    else if(root->right != nullptr && root->left == nullptr) {
        return max(maxBinTree(root->right), root->data);
    }
    return max(root->data,(max(maxBinTree(root->right), maxBinTree(root->left))));
}

// Task 4
bool palindrome(char* arr, int length) {
//    cout << arr << endl;
    if (length <= 1) {
        return true;
    }
    else {
        if (arr[0] != arr[length-1]) {
            return false;
        }
        return palindrome(++arr, length-2);
    }
//    if (length <= 1) {
//        return true;
//    }
//    else {
//        if (arr[0] != arr[--length]) {
//            return false;
//        }
//        return palindrome(++arr, --length);
//    }
}

// Task 5
int tower(int count, char start, char target, char spare) {
    if (count == 0) {
        return 0;
    }
    else {  //if (count > 0) {
        int move1 = tower(count - 1, start, spare, target);
        int move2 = tower(count - 1, spare, target, start);
        count = move1 + move2 + 1;
    }
    return count;
}

// Task 6
void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}

int main() {
    // Task 1
    cout << boolalpha << evenBin(24) << endl;   // 11000
    cout << boolalpha << evenBin(3) << endl;    // 11
    cout << boolalpha << evenBin(2) << endl;    // 10
    cout << boolalpha << evenBin(11) << endl;    // 1011
    
    // Task 2
    Node* lst1 = nullptr;
    lst1 = new Node(1);
    lst1->next = new Node(2);
    Node* lst2 = nullptr;
    lst2 = new Node(2);
    lst2->next = new Node(3);
    lst2->next->next = new Node(4);
    printList(combLists(lst1, lst2));
    

    // Task 3
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    try {
        cout << maxBinTree(&f) << endl;
        cout << maxBinTree(nullptr) << endl;
    }
    catch (invalid_argument ex){
        cerr << "Caught an exception: " << ex.what() << endl;
    }

    // Task 4
    char s[] = "racecar";
    if (palindrome(s, 7)) { cout << "Yes!\n"; }
    char dog[] = "dog";
    if (palindrome(dog, 3)) { cout << "Yes!\n"; }
    else { cout << "No!\n"; }
    char noon[] = "noon";
    if (palindrome(noon, 4)) { cout << "Yes!\n"; }
    
    // Task 5
    cout << tower(1,'a','b','c') << endl;
    cout << tower(2,'a','b','c') << endl;
    cout << tower(3,'a','b','c') << endl;
    cout << tower(4,'a','b','c') << endl;
    cout << tower(5,'a','b','c') << endl;
    cout << tower(6,'a','b','c') << endl;
    cout << tower(7,'a','b','c') << endl;
    
    // Task 6
//    void mystery(int n) {
//        if (n > 1) {
//            cout << 'a';
//            mystery(n/2);
//            cout << 'b';
//            mystery(n/2);
//        }
//        cout << 'c';
//    }
    // n = 1
    // c
    // n = 2
    // acbcc
    // n = 3
    // acbcc
    // n = 4
    // aacbccbacbcc
    // n = 5
    // 
    // n = 6
    //
    // n = 7
    //
    // n = 8
    //
    // n = 9
    //
    // n = 10
    
}



