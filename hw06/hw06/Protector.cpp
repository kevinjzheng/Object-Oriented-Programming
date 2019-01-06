//
//  Protector.cpp
//  hw07
//
//  Created by Kevin J. Zheng on 11/10/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "Protector.h"
#include "Noble.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace WarriorCraft {
    Protector::Protector(const string& name, const double& strength) :
        name(name), strength(strength) { }
    Lord* Protector::getOwner() const { return owner; }
    void Protector::setOwner(Lord* newOwner) { owner = newOwner; }
    string Protector::getName() const { return name; }
    bool Protector::getAlive() const { return isAlive; }
    void Protector::setAlive(bool status) { isAlive = status; }
    double Protector::getStrength() const { return strength; }
    void Protector::setStrength(double ratio)
        { strength = strength - (strength * ratio); }
    bool Protector::quit() {    // allows protector to leave an army
        if (owner != nullptr) {
            string ownerName = owner->getName();
            if (owner->remove(*this)) {
                cout << name << " quits from the army, abandoning his lord ";
                cout << ownerName << endl;
                return true;
            }
        }
        return false;
    }
    
    Warrior::Warrior(const string& name, const double strength) :
        Protector(name, strength) { }
    void Warrior::defend() const {  // battlecry
        cout << " says: Take that in the name of my lord, ";
        cout << getOwner()->getName() << endl;
    }

    Wizard::Wizard(const string& name, const double& strength) :
        Protector(name, strength) { }
    void Wizard::defend() const {   // battlecry
        if (Protector::getAlive()) {
            cout << "POOF!" << endl;
        }
    }

    Archer::Archer(const string& name, const double& strength) :
        Warrior(name, strength) { }
    void Archer::defend() const {   // battlecry
        if (Protector::getAlive()) {
            cout << "TWANG! " << Protector::getName();
            Warrior::defend();
        }
    }

    Swordsman::Swordsman(const string& name, const double& strength) :
        Warrior(name, strength) { }
    void Swordsman::defend() const {    // battlecry
        if (Protector::getAlive()) {
            cout << "CLANG! " << Protector::getName();
            Warrior::defend();
        }
    }
}

