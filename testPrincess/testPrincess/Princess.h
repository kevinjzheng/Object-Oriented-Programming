//
//  Princess.h
//  testPrincess
//
//  Created by Kevin J. Zheng on 10/15/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.

#ifndef PRINCESS_H /* if not defined */
#define PRINCESS_H /* then define */

#include <string>
//using namespace std;  // no header file will have a using namespace

namespace Fantasy {
    class FrogPrince;    // forward class declaration

    class Princess {
    public:
        Princess(const std::string& name);
        void display() const;
        void marries(FrogPrince& bethothed);
    private:
        std::string name;
        FrogPrince* spouse;
    };
}

#endif  /* ends the define */
