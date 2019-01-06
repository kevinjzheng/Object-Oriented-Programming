//
//  mixIns.cpp
//  mixIns
//
//  Created by Kevin J. Zheng on 11/12/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    Person(const string& name) : name(name) {}
    virtual void display() const { cout << "Person"; }
private:
    string name;
};

// virtual inheritance
class Student : public virtual Person {
public:
    Student(const string& name) : Person(name) {}
    virtual void display() const { cout << "Student"; }
private:
//    string name;
};

// virtual inheritance
class Instructor : public virtual Person {
public:
    Instructor(const string& name) : Person(name) {}
    virtual void display() const { cout << "Instructor"; }
private:
//    string name;
};

// diamond inheritance so there is only one instance of shared variables
class TA : public Student, public Instructor {
public:
    TA(const string& name) : Person(name), Student(name), Instructor(name) {}
    void display() const { Student::display(); }
private:
};

int main() {
    
}
