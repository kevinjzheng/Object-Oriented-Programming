//
//  intro1.cpp
//  intro
//
//  Created by Kevin J. Zheng on 9/10/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>   // not a primitive, primitives don't need includes
using namespace std;

struct Car {
    string color; // if not given a value would be defaulted to empty string
    int year;
};

void addOne(int n) {    // pass by value; essentially a copy
    ++n;
//    n++;
}

int addOneV2(int n) {    // pass by value
    ++n;    // post increment
    return n;
    //    n++;  // pre increment
}

void addOneV3(int& n) {    // pass by reference; modifying the original
    ++n;
}
// the & sign makes it refer to the actual reference instead of making a copy

void printVector(const vector<int>& v) {
    for (int n : v) {
        cout << n << ' ';
    }
    cout << endl;
}
// const: the thing cannot be modified within the function
// pass by value would be for typically smaller types because creating
//      copies of larger items like vectors make be very time and space inefficient

int main() {
    int x = 17;
    cout << x << endl;
    addOne(x);
    cout << x << endl;
    x = addOneV2(x);
    cout << x << endl;
    addOneV3(x);
    cout << x << endl;
    
    vector<int>  fib{1,1,2,3,5,8,13};
//    cout << fib[0] << endl;

    printVector(fib);
    vector<string> vs{"moe","larry","curly"};
    for (const string& s : vs) {    // since we talk about the string we can protect it
        cout << s << endl;
    }
    // for range is nicer but also introduces the problem of copying
    for (size_t i = 0; i < vs.size(); ++i) {    // can't const the index
        cout << vs[i] << endl;
        vs[i] = "fred";
        
    }
    const vector<string> test{"Hello","World"}; // const vector protects all the items
//    test[0][0] = "B";  // won't work
    cout << test[0] << endl;
    
    Car myCar;  // we are creating an instance of struct Car
    cout << myCar.color << ' ' << myCar.year << endl;
    myCar.color = "red";
    myCar.year = 1970;
    cout << myCar.color << ' ' << myCar.year << endl;
    
    vector<Car> cars{myCar};
    cout << cars[0].color << endl;
}
// pass by value for copies for primatives else use pass by reference


