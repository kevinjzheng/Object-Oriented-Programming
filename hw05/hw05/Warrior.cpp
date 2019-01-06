//
//  Warrior.cpp
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
    Warrior::Warrior(const string& name, float strength) : name(name), strength(strength){}
        
    string Warrior::getName() const { return name; }
    
    float Warrior::getStrength() const { return strength; }
    
    void Warrior::setStrength(float newStrength) { strength = newStrength; }
    
    Noble* Warrior::getOwner() const { return owner; }
    
    void Warrior::setOwner(Noble* newOwner) { owner = newOwner; }
    
    void Warrior::setAlive(bool status) { alive = status; }
    
    bool Warrior::getAlive() const { return alive; }
    
    // Warrior runaway method
    bool Warrior::runaway() {
        if (owner != nullptr) {
            string ownerName = owner->getName();
            if (owner->remove(*this)) {
//                Tarzan flees in terror, abandoning his lord, King Arthur
                cout << this->getName() << " flees in terror, abandoning his ";
                cout << "lord, " << ownerName << endl;
                return true;
            }
        }
        return false;
    }

}
