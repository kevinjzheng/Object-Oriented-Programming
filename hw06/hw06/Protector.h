//
//  PROTECTOR.H
//  hw07
//
//  Created by Kevin J. Zheng on 11/10/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
    class Noble;    // forward class declaration
    class Lord;     // forward class declaration
    
    class Protector {
    public:
        Protector(const std::string& name, const double& strength);
        Lord* getOwner() const;
        void setOwner(Lord* newOwner);
        std::string getName() const;
        virtual void defend() const = 0;    // pure virtual battlecry
        bool getAlive() const;
        void setAlive(bool status);
        double getStrength() const;
        void setStrength(double ratio);
        bool quit();
    private:
        std::string name;
        Lord* owner = nullptr;
        bool isAlive = true;
        double strength;
    };

    class Warrior : public Protector {
    public:
        Warrior(const std::string& name, const double strength);
        virtual void defend() const = 0;    // pure virtual battlecry
    private:
    };

    class Wizard : public Protector {
    public:
        Wizard(const std::string& name, const double& strength);
        void defend() const;    // wizard battlecry
    private:
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string& name, const double& strength);
        void defend() const;    // archer battlecry
    private:
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string& name, const double& strength);
        void defend() const;    // swordsman battlecry
    private:
    };
}

#endif /* PROTECTOR_H */
