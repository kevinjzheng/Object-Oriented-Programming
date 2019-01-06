//
//  exceptions.cpp
//  exceptions
//
//  Created by Kevin J. Zheng on 12/12/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdlib>

#include <exception>
#include <stdexcept>

//#define NDEBUG  //  helps make the assertions go away
#include <cassert>

using namespace std;

struct OurException {
    
};

void bar(int n) {
    assert(n < 200);
    vector<int> v;
    v.push_back(17);
    cout << v[1] << endl;
//    cout << v.at(1) << endl;
    if (n > 200) {
        // What to do?
//        throw 3.14159;
        throw OurException();
    }
}

void foo(int n) { bar(n); }

int main() {
//    vector<int> v;
//    v.push_back(17);
//    cout << v[1] << endl;
//    cout << v.at(1) << endl;    // this throws out of range exception
    try {
        foo(300);
    }
    catch(double d) {   // catches the throw and continues the program
        cerr << "Caught a double: " << d << endl;
    }
    catch(out_of_range oor) {
        cerr << "Caught an out_of_range: " << oor.what() << endl;
    }
    catch(exception ex) {   // general catching after specifics
        cerr << "Caught an exception: " << ex.what() << endl;
    }
    catch(...) {    // only need this if you don't know what your catching
        cerr << "Caught something, don't know what. So long and thanks for all the fish" << endl;
    }
    cerr << "still going\n";
}

/*
 1. Terminate with feedback
 2. Exceptions
 3. return with error value
*/
