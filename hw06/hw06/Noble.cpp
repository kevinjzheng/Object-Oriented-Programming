//
//  Noble.cpp
//  hw07
//
//  Created by Kevin J. Zheng on 11/10/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "Noble.h"
#include "Protector.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name, const double& strength) :
        name(name), strength(strength) { }
    bool Noble::getAlive() const { return isAlive; }
    double Noble::getStrength() const { return strength; }
    string Noble::getName() const { return name; }
    void Noble::setStrength(double ratio) { // updates strength
        strength = strength - (strength * ratio);
    }
    void Noble::battle(Noble& opponent) {
        if (!isAlive && !opponent.isAlive ) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!opponent.isAlive) { // opponent is dead
            cout << "He's dead, " << name << endl;
        }
        else if (!isAlive) {  // noble is dead
            cout << "He's dead, " << opponent.name << endl;
        }
        else {  // both are alive and healthy to fight
            if (strength == opponent.strength) {    // of equal strength
                cout << "Mutual Annihalation: " << name << " and " <<
                opponent.name << " die at each other's hands" << endl;
                isAlive = false;
                setStrength(1); // ratio is 1 so that makes strength 0
                opponent.isAlive = false;
                opponent.setStrength(1); // ratio is 1 so that makes strength 0
            }
            else if (strength > opponent.strength) {    // this army is stronger
                cout << name << " defeats " << opponent.name << endl;
                double ratio = opponent.strength / strength;
                setStrength(ratio);
                opponent.setStrength(1); // ratio is 1 so that makes strength 0
                opponent.isAlive = false;
            }
            else {  // (strength < opponent.strength)   // opponent is stronger
                cout << opponent.name << " defeats " << name << endl;
                double ratio = strength / opponent.strength;
                opponent.setStrength(ratio);
                setStrength(1); // ratio is 1 so that makes strength 0
                isAlive = false;
            }
        }
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight
        (const string& name, const double& strength) : Noble(name,strength) { }
        void PersonWithStrengthToFight::battle(Noble& rhs)
            { Noble::battle(rhs); }
        void PersonWithStrengthToFight::setStrength(double ratio)
            { Noble::setStrength(ratio); };

    Lord::Lord(const string& name) : Noble(name,0) {}
    bool Lord::hires(Protector& rhs) {  // hires a protector
        if ((this->getAlive()) && (rhs.getAlive()) &&
            rhs.getOwner() == nullptr) { // test cases for hiring
            rhs.setOwner(this);
            Defenders.push_back(&rhs);
            strength += rhs.getStrength();
            return true;
        }
        return false;
    }
    void Lord::battle(Noble& rhs) {
        cout << getName() << " battles " << rhs.getName() << endl;
        for (Protector* defender : Defenders) {
            defender->defend(); // protectors who are alive, battlecry
        }
        Noble::battle(rhs);
    }
    void Lord::setStrength(double ratio) {
        for (Protector* defender : Defenders) {
            defender->setStrength(ratio);
            if (defender->getStrength() == 0) {
                defender->setAlive(false);
            }
        }
        // recalculate lord's strength
        strength = 0;
        for (Protector* defender : Defenders) {
            strength += defender->getStrength();
        }
    }
    bool Lord::remove(Protector& rhs) { // removing a protector from the army
        bool found = false;
        for (size_t i = 0; i < Defenders.size(); i++) {
            if (Defenders[i] == &rhs) {
                found = true;
                Protector* temp = &rhs;
                Defenders[i] = Defenders[i+1];
                Defenders[i+1] = temp;
            }
        }
        if (found || Defenders[Defenders.size() - 1] == &rhs) {
            Defenders.pop_back();
            rhs.setOwner(nullptr);
            return true;
        }
        return false;
    };
}
