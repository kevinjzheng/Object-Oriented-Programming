
//  polynomial.cpp
//  hw08
//
//  Created by Kevin J. Zheng on 11/30/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "polynomial.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// Overloading Polynomial Output Operator
ostream& operator<<(ostream& os, const Polynomial& rhs) {
    if (rhs.degree != -1) {
        Node* currNode = rhs.header->next;
        for (int i = rhs.degree; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                currNode = currNode->next;
            }
            if (currNode->data != 0) {
                if (i != 1) {
                    if (currNode->data == 1) {
                        os << "x^" << i << " + ";
                    }
                    else {
                        os << currNode->data << "x^" << i << " + ";
                    }
                }
                else {
                    if (currNode->data == 1) {
                        os << "x" << " + ";
                    }
                    else {
                        os << currNode->data << "x" << " + ";
                    }
                }
            }
            currNode = rhs.header->next;
        }
        os << currNode->data;
    }
    return os;
}

// Polynomial Default Constructors
Polynomial::Polynomial() : degree(-1), header(new Node(0)) {
    header->next = new Node(0);
    degree++;
};
Polynomial::Polynomial(vector<int> coeff) : degree(-1),
    header(new Node(0)){
    Node* currNode = header;
    for (size_t i = 0; i < coeff.size(); i++) {
        Node* newNode = new Node(coeff[coeff.size() - (i+1)]);
        currNode->next = newNode;
        currNode = currNode->next;
        degree++;
    }
};

// Polynomial Destructor
Polynomial::~Polynomial() {
    Node* currNode = header;
    Node* nextNode = header->next;
    while (nextNode != nullptr) {
        delete currNode;
        currNode = nextNode;
        nextNode = nextNode->next;
    }
    
}

// Polynomial Copy-Constructor
Polynomial::Polynomial(const Polynomial& rhs) {
    degree = rhs.degree;
    header = new Node(0);
    Node* currNode = rhs.header->next;
    Node* copy = header;
    while (currNode != nullptr) {
        copy->next = new Node(currNode->data);
        currNode = currNode->next;
        copy = copy->next;
    }
}

// Polynomial Assignment Operator
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    // 0. Self assignment
    if (&rhs != this) {
        // 1. Free up space
        Node* currNode = header;
        Node* nextNode = header->next;
        while (nextNode != nullptr) {
            delete currNode;
            currNode = nextNode;
            nextNode = nextNode->next;
        }
        // 2. Allocate new space
        header = new Node(0);
        // 3. Copying existing data
        degree = rhs.degree;
        currNode = rhs.header->next;
        Node* assignNode = header;
        while (currNode != nullptr) {
            assignNode->next = new Node(currNode->data);
            currNode = currNode->next;
            assignNode = assignNode->next;
        }
    }
    // 4. Return something
    return *this;
}

// Overloading Polynomial Operator +=
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* lhsNode = header;
    Node* rhsNode = rhs.header;
    while (lhsNode->next != nullptr || rhsNode->next != nullptr) {
        if (lhsNode->next != nullptr && rhsNode->next != nullptr) {
            lhsNode->next->data += rhsNode->next->data;
            lhsNode = lhsNode->next;
            rhsNode = rhsNode->next;
        }
        // if the rhs is longer than the lhs
        else if (rhsNode->next != nullptr && lhsNode->next == nullptr) {
            lhsNode->next = new Node(rhsNode->next->data);
            rhsNode = rhsNode->next;
            lhsNode = lhsNode->next;
            degree++;
        }
        else {  // if lhs is longer than rhs, keep bumping lhs pointer
            lhsNode = lhsNode->next;
        }
    }
    return *this;
}

// Overloading Polynomial Operator +
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial newPoly(lhs);
    return newPoly += rhs;
}

// Overloading Polynomial Operator ==
bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree == rhs.degree) {
        Node* lhsNode = lhs.header->next;
        Node* rhsNode = rhs.header->next;
        while (lhsNode != nullptr) {
            if (lhsNode->data == rhsNode->data) {
                lhsNode = lhsNode->next;
                rhsNode = rhsNode->next;
            }
        }
        return true;
    }
    return false;
}

// Overloading Polynomial Operator !=
bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}

// Evaluate Method Polynomial
int Polynomial::evaluate(const int val) {
    int sum = 0;
    Node* currNode = header->next;
    if (degree >= 0) {
        sum += currNode->data;
        currNode = currNode->next;
        for (int i = 0; i < degree; i++) {
            sum += (pow(val,i+1)) * (currNode->data);
            currNode = currNode->next;
        }
    }
    return sum;
}

