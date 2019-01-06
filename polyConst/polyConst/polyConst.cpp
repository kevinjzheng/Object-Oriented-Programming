//
//  main.cpp
//  polyConst
//
//  Created by Kevin J. Zheng on 11/7/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
using namespace std;

//class Base {
//public:
//    Base() { this->foo(); }
//    virtual void foo() const { cout << "Base\n"; }
//    void display() { this->foo(); }
//};
//
//class Derived : public Base{
//public:
//    Derived(int n) : Base(), x(n) {}
//    void foo() const { cout << "Dervied: x == " << x << endl; }
//private:
//    int x;
//};

class Base {
public:
    virtual void display(ostream& os = cout) const {
        os << "Base";
    }
};

ostream& operator<<(ostream& os, const Base& rhs) {
//    os << "Base";
    rhs.display(os);
    return os;
}

class Derived : public Base {
    void display(ostream& os = cout) const {
        os << "Derived";
    }
};

//ostream& operator<<(ostream& os, const Derived& rhs) {
//    os << "Derived";
//    return os;
//}

void func(const Base& base) {
    cout << base << endl;
}

//int main() {
//    Derived der(17);
//    der.display();
//}

int main() {
    Derived der;
    cout << der << endl;
    func(der);
    /* dumb because there are two ways to display derived, we don't need the
     derived output operator because it would wrap and use the base output
     operator up top */

}

