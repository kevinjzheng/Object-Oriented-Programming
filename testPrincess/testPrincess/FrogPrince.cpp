//
//  FrogPrince.cpp
//  testPrincess
//
//  Created by Kevin J. Zheng on 10/17/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "Princess.h"
#include "FrogPrince.h"
#include <string>
#include <iostream>
using namespace std;

namespace Fantasy {
    FrogPrince::FrogPrince(const string& name) : name(name) {}
    void FrogPrince::display() const { cout << "Frog: " << name << endl; }
    void FrogPrince::marries(Princess& betrothed) {}
    void FrogPrince::setSpouse(Princess* betrothed) { spouse = betrothed; }
}
