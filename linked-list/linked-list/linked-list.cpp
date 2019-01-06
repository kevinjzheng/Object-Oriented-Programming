//
//  linked-list.cpp
//  linked-list
//
//  Created by Kevin J. Zheng on 11/14/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
using namespace std;

//class Node {
//public:
//    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
//
//    //accesors
//    int getData() const { return data; }
//    Node* getNext() { return next; }
//
//    //mutators
//    void setData(int data) {this->data = data; }
//    void setNext(Node* next) { this->next = next; }
//
//private:
//    int data;
//    Node* next;
//};

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

/* if you want to change the address of the pointer, you must pass by reference
 in order to change the address of the ptr */
/* we will never be passing in a node object, we will be passing a node* address */

Node* listDuplicate(Node* headPtr) {
    if (headPtr == nullptr) {
        return nullptr;
    }
    Node* result = new Node(headPtr->data);
    Node* last = result;
    Node* p = headPtr->next;
    
//    you don't need length of linked list to for loop thru the list
//    for (Node* p = headPtr->next; p != nullptr; p = p->next) {
//        last->next = new Node(p->data);
//        p = p->next;
//        last = last->next;
//    }
    
    while (p != nullptr) {
        last->next = new Node(p->data);
        p = p->next;
        last = last->next;
    }
    return result;
}

// recursion is expensive, space-wise, each recursive call is on the call stack
Node* listDuplicateR(Node* headPtr) {
//    Node* rest = listDuplicateR(headPtr->next);
//    Node* result = new Node(headPtr->data,rest);
//    return result;
    if (headPtr == nullptr) return nullptr;
    return new Node(headPtr->data, listDuplicateR(headPtr->next));
}

void listAddHead(Node*& headPtr, int data) {
//    Node* p = new Node(data,headPtr);
//    headPtr = p;
    headPtr = new Node(data, headPtr);
}

void listDisplay(const Node* headPtr) {
    const Node* p = headPtr;
    while (p != nullptr) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

int listLength(const Node* headPtr) {
    int count = 0;
    const Node* p = headPtr;
    while (p != nullptr) {
        ++count;
        p = p->next;
    }
    return count;
}

bool listRemoveHead(const Node*& headPtr) {
    if (headPtr == nullptr) {
        return false;
    }
    else {
        // Remember where the
        const Node* first = headPtr;
        // Have the head point to the old second node
        headPtr = headPtr->next;
        // Free up the old first node
        delete first;
        return true;
    }
}

void listRemoveAfter(Node* prior) {
    Node* target = prior->next;
    
    // Connect prior to node after the target
//    prior->next = target->next;
    prior->next = prior->next->next;
    
    // Free up
    delete target;
}

void listAddAfter(Node* prior, int data) {
    prior->next = new Node(data,prior->next);
}

void listClear(Node*& headPtr) {
    if (headPtr == nullptr) return;
    Node* next = headPtr->next;
    
    while (next != nullptr) {
        delete headPtr;
        headPtr = next;
        next = next->next;
    }
    delete headPtr;
    // hands headPtr a garbage address
    headPtr = nullptr;  // we have to do this for safety purposes
}

int main () {
    Node* myList = nullptr;
    myList = new Node(17);
    myList->next = new Node(28);
    
//    cout << myList->data << " " << myList->next->data << endl;
    listDisplay(myList);
    
    Node* another = listDuplicate(myList);
    listDisplay(another);
    
    Node* recursion = listDuplicateR(myList);
    listDisplay(recursion);
}
