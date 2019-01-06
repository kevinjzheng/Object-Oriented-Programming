//
//  inheritance.cpp
//  inheritance
//
//  Created by Kevin J. Zheng on 10/24/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Pet {
public:
    Pet(const string& name) : name(name) {
        cerr << "Pet(string)\n" << endl;
    }
//    /* virtual */ void eat() const { cout << "eating\n"; }
    virtual void eat() const { cout << "eating\n"; }
    virtual ~Pet() {} 
    
protected:  /* marking this protected so that only cats can call on other cats
    and other dogs can call on other dogs. No outsiders */
    const string& getName() const { return name; }
    
private:
//protected:
    /* any attribute is not accesible to outsiders but the derived can see
     its own name and names of other cats but slugs can't see cat names and
     cat can't see slug names */
    string name;
};
class Cat : public Pet {
public:
    // name is not directly accesible by the cat`
    Cat(const string& name) : Pet(name) {
        cerr << "Cat(string)\n" << endl;
    } /* : name(name) { } */
    void purr() const { cout << "purr\n"; }
    void eat() const { cout << "Cat eating\n"; }
};
class Slug : public Pet {
public:
    using Pet::Pet; // which would be using the base's constructors
    // give this class access to the base's constructors as if it were Slug's
    
};
class Roach : public Pet {};

void silly(const Pet& somePet) {
    somePet.eat();
}

void silly2(const Cat& aCat) {
    aCat.purr();
}

int main() {
//    Cat felix;
//    felix.eat();
//    Pet peeve;
//    silly(peeve);
    
    // has a reference of the whole cat, but its viewed as a pet
    // without the virtual it would just call the method located in the base
    // for the most optimal call
    // adding a virtual in the front makes the compiler choose the method
    // call based on what was passed into the parameters
    // By definition this is polymorphism
//    silly(felix);
    
    // methods of derived cannot be called by the main class
    // something expecting a main but a derived passed in works, but the
    // reverse doesn't work
//    peeve.purr();
//    silly2(peeve);
    
//    Slug sluggo;
//    Roach archie;
    
//    peeve = sluggo;   // legal, but slicing error (principle of substitutability
//    sluggo = peeve;   // not legal because passing in base when asked for derived
    
//    cout << "========" << endl;
//    // push back is a copying operation
//    vector<Pet> menagerie;
//    menagerie.push_back(felix);
//    menagerie.push_back(peeve);
//    menagerie.push_back(sluggo);
//    menagerie.push_back(archie);
//    for (size_t i = 0; i < menagerie.size(); ++i) {
//        menagerie[i].eat();
//    }
//
//    cout << "========" << endl;
//    // push back is a copying operation
//    vector<Pet*> menagerie2;
//    menagerie2.push_back(&felix);
//    menagerie2.push_back(&peeve);
//    menagerie2.push_back(&sluggo);
//    menagerie2.push_back(&archie);
//    for (size_t i = 0; i < menagerie.size(); ++i) {
//        menagerie2[i]->eat();
//    }
//
    Pet peeve2("peeve");
    Cat felix2("Felix");
    
    Slug sluggo("Sluggo");
    
    Pet* petPtr;
    Slug* slugPtr = &sluggo;
    Cat* catPtr = &felix2;
    petPtr = catPtr;
    petPtr = slugPtr;
//    petPtr->purr();   // won't work because purr() is not a method of Pet Class
    petPtr->eat();  /* will say cat is eating because it uses the base's method
    but those methods can be overwritten in a derived class and call that
    method instead */
//    catPtr = petPtr;  // type mismatch won't compile
    catPtr->purr();
    
}
