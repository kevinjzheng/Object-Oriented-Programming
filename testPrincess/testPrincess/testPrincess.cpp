//
//  testPrincess.cpp
//  testPrincess
//
//  Created by Kevin J. Zheng on 10/15/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "Princess.h"
#include "FrogPrince.h"
#include <iostream>
#include <string>
using namespace std;
using namespace Fantasy;    // or Fantasy::Princess and Fantasy::FrogPrince


                        /* CYCLIC ASSOCIATION */

//class FrogPrince; // forward class declaration
//// simply means that frogprince will get defined eventually: prototype
//
//class Princess {
//public:
//    Princess(const string& name);
////    Princess(const string& name) : name(name) { }
//    void display() const; // this const is an identifier of this function
////    void display() const { cout << "Princess: " << name << endl; }
//    void marries(FrogPrince& bethothed);    // prototype!
////    void marries(FrogPrince& betrothed) {
////        spouse = &betrothed;
//        /* compiler doesn't know yet that frogprince has this method, although
//         promised a prototype */
////        betrothed.setSpouse(this);
////    }
//private:
//    string name;
//    FrogPrince* spouse;
//};
//
//class FrogPrince {
//public:
//    FrogPrince(const string& name) : name(name) { }
//    void display() const { cout << "Frog: " << name << endl; }
//    void marries(Princess& betrothed) { }
//    void setSpouse(Princess* betrothed) { spouse = betrothed; }
//private:
//    string name;
//    Princess* spouse;
//};


///* intialization list is part of implementation and not the identifier */
//// Princess Implementation
//void Princess::marries(FrogPrince& betrothed) {
//    spouse = &betrothed;
//    // compiler doesn't know yet that frogprince has this method
//    betrothed.setSpouse(this);
//}
//
//void Princess::display() const { cout << "Princess: " << name << endl; }
//
//Princess::Princess(const string& name) : name(name) { }

int main() {
    Princess snowy("Snow White");
    snowy.display();
    FrogPrince froggy("Froggy");
    froggy.display();
    snowy.marries(froggy);  /* compiler sees there is a prototype so it is
                             promised so would compile */
    snowy.display();
}

