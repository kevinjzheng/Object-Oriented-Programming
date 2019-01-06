 //
//  Noble.cpp
//  hw05
//
//  Created by Kevin J. Zheng on 10/26/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    // noble default constructor
    Noble::Noble(const string& name) : name(name) {}
    
    std::string Noble::getName() const {
        return name;
    }
    
    bool Noble::hire(Warrior& newWarrior) {
        if (!alive) {   // if noble is dead
            cerr << name << " cannot hire if he is not alive!" << endl;
            return false;
        }
        else if (!newWarrior.getAlive()) {  // if warrior is dead
            cerr << newWarrior.getName() << " is not alive!" << endl;
            return false;
        }
        else {  //(!newWarrior.getOwner())  // adding to army
            newWarrior.setOwner(this);
            Army.push_back(&newWarrior);
            return true;
        }
        return false;
    }
    
    bool Noble::remove(Warrior& extWarrior) {
        bool found = false;
        for (size_t i = 0; i < Army.size() - 1; i++) {
            if (Army[i] == &extWarrior) {
                found = true;
                Warrior temp = *Army[i];
                Army[i] = Army[i+1];
                Army[i+1] = &temp;
            }
        }
        if (found || Army[Army.size() - 1] == &extWarrior) {
            Army.pop_back();
            extWarrior.setOwner(nullptr);
            return true;
        }
        return false;
    }
    
    bool Noble::fire(Warrior& extWarrior) {
        if (!alive) {   // if noble is dead
            cerr << name << " cannot fire if he is not alive!" << endl;
            return false;
        }
        if (remove(extWarrior)) {
            cout << extWarrior.getName() << ", you're fired! -- " <<
            name << endl;
        }
        return false;
    }
    
    void Noble::battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (!alive && !opponent.alive) {    // both nobles are dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!opponent.alive) { // opponent is dead
            cout << "He's dead, " << name << endl;
        }
        else if (!alive) {  // noble is dead
            cout << "He's dead, " << opponent.name << endl;
        }
        else {
            float army1Power = 0;
            float army2Power = 0;
            // add up army powers
            for (size_t i = 0; i < Army.size(); i++) {
                army1Power += Army[i]->getStrength();
            }
            for (size_t j = 0; j < opponent.Army.size(); j++){
                army2Power += opponent.Army[j]->getStrength();
            }
            // compare army powers
            if (army1Power == army2Power) { // if powers are equal
                cout << "Mutual Annihalation: " << name << " and " <<
                opponent.name << " die at each other's hands" << endl;
                alive = false;
                opponent.alive = false;
                // setting both army's warriors to dead
                for (size_t i = 0; i < Army.size(); i++) {
                    Army[i]->setStrength(0);
                    Army[i]->setAlive(false);
                }
                for (size_t j = 0; j < opponent.Army.size(); j++) {
                    opponent.Army[j]->setStrength(0);
                    opponent.Army[j]->setAlive(false);
                }
            }
            else if (army1Power > army2Power) {
                float ratio = (army2Power / army1Power);
                cout << name << " defeats " << opponent.name << endl;
                opponent.alive = false;
                // set opponent army to dead
                for (size_t j = 0; j < opponent.Army.size(); j++) {
                    opponent.Army[j]->setStrength(0);
                    opponent.Army[j]->setAlive(false);
                }
                // dividing the current army's warriors' powers
                for (size_t i = 0; i < Army.size(); i++) {
                    float newStrength= Army[i]->getStrength() -
                    (Army[i]->getStrength() * ratio);
                    Army[i]->setStrength(newStrength);
                }
                
            }
            else {  // army2Power > army1Power
                float ratio = (army1Power / army2Power);
                cout << opponent.name << " defeats " << name << endl;
                alive = false;
                // setting current army's warriors' to dead
                for (size_t i = 0; i < Army.size(); i++) {
                    Army[i]->setStrength(0);
                    Army[i]->setAlive(false);
                }
                // dividing the opponent's army's warriors' to dead
                for (size_t j = 0; j < opponent.Army.size(); j++) {
                    float newStrength= Army[j]->getStrength() -
                    (Army[j]->getStrength() * ratio);
                    opponent.Army[j]->setStrength(newStrength);
                }
            }
        }
    }
    // Noble Overload Output Operator
    ostream& operator<<(ostream& os, const Noble& rhs) {
        os << rhs.name << " has an army of " << rhs.Army.size() << endl;
        for (size_t i = 0; i < rhs.Army.size(); i++) {
            os << "\t" << rhs.Army[i]->getName() << ": " <<
            rhs.Army[i]->getStrength() << endl;
        }
        return os;
    }
}
