//
//  FrogPrince.h
//  testPrincess
//
//  Created by Kevin J. Zheng on 10/15/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef FROGPRINCE_H
#define FROGPRINCE_H

#include <string>
#include <iostream>

namespace Fantasy {
    class Princess; // forward class declaration

    class FrogPrince {
    public:
        FrogPrince(const std::string& name);
        void display() const;
        void marries(Princess& betrothed);
        void setSpouse(Princess* betrothed);
    private:
        std::string name;
        Princess* spouse;
    };
}

#endif
