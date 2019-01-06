//
//  polynomial.h
//  hw08
//
//  Created by Kevin J. Zheng on 11/30/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>
#include <iostream>

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public:
    Polynomial();
    Polynomial(std::vector<int> coeff);
    Polynomial(const Polynomial& rhs);
    Polynomial& operator+=(const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
    ~Polynomial();
    int evaluate(const int val);
private:
    int degree;
    Node* header;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

#endif /* POLYNOMIAL_H */
