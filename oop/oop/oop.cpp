//
//  oop.cpp
//  oop
//
//  Created by Kevin J. Zheng on 9/17/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//struct Person {   // simplier things
class Person {  // more complicated objects with functions and more data
private:
    string name;
    int age;
    
public:
    // this function has no return type at all
//    Person(const string& theName, int theAge) : name(theName), age(theAge){
    Person(const string& name, int age) : name(name), age(age){
//        name = theName;
//        age = theAge;
    }
//    void displayPerson() {
//        cout << "Person: " << name << endl;
//
//    }
//    void display() {
//        cout << "Person: " << name << endl;
//
//    }
    void display(/* parameter list */) const { /* body */
        cout << "Person: " << name << endl;
        
    }
};

//void displayPerson(const Person& aPerson) {
//    cout << "Person: " << aPerson.name << endl;
//
//}

int main() {
//    creating an instance of an Object: Person
//    Person john;
//    john.name = "John";
    Person john("John",20);    //    constructors
//    john.name = "Fred"; // this should be the only thing that breaks
//    displayPerson(john);
//    john.displayPerson();
    john.display();
}
