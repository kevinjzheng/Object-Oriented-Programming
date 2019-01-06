//
//  copy-control.cpp
//  copy-control
//
//  Created by Kevin J. Zheng on 10/1/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Foo {
public:
    Foo(int x) { p = new int(x); }
    void display() const { cout << *p << endl; }
    void setValue(int val) { * p = val; }
//    void cleanUp() {
//        delete p;
//        p = nullptr;
//    }
    // Destructor, will be called automatically whenever an instance of Foo is
    //  about to cease to exist
    ~Foo() {
        delete p;
        p = nullptr;
    }
    Foo(const Foo& anotherFoo) { // copy-constructor
        p = anotherFoo.p; // shallow copy
        p = new int(*anotherFoo.p); // deep copy
    }
    Foo& operator=(const Foo& rhs) {
        // 0. Self-assignment
        if (&rhs != this) { // if it is itself
            // 1.Free up    // looks like destructor
            delete p;
            // 2.Allocate
            //        p = new int();
            // 3.Copying    // looks like copy-constructor
            //        *p = *rhs.p;
            p = new int(*rhs.p);
        }
        // 4.Return something
        return *this;
    }
private:
    int* p;
};

// a shallow copy is being made
void doNothing(Foo someFoo) {}

void simpleFunc() {
    Foo aFoo(17);
    aFoo.display();
//    aFoo.cleanUp();
    doNothing(aFoo);
    aFoo.display();
}

int main() {
    simpleFunc();
    
    Foo a(17);
    Foo b(28);
    
    a = b; // operator= , operator overload
//    operator = (a, b); // cant work, c++ won't let it work
    a.operator=(b);
    
    Foo c(a);
    Foo d = a;  // d is being intialized and defined and thus use copy-construct
    
    // this is a prototype
    // I promise there will be a function e with no parameters that returns Foo
//    Foo e();    // using default constructor incorrectly
    
//    Foo e; // create e of Foo type with its default constructor
}
