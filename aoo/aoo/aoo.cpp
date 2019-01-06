//
//  aoo.cpp
//  aoo
//
//  Created by Kevin J. Zheng on 10/22/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* Arithmetic Operator Overloading */

class Complex {
    friend ostream& operator<<(ostream& os, Complex rhs) {
        os << rhs.real;
        if (rhs.imaginary >= 0) { os << '+'; }
        os << rhs.imaginary << 'i';
        return os;
    }
public:
    Complex() : real(0), imaginary(0) { }
    Complex(double real) : real(real), imaginary (0) { }
    Complex(double real, double imag) : real(real), imaginary(imag) { }
    
    Complex& operator+=(const Complex& rhs) {
        //        this->real += rhs.real;
        real += rhs.real;
        //        this->imaginary += rhs.imaginary;
        imaginary += rhs.imaginary;
        return *this;
    }
    
    Complex& operator++() {
        real++;
        return *this;
    }
    
    // c1++
    
//    const Complex& operator++(int dummy) { // NO
    Complex operator++(int dummy) {
        Complex result(*this);
        ++real;
        return result;
    }
    
    // conversion operator
    explicit operator bool() const {
        return real != 0 || imaginary != 0;
    };
    
    bool operator==(const Complex& rhs) const {
        return real == rhs.real && imaginary == rhs.imaginary;
    }
    
private:
    double real, imaginary;
};

// don't return a reference because its on the call stack and its about to
// disappear once it has finished
//const Complex& operator+(const Complex& lhs, const Complex& rhs) {    // NO!
Complex operator+(const Complex& lhs, const Complex& rhs) {
    Complex result = lhs;
    return result += rhs;
}


int main() {
    Complex c1;     // 0 + 0i
    Complex c2(17); // 17 + 0i
    Complex c3(3, -5); // 3 - 5i
    cout << "c1: "  << c1 << endl
         << "c2: "  << c2 << endl
         << "c3: "  << c3 << endl;
    c1 = c2 + c3;
    operator+(c2, c3);
//    c2.operator+(c3);
    
     c1 += c2;
//    operator+=(c1, c2);
    c1.operator+=(c2);
//    cout << "c1: "  << c1 << endl
//    << "c2: "  << c2 << endl
//    << "c3: "  << c3 << endl;
    
    ++c1;
//    operator++(c1);
    c1.operator++();
    
    c1++;

    c1.operator++(0);   // 0 just allows you to overload operator 2 different ways
    
    /* limiting where a function could be used so we mark the opeartor bool()
     explicit (line 51); this means it would only be used when asking for a
     bool and no other reason */
    if (c1) { } // operator bool()
    
    if (c1 == c2) { }
    // typically by convention, binary operators are outside
//    operator==(c1,c2);
    c1.operator==(c2);
    
    cout << c1 << endl;
    if (c1 == c1) {
        cout << "c1 == c1\n";
    }else {
        cout << "c1 != c1\n";
    }
    
    Complex c4(1);
    if (c1 == c4) {
        cout << "c1 == c4\n";
    }else {
        cout << "c1 != c4\n";
    }
    
    // this converts the int to a Complex because we have
    // Complex(double real) : real(real), imaginary (0) { } (line 25)
    // int would convert to double, double to Complex
    if (c4 == 1) {
        cout << "c4 == 1\n";
    }else {
        cout << "c4 != 1\n";
    }

    
//    if (1.0 == c4) {
//        cout << "c4 == 1\n";
//    }else {
//        cout << "c4 != 1\n";
//    }
}


