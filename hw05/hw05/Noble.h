//
//  Noble.h
//  hw05
//
//  Created by Kevin J. Zheng on 10/26/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>
namespace WarriorCraft {
    class Warrior;
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
    public:
        Noble(const std::string& name);
        std::string getName() const;
        bool hire(Warrior& newWarrior);
        bool fire(Warrior& extWarrior);
        void battle(Noble& opponent);
        bool remove(Warrior& extWarrior);
    private:
        std::string name;
        std::vector<Warrior*> Army;
        bool alive = true;
    };
}

#endif /* NOBLE_H */
