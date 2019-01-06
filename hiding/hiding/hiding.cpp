//
//  hiding.cpp
//  hiding
//
//  Created by Kevin J. Zheng on 11/5/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
using namespace std;

class Base {
public:
    void foo(int n) const { cout << "Base::foo(n)\n"; }
};

class Derived : public Base {
public:
    void foo() const { cout << "Derived::foo()\n"; }
    /* before adding the two methods below, the derived class was hiding the foo
     method in the base class */
    void foo (int n) const { Base::foo(n); }
    using Base::foo;
};

int main() {
    Derived der;
    der.foo(17);
    der.Base::foo(17);
}
