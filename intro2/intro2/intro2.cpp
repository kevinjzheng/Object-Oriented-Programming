//
//  intro2.cpp
//  structs
//
//  Created by Kevin J. Zheng on 9/12/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Person { // capatilizing the types you define
    string name;    // not capatilizing variables you define
    int age;
};

struct Word {
    string token;
    vector<int> positions;
};

int main() {
    vector<Person> people;
    Person fred;    // unintialized int and an emtpy string
    people.push_back(fred); // the Person inside the vector is a copy of fred
    
    ifstream ifs("people");
    if (!ifs) {
        cerr << "failed to open people" << endl;
        exit(1);    // returning 0 when finished usually means success other numbers mean fail
    }
    
    string name;
    int age;
    ifs >> name >> age; // if stream is broken no more reads can be made afterward
    Person who;
    who.name = name;
    who.age = age;
    people.push_back(who);
    
    while(ifs >> name >> age) {
        Person someone;
        someone.name = name;
        someone.age = age;
//        Person someone{name,age};     works just the same way
        people.push_back(someone);
    }
    
    //for (Person anyone : people) {
    for (const Person& anyone: people) {
        cout << anyone.name << ' ' << anyone.age << endl;
    }
    
    vector <Word> words;
    
    
    return 0;
    

}
