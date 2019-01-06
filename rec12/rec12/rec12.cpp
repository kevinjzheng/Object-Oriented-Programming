//
//  rec12.cpp
//  rec12
//
//  Created by Kevin J. Zheng on 11/29/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class Node;

//class Iterator {
//    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
//        return &lhs != &rhs;
//    }
//public:
//    Iterator(Node* p) : where(p) {}
//    Iterator& operator++() {
////        ++where;
//        return *this;
//    }
//    Iterator& operator--() {
////        ++where;
//        return *this;
//    }
//    Node operator*() const {
//        return where->data;
//    }
//    Node& operator*() {
//        return *where;
//    }
//private:
//    Node* where;
//};

class List {
    friend ostream& operator<<(ostream& os, const List& rhs) {
        Node* currNode = rhs.header->next;
        while (currNode != rhs.trailer) {
            os << currNode->data << ' ';
            currNode = currNode->next;
        }
        return os;
    }
private:
    size_t length;
    struct Node {
        Node(int data = 0, Node* next = nullptr, Node* prior = nullptr) :
        data(data), next(next), prior(prior) { }
        int data;
        Node* next;
        Node* prior;
    };
    Node* header;
    Node* trailer;
public:
    class Iterator {
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.where != rhs.where;
        }
        friend class List;
    public:
        Iterator(Node* node) : where(node) {}
        Iterator& operator++() {
            where = where->next;
            return *this;
        }
        Iterator& operator--() {
            where = where->prior;
            return *this;
        }
        int operator*() const {
            return where->data;
        }
        int& operator*() {
            return where->data;
        }
    private:
        Node* where;
    };
    
    List() : length(0), header(new Node(0)), trailer(new Node(0)) {
        header->next = trailer;
        trailer->prior = header;
    }
    int& operator[](size_t index) {
        Node* currNode = header->next;
        size_t i = 0;
        while (i != index && currNode != trailer) {
            currNode = currNode->next;
            i++;
        }
        return currNode->data;
    }
    int operator[](size_t index) const {
        Node* currNode = header->next;
        size_t i = 0;
        while (i != index && currNode != trailer) {
            currNode = currNode->next;
            i++;
        }
        return currNode->data;
    }
    void push_back(int data) {
        Node* newNode = new Node(data);
        trailer->prior->next = newNode;
        newNode->prior = trailer->prior;
        newNode->next = trailer;
        trailer->prior = newNode;
        length++;
    }
    void push_front(int data) {
        Node* newNode = new Node(data);
        newNode->next = header->next;
        header->next->prior = newNode;
        header->next = newNode;
        newNode->prior = header;
        length++;
    }
    void pop_back() {
        if (trailer->prior != header) {
            Node* popNode = trailer->prior;
            trailer->prior = trailer->prior->prior;
            trailer->prior->next = trailer;
            delete popNode;
            length--;
        }
    }
    void pop_front() {
        if (header->next != trailer) {
            Node* popNode = header->next;
            header->next = header->next->next;
            header->next->prior = header;
            delete popNode;
            length--;
        }
    }
    void clear() {
        while (header->next != trailer) {
            pop_back();
        }
    }
    Iterator erase(const Iterator& iterator) {
        Node* currNode = iterator.where;
        currNode->prior->next = currNode->next;
        currNode->next->prior = currNode->prior;
        delete currNode;
        length--;
        return Iterator(currNode->next);
    }
    Iterator begin() {
        return Iterator(header->next);
    }
    Iterator end() {
        return Iterator(trailer);
    }
    Iterator insert(const Iterator& iterator, int data) {
        Node* newNode = new Node(data);
        Node* currIter = iterator.where;
        currIter->prior->next = newNode;
        newNode->prior = currIter->prior;
        newNode->next = currIter;
        currIter->prior = newNode;
        length++;
        return Iterator(newNode);
    };
    int front() {
        return header->next->data;
    };
    int back() {
        return trailer->prior->data;
    };
    size_t size() const {
        return length;
    };

};

void printListInfo(List& myList) {
    cout << "size: " << myList.size()
    << ", front(): " << myList.front()
    << ", back(): " << myList.back()
    << ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {
    
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
    << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
//
//    // Task 8
//    cout << "\n------Task Eight------\n";
//    cout << "Copy control\n";
//    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
//    myList.clear();
//    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
//    printListInfo(myList);
//    cout << "Calling doNothing(myList)\n";
//    doNothing(myList);
//    cout << "Back from doNothing(myList)\n";
//    printListInfo(myList);
//
//    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
//    List listTwo;
//    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
//    printListInfo(listTwo);
//    cout << "listTwo = myList\n";
//    listTwo = myList;
//    cout << "myList: ";
//    printListInfo(myList);
//    cout << "listTwo: ";
//    printListInfo(listTwo);
//    cout << "===================\n";
}
