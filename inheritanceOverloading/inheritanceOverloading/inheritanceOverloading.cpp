//
//  inheritanceOverloading.cpp
//  inheritanceOverloading
//
//  Created by Kevin J. Zheng on 11/5/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

/* Demonstrates how the compiler decides for overloading */
#include <iostream>
using namespace std;

class Parent {
public:
    virtual void whereami() const {
        cout << "Parent!!!" << endl;
    }
};
class Child : public Parent {
public:
    void whereami() const {
        cout << "Child!!!" << endl;
    }
};
//class GrandChild : public Child {};

void func(Parent& base) { cout << "func(Parent)\n"; }
void func(Child& derived) { cout << "func(Child)\n"; }
//void func(Child& derived, Parent& base) { cout << "func(Child,Parent)\n"; }
//void func(Parent& base, Child& derived) { cout << "func(Parent,Child)\n"; }

void otherFunc(Parent& base) {
    func(base);         /* this is passing in a base reference as a parameter */
    base.whereami();    /* polymorphism is happening based on the object your
                         calling it on */
}

int main() {
//    Parent par;
//    func(par);
//    Child child;
//    func(child);
//    // neither function has a more specific parameter list: ambigous call
////    func(child, child);
//    GrandChild gc;
//    func(gc);
//
//    otherFunc(child);
    Child child;
    otherFunc(child);
}
