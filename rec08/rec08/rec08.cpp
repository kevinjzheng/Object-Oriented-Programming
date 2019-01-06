//
//  rec08.cpp
//  rec08
//
//  Created by Kevin J. Zheng on 10/25/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

/*
 testRational.cpp
 CS2124
 Implement the class Rational, so that the following program works.
 */

// If usingtime allows use  separate compilation, otherwise just define the
// class below
//#include "Rational.h"

// If usingtime allows after using separate compilation, then wrap the
// class in a namespace.
// using namespace CS2124;

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

class Rational {
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend ostream& operator<<(ostream& os, const Rational& rhs) {
        os << rhs.numerator << '/' << rhs.denominator;
        return os;
    }
    friend istream& operator>>(istream& is, Rational& rhs) {
        char div;
        is >> rhs.numerator >> div >> rhs.denominator;
        rhs.normalize();
        return is;
    }
public:
    Rational(int num=0, int denom=1) : numerator(num), denominator(denom) {
        normalize();
    }
    
    Rational& operator+=(const Rational& rhs) {
        int tempNum = rhs.numerator;
        int tempDenom = rhs.denominator;
        if (denominator != rhs.denominator) {
            tempDenom *= denominator;
            tempNum *= denominator;
            denominator *= rhs.denominator;
            numerator *= rhs.denominator;
        }
        numerator += tempNum;
        normalize();
        return *this;
    }
    
    // pre-increment
    Rational& operator++() {
        numerator += denominator;
        normalize();
        return *this;
    }
    
    // post-increment
    Rational operator++(int dummy) {
        Rational result(*this);
        numerator += denominator;
        normalize();
        return result;
    }
    
    explicit operator bool() const {
        return numerator != 0;
    };
    
private:
    int numerator;
    int denominator;
    int greatestCommonDivisor(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }
    void normalize() {
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0 && numerator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
        else if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }
};

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational newRational = lhs;
    return newRational += rhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

// pre-decrement
Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}

// post-decrement
Rational operator--(Rational& rhs, int dummy) {
    Rational result = rhs;
    rhs += -1;
    return result;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs == rhs || lhs < rhs;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs == rhs || lhs > rhs;
}

int main() {
    Rational twoThirds(2,3);
    cout << twoThirds << endl;
    
    Rational a, b;
    cout << "Input two rational numbers.\n";
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    Rational one(1);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;

    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

//     Even though the above example, (a++ ++), compiled, the
//     following shouldn't.
//     But some compiler vendors might let it...  Is your compiler
//     doing the right thing?
//     cout << "a-- -- = " << (a-- --) << endl;
//     cout << "a = " << a << endl;
    
    cout << "b = " << b << endl;
    cout << "a < b: " << (a < b) << endl;
    cout << "a > b: " << (a > b) << endl;
    
    cout << "a <= b: " << (a <= b) << endl;
    cout << "a >= b: " << (a >= b) << endl;
    
    Rational three(3);
    Rational three2(3);
    
    cout << "3 <= 3: " << (three <= three2) << endl;
    cout << "3 >= 3: " << (three >= three2) << endl;
    
    
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }
}

