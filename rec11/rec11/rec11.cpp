//
//  rec11.cpp
//  rec11
//
//  Created by Kevin J. Zheng on 11/15/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
 functions for use with CS2124 rec11
 -jbs
 */

// Node to be used a part of linked list
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

// listInsertHead: adds a data item to the beginning of a [possibly empty] list
void listInsertHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

// printList: display method for my lists
void printList(Node* currNode) {
    while (currNode != nullptr) {
        cout << currNode->data << ' ';
        currNode = currNode->next;
    }
    cout << "\n";
}

// splice: adds a list into a list that its being spliced into
void splice(Node* newNode, Node* currNode) {
    // if currNode list is at the end of the list
    if (currNode->next == nullptr) {
        currNode->next = newNode;
    }
    else {
        Node* tempNext = currNode->next->next;
        currNode->next->next = newNode;
        while (newNode->next != nullptr) {
            newNode = newNode->next;
        }
        newNode->next = tempNext;
    }
}

// isSublist: checks if a list is a sublist of another list
Node* isSublist(Node* lookFor, Node* lookIn) {
    Node* lookForTemp = lookFor;
    Node* lookInTemp = lookIn;
    bool found = false;
    while (lookIn != nullptr && !found) {
        /* resets looking for and goes back to bookmark's next to continue
        checking, quadratic runtime */
        if (lookIn->data != lookFor->data) {
            lookFor = lookForTemp;
            lookIn = lookInTemp->next;
            lookInTemp = lookIn;
        }
        else {
            lookIn = lookIn->next;
            lookFor = lookFor->next;
        }
        if (lookFor == nullptr) {
            found = true;
            return lookInTemp;
        }
    }
    cout << "Failed to match!";
    return nullptr;
}

Node* shardListBruteForce(Node* head1, Node* head2) {
    while (head2 != nullptr) {
        Node* temp1 = head1;
        if (head1 != head2) {
            head1 = head1->next;
        }
        if (head1 == nullptr) {
            head1 = temp1;
            head2 = head2->next;
        }
        else {
            return head1->next;
        }
    }
    return nullptr;
}

Node* sharedListUsingSet(Node* head1, Node* head2) {
    unordered_set<Node*> list1;
    while (head1 != nullptr) {
        list1.insert(head1);
        head1 = head1->next;
    }
    while (head2 != nullptr) {
        if (list1.find(head2) != list1.end()) {
            return head2;
        }
        head2 = head2->next;
    }
    return nullptr;
}

int main() {
    Node* myList = listBuild({5,7,9,1});
    Node* myInsert = listBuild({6,3,2});
//    printList(myList);
//    printList(myInsert);
//    splice(myInsert, myList->next);
//    printList(myList);
//    Node* bigList = listBuild({5,7,6,3,2,9,1,7,6,3,1});
//    Node* littleList = listBuild({6,2,3});
//    printList(bigList);
//    printList(littleList);
//    isSublist(littleList, bigList);
//    Node* listLook = listBuild({2,9,1,4});
//    isSublist(listLook, bigList);
//    Node* anotherOne = listBuild({7,6,3});
//    isSublist(anotherOne, bigList);
    cout << "Part One: " << endl;
    cout << "L1: ";
    printList(myList);
    cout << "L2: ";
    printList(myInsert);
    cout << "Target: ";
    printList(myList->next);
    cout << "Splicing L2 at target in L1" << endl;
    splice(myInsert, myList);
    cout << "L1: ";
    printList(myList);
    cout << "L2: ";
    printList(myInsert);
    cout << "=====================" << endl;
    cout << "Part Two: " << endl;
    cout << "Target: ";
    Node* targetList = listBuild({1,2,3,2,3,2,4,5,6});
    printList(targetList);
    cout << "Attempt match: 1" << endl;
    Node* one = listBuild({1});
    printList(isSublist(one, targetList));
    cout << "Attempt match: 3 9" << endl;
    Node* threeNine = listBuild({3,9});
    printList(isSublist(threeNine, targetList));
    cout << "Attempt match: 2 3" << endl;
    Node* twoThree = listBuild({2,3});
    printList(isSublist(twoThree, targetList));
    cout << "Attempt match: 2 4 5 6" << endl;
    Node* twoFourFiveSix = listBuild({2,4,5,6});
    printList(isSublist(twoFourFiveSix, targetList));
    cout << "Attempt match: 2 3 2 4" << endl;
    Node* twoThreeTwoFour = listBuild({2,3,2,4});
    printList(isSublist(twoThreeTwoFour, targetList));
    
    cout << "=====Brute Force=====" << endl;
    Node* twoThreeFourFive = listBuild({2,3,4,5});
    Node* twoThreeThree = listBuild({2,3,3});
    twoThreeThree->next->next->next = twoThreeFourFive->next->next;
    printList(twoThreeFourFive);
    printList(twoThreeThree);
    printList(shardListBruteForce(twoThreeFourFive,twoThreeThree));
    cout << "======Using Set======" << endl;
    printList(sharedListUsingSet(twoThreeFourFive, twoThreeThree));
    
}
