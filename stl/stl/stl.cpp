//
//  stl.cpp
//  stl
//
//  Created by Kevin J. Zheng on 11/28/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void print(char* start, char* stop) {
    for (char* p = start; p != stop; ++p) {
        cout << *p << ' ';
    }
    cout << endl;
}

void print(list<char>::iterator start, list<char>::iterator stop) {
    for (list<char>::iterator p = start; p != stop; ++p) {
        cout << *p << ' ';
    }
    cout << endl;
}

template <class T>
void print(T start, T stop) {
    for (T p = start; p != stop; ++p) {
        cout << *p << ' ';
    }
    cout << endl;
}

list<char>::iterator find(list<char>::iterator start, list<char>::iterator stop,
                          char target) {
    for (list<char>::iterator iter = start; iter != stop; ++iter) {
        if (*iter == target) { return iter; }
    }
    return stop;
}

template <typename T, typename U>
T myfind(T start, T stop, U target) {
    for (T iter = start; iter != stop; ++iter) {
        if (*iter == target) { return iter; }
    }
    return stop;
}

// known as predicates
bool isEven(int n) { return n % 2 == 0; }

template <typename Iter, typename Func>
Iter myfind_if(Iter start, Iter stop, Func pred) {
    for (Iter iter = start; iter != stop; ++iter) {
        if (pred(*iter)) return iter;
    }
    return stop;
}


class IsEven {
public:
    bool operator() (int n) { return n % 2 == 0; }
};

class IsMultiple {
public:
    IsMultiple(int factor) : factor(factor) { }
    bool operator() (int n) { return n % factor == 0; }
private:
    int factor;
};

int main() {
    char array[] = "Bjarne Stroustrup"; // last char in string is a null pointer
    int len = 17;
    sort(array, array+len);     // SORTED

    vector<char> vc(array, array+len);
    
    list<char> lc(array, array+len);
    //    list<char> lc2(vc);   // NOT IN THE STL LIBRARY
    list<char> lc3(vc.begin(), vc.end());   // half opened range [begin, end)
    
    for ( char* p = array; p != array + len; ++p) {
        cout << *p << ' ';
    }
    cout << endl;
    print(array, array + len);
    print(lc.begin(), lc.end());
    
    for (size_t i = 0; i < vc.size(); i++) {
        cout << vc[i] << ' ';
    }
    cout << endl;
    
//    for (size_t i = 0; i < vc.size(); i++) {
//        cout << lc[i] << ' ';
//    }
//    cout << endl;
    
    cout << *myfind(lc.begin(), lc.end(), 's') << endl;
    list<char>::iterator iter = myfind(lc.begin(), lc.end(), 'Q');
    
    /* auto would be used when the template already defined that the return
    type were to be the same type as lc.begin() and lc.end() so rewriting the
    return type would be a hassle and auto works */
    auto iter2 = myfind(lc.begin(), lc.end(), 'Q');
//    auto y; // DOESNT WORK!!!
    auto x = 17; // WORKS CUZ IT KNOWS U PROVIDED 17
    
    if (iter == lc.end()) {
        cout << "Q is not in..." << endl;
    }
    
    list<int> li {1, 3, 5, 7, 16, 25};
    
    find_if(li.begin(), li.end(), isEven);
    
    IsEven isEvenFunctor;

    IsMultiple multipleOf17(17);
    
    cout << boolalpha << isEvenFunctor(2) << endl;
    cout << isEvenFunctor(3) << endl;
    
    // overloaded the function call operator
    // mimics the function call
    find_if(li.begin(), li.end(), isEvenFunctor);
    // creating an instance of class IsEven with default constructor
    find_if(li.begin(), li.end(), IsEven());
    find_if(li.begin(), li.end(), multipleOf17);
    find_if(li.begin(), li.end(), IsMultiple(17));
//    find_if(li.begin(), li.end(), n % 2 == 0);
    
    int target = 17;
    // the compiler creates a functor and an instance of the functor class
    find_if(li.begin(), li.end(), [target] (int n) -> bool { return n % 2 == 0; } );
    
    // unamed functions or lambda expressions or functions
    // inferring the type without having a return type
    find_if(li.begin(), li.end(), [] (int n) { return n % 2 == 0; } );
    find_if(li.begin(), li.end(), [] (int n) -> bool { return n % 2 == 0; } );
//     do nothing function
    // all these equivalent
    [] {} ();
    [] () {} ();
    [] () -> void {} ();
    /* would have been potentially ambigous if the double return type had not
     specified */
    [] (int n) -> double {
        if (n == 0) return 17;
        else return 3.14;
    } (42);
    
    [] (int n) -> void {
        if (n == 0) cout << 17;
        else cout << 3.14;
    } (0);
    
}
