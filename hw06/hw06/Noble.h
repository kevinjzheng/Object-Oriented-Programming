//
//  Noble.h
//  hw07
//
//  Created by Kevin J. Zheng on 11/10/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef NOBLE_H
#define NOBLE_H

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
    class Protector;    // forward class declaration

    class Noble {
    public:
        Noble(const std::string& name, const double& strength);
        virtual void battle(Noble& rhs) = 0;
        bool getAlive() const;
        double getStrength() const;
        virtual void setStrength(double ratio) = 0;
        std::string getName() const;
    protected:
        double strength;
    private:
        std::string name;
        bool isAlive = true;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight
            (const std::string& name, const double& strength);
        void battle(Noble& rhs);
        void setStrength(double ratio);
    private:
    };

    class Lord : public Noble {
    public:
        Lord(const std::string& name);
        bool hires(Protector& rhs);
        void battle(Noble& rhs);
        void setStrength(double ratio);
        bool remove(Protector& rhs);    // removes a protector from the army
    private:
        std::vector<Protector*> Defenders;
    };
}
#endif /* NOBLE_H */
