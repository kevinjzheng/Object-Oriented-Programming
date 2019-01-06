//
//  Warrior.h
//  hw05
//
//  Created by Kevin J. Zheng on 10/26/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <vector>
#include <string>
namespace WarriorCraft {
    class Noble;
    class Warrior {
    public:
        Warrior(const std::string& name, float strength);
        std::string getName() const;
        float getStrength() const;
        void setStrength(float newStrength);
        Noble* getOwner() const;
        void setOwner(Noble* newOwner);
        void setAlive(bool status);
        bool getAlive() const;
        bool runaway();
    private:
        std::string name;
        float strength;
        Noble* owner = nullptr;
        bool alive = true;
    };
}

#endif /* WARRIOR_H */
