//
//  Vector.cpp
//  Vector
//
//  Created by Kevin J. Zheng on 10/9/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

/*
 Vector Class
 Demonstrates:
    Good example of copy control
    Dynamic arrays and pointer arithmetic
    Square bracket operator
    Implementation of an important data structure
*/

#include <iostream>
using namespace std;


// acts as a pointer to the location of the data
class Iterator {
    // binary functions/operators are non-members by convention
    // not a combination operator
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
        // comparing the two where pointers if they point at the same
        return lhs.where != rhs.where;
    }
public:
    Iterator(int* p) : where(p) {}
    Iterator& operator++() {
        ++where;
        return *this;
    }
    /* if the operator* was implemented a non-member then it would take an
    Iterator&. But since its a uninary opeartor member it takes no parameters */
    // int x = *p;     // p.operator*();
    int operator*() const {
        return *where;
    }
    int& operator*() {
        return *where;
    }
private:
    int* where;
};




//template <typename Fred>
class Vector {
public:
//    Vector() : theSize(0), theCapacity(1), data(new int[theCapacity]) { }
    /* with that keyword, c++ would only use it when the programmer wants it
     in this case, Vectr(int num) */
    explicit Vector(size_t number = 0, int value = 0)
//    explicit Vector(size_t number, Fred val = Fred())
        : theSize(number), theCapacity(number), data(new int[theCapacity]) {
            for (size_t i = 0; i < number; i++) {
                data[i] = value;
            }
        }

    // Copy control
    ~Vector() {
        delete [] data;
    }
    
    Vector(const Vector& rhs) {
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new int[2 * theCapacity];
//        data = new Fred[2 * theCapacity];
        for (size_t i = 0; i < theSize; i++) {
            data[i] = rhs.data[i];
        }
    }
    
    Vector& operator=(const Vector& rhs) {
        // 1. Check for self assignment: checking addresses
        if (this != &rhs) {
            // 2. Free Up
            delete [] data;
            
            // 3. Allocating
            data = new int[rhs.theCapacity];
            
            // 4. Copying
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < rhs.theSize; i++) {
                data[i] = rhs.data[i];
            }
        }
        // 5. Returning yourself
        return *this;
    }
    
    void push_back(int val) {
        if (theCapacity == 0) {
            delete [] data;
            data = new int[1];
            theCapacity = 1;
        }
        else if (theSize == theCapacity) {
            int* oldData = data;
            data = new int[theCapacity];
            for (size_t i = 0; i < theSize; i++) {
                data[i] = oldData[i];
            }
            theCapacity *= 2;
            delete [] oldData;
        }
        data[theSize] = val;    // puts it at index theSize
        ++theSize;  // then increments
    }
    
    void pop_back() { --theSize; }
    
    void clear() { theSize = 0; }
    
    size_t size() { return theSize; }
    
    size_t size() const { return theSize; }
    
    // Square Brackets
    int& operator[](size_t index) { return data[index]; }
    // we made a reference return so that we can use the 0 on the left side
    //  of the assignment operator
//    int operator[](size_t index) const { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
    
    // returns the address of the first element
//    int* begin() { return data; }
//    int* begin() const { return data; }
    /* pointer arithmetic; incrementing a pointer can allow me to access the
     next item in the array, thus this would return the address AFTER the last
     element */
//    int* end() { return data + theSize; }
//    int* end() const { return data + theSize; }
//
    Iterator begin() { return Iterator(data); }
    Iterator begin() const { return Iterator(data); }
    
    Iterator end() { return Iterator(data+theSize); }
    Iterator end() const { return Iterator(data+theSize); }
    
private:
    size_t theCapacity;
    size_t theSize;
    int* data;
    //    Fred* data;
    
};

/* template <class T>  or template <typename T>  allows you to pass
void printVector(const Vector<T>& vec) */
void printVector(const Vector& v) {
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
//         v[i] = 17; // int& operator[](size_t index)const{return data[index]}
        // is wrong
    }
}

void printVector2(const Vector& v) {
    /* if passing in const Vector& v then since v uses begin() and end() and
     those are not const, it won't work, so add a begin() and end() that is
     const so it would work */
    for (int x : v) {
        cout << x << endl;
    }
}

void print(const Vector& v) {
    for (int& val : v) {    // would result in everything in the vector being
        // incremented
        cout << val << ' ';
        ++val;
    }
    cout << endl;
}

int main() {
    
    // Not templated. Our Vector class can only hold ints.
//    Vector<int> vec;
    
    Vector v;
    //    Vector<int> v;
    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);
    
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    
    for (int x : v) {
        cout << x << endl;
    }
    
    for (Iterator p = v.begin(); p != v.end(); ++p) {
//        creates copies of the values, this is what c++ does pass by value
//        int x = *p;
//        cout << x << endl;
        cout << *p << endl;
    }
    
    // must support a begin and end method that returns something that can be
    //  used to walk through the collection
    for (int x : v) {
        cout << x << endl;
    }
    
    // equivalent to
    for (int* p = v.begin(); p != v.end(); ++p) {
        int x = *p;     // p.operator*();
        cout << x << endl;
    }
    
    Vector v2(v);
    Vector v3;
    v3 = v3;
    v[0] = 100;
    
//    Vector v2(17);  // vector of 17, 0's
    
    // explicit stops this following code to work
//    v = 17;     // thinks its v = Vector(17); a temporary vector passing in 17
    
//    v[0] = 100;
//    for (size_t i = 0; i < v2.size(); i++) {
//        cout << v2[i] << endl;
//    }
    
    
}
