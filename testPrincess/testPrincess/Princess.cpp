//
//  Princess.cpp
//  testPrincess
//
//  Created by Kevin J. Zheng on 10/15/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "Princess.h"
#include "FrogPrince.h"
#include <string>
#include <iostream>
using namespace std;

namespace Fantasy {
    Princess::Princess(const string& name) : name(name) {}

    void Princess::marries(FrogPrince& betrothed) {
        spouse = &betrothed;
        betrothed.setSpouse(this);
    }

    void Princess::display() const { cout << "Princess: " << name << endl; }
}



