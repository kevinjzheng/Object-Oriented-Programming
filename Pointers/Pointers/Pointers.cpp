//
//  Pointers.cpp
//  Pointers
//
//  Created by Kevin J. Zheng on 9/24/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Person {
public:
    Person(const string& name) : name(name) {}
    void display(ostream& os = cout) const {
        os << "Name: " << name << endl;
    }
    
    bool marries(Person& betrothed) {
        if (isMarried() || betrothed.isMarried()) {
            cout << "Person is already married\n";
            return false;
        } else {
            spouse = &betrothed;
//            married = true;
            betrothed.spouse = this;
//            betrothed.married = true;
            return true;
        }
    }
    
    bool isMarried() const {
//        return married;
        return spouse != nullptr;
    }
private:
    string name;
//    bool married = false;
    Person* spouse = nullptr;
};

int main() {
    Person john("John");
    Person mary("Mary");
    john.display();
    mary.display();
    john.marries(mary);
    
    Person sally("Sally");
    sally.marries(john);
    
    int x = 17;
    cout << &x << endl;
    
    // define type of pointer
    int* p = &x;
    // dereference operator
    cout << *p << endl;
    
//    int& intRef *p;
    x = 42;
    cout << *p << endl;
    
//    int y = *p;
//    cout << y << "here" << endl;
    
    int* q = p;
    cout << q << " here" << endl;
    
    const int* r1 = &x; // r cannto be used to modify x
    int* const r2 = &x; // r cannot change to point to a different int
    
    vector<Person*> people; // vector of Person pointers
    
    ifstream ifs("people");
    string name;
    while (ifs >> name) {
        // Persone someone is created once and whenever looped it is being
        //  reintialized but the addres of this someone Person is never changed
//        Person someone(name);
        // allocates a new Person object with a different address in the Heap
        // dynamic memory in the Heap
        Person* personPtr = new Person(name);
        people.push_back(personPtr);
    }
    
    for (Person* aPerson : people) {
//        (*aPerson).display();   // . has a higher precedence than *
        aPerson->display();
    }
    
    for (Person* aPerson : people) {
        //        (*aPerson).display();   // . has a higher precedence than *
        delete aPerson;
    }

    
}
