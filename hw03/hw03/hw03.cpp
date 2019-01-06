//
//  hw03.cpp
//  hw03
//
//  Created by Kevin J. Zheng on 10/2/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// prototype to allow me to use Noble in Warrior class
class Noble;

// defining warrior class
class Warrior {
public:
    Warrior(const string& name, float strength) : name(name), strength(strength){}
    
    string getName() const {
        return name;
    }
    
    float getStrength() const {
        return strength;
    }
    
    void setStrength(float newStrength) {
        strength = newStrength;
    }
    
    Noble* getOwner() const {
        return owner;
    }
    
    void setOwner(Noble* newOwner) {
        owner = newOwner;
    }
    
    void setAlive(bool status) {
        alive = status;
    }
    
    bool getAlive() const {
        return alive;
    }
private:
    string name;
    float strength;
    Noble* owner = nullptr;
    bool alive = true;
};

// defining noble class
class Noble {
public:
    // noble default constructor
    Noble(const string& name) : name(name) {}
    
    bool hire(Warrior& newWarrior) {
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

    bool fire(Warrior& extWarrior) {
        if (!alive) {   // if noble is dead
            cerr << name << " cannot fire if he is not alive!" << endl;
            return false;
        }
        bool found = false;
        // loop through army to find warrior to fire
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
            cout << extWarrior.getName() << ", you're fired! -- " <<
            name << endl;
            extWarrior.setOwner(nullptr);
            return true;
        }
        return false;
    }
    
    void battle(Noble& opponent) {
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
    
    void display() {    // displaying a noble's army
        cout << name << " has an army of " << Army.size() << endl;
        for (size_t i = 0; i < Army.size(); i++) {
            cout << "\t" << Army[i]->getName() << ": " <<
            Army[i]->getStrength() << endl;
        }
    }
private:
    string name;
    vector<Warrior*> Army;
    bool alive = true;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
    
    art.fire(cheetah);
    art.display();
    
    // custom test cases
//    billie.hire(cheetah);
//    billie.display();
    
//    art.battle(lance);
    
//    jim.display();
//    lance.display();
//    art.display();
//    linus.display();
//    billie.display();
//
    
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    
//    Extra Test Cases
//    jim.display();
//    lance.display();
//    art.display();
//    linus.display();
//    billie.display();
//    lance.hire(cheetah); // custom test-case
    
}
