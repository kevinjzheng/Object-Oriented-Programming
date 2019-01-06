//
//  cc-inheritance.cpp
//  cc-inheritance
//
//  Created by Kevin J. Zheng on 11/5/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
using namespace std;

class Member {
    
};

class Base {
public:
    Base() {
        cerr << "Base()\n";
    }
    virtual ~Base() {
        cerr << "~Base()\n";
    }
    Base(const Base& rhs) {
        cerr << "Base(const Base&)\n";
    }
    Base& operator=(const Base& rhs) {
        cerr << "Base::operator=(const Base&)\n";
        return *this;
    }
};

class Derived : public Base {
public:
    Derived() {
        cerr << "Derived()\n";
    }
    ~Derived() {
        cerr << "~Derived()\n";
    }
    // copy-constructor
    Derived(const Derived& rhs) : Base(rhs), mem(rhs.mem) {
        cerr << "Derived(const Derived&)\n";
        /* since in the intialization list, it only invokes the base copy
         constructor, don't forget to copy the member variable as well */
    }
    // assignment operator
    Derived& operator=(const Derived& rhs) {
//        *this Base::= rhs;
//        this->Base::operator=(rhs);   either this
        Base::operator=(rhs);           // or this
        
        mem = rhs.mem;  // to copy over the member
        cerr << "Derived::operator=(const Derived&)\n";
        return *this;
    }
private:
    Member mem;
};

int main() {
//    Derived der;
    cout << "=======\n";
    Base* base = new Derived();
    delete base;
}
