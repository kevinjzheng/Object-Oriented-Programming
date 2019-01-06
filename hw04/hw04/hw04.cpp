//
//  hw04.cpp
//  hw04
//
//  Created by Kevin J. Zheng on 10/14/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Noble;

class Warrior {
public:
    // Warrior default constructor, intialize with passed in variables
    Warrior(const string& name, float strength) : name(name),
    strength(strength) { }
    
    string getName() const { return name; }
    
    float getStrength() const { return strength; }
    
    Noble* getOwner() const { return nobleOwner; }
    
    void setOwner(Noble* newOwner) { nobleOwner = newOwner; }
    
    void setStrength(float newStrength) { strength = newStrength; }
private:
    string name;
    float strength;
    Noble* nobleOwner = nullptr;
};

class Noble {
public:
    // Noble default constructor, intialize with pass in variables
    Noble(const string& name) : name(name) { }
    
    string getName() const { return name; }
    
    bool isAlive() const { return alive; }
    
    void setAlive(bool status) { alive = status; }
    
    /* passing in a warrior pointer add that pointer to army vector and set
     warrior owner to current noble */
    bool hire(Warrior* warrior) {
        // if warrior is already hired print error message and return false
        if (warrior->getOwner() != nullptr) {
            cerr << warrior->getName() << " is already owned by " <<
            warrior->getOwner()->getName() << "!" << endl;
            return false;
        }
        // if warrior is hired successfuly return true
        else {
            warrior->setOwner(this);
            Army.push_back(warrior);
            return true;
        }
    }
    
    bool fire(Warrior* warrior) {
        // if noble doesnt own warrior, can't fire, return false
        if (warrior->getOwner() != this) {
            cerr << (*this).name << " doesn't own " << warrior->getName() <<
            "!" << endl;
            return false;
        }
        // if noble owns warrior, fire and return true
        else { //(warrior->getOwner() != nullptr) {
            // swap until warrior is at the back of the vector and popback
            for (size_t i = 0; i < Army.size(); i++) {
                if (warrior == Army[i]) {
                    Warrior* temp = Army[i];
                    Army[i] = Army[i+1];
                    Army[i+1] = temp;
                }
            }
            Army.pop_back();
            warrior->setOwner(nullptr);
            cout << "You don't work for me anymore " << warrior->getName() <<
            "! -- " << (*this).name << "." << endl;
            return true;
        }
    }
    
    void battle(Noble* opponent) {
        cout << (*this).name << " battles " << opponent->getName() << endl;
        float army1Power(0);
        float army2Power(0);
        float ratio(0); // ratio for winning and losing battles
        // loops to add up armies powers
        for (size_t i = 0; i < (*this).Army.size(); i++) {
            army1Power += (*this).Army[i]->getStrength();
        }
        for (size_t j = 0; j < opponent->Army.size(); j++) {
            army2Power += opponent->Army[j]->getStrength();
        }
        // test case for both dead nobles
        if ((*this).alive == false && opponent->isAlive() == false) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        // test cases for 1 dead noble
        else if (opponent->isAlive() == false)  {
            cout << "He's dead, " << (*this).name << endl;
        }
        else if ((*this).alive == false) {
            cout << "He's dead, " << opponent->getName() << endl;
        }
        // test case for equal power, set all strengths to 0 and status to dead
        else if (army1Power == army2Power) {
            cout << "Mutual Annihalation: " << (*this).name << " and " <<
            opponent->getName() << " die at each other's hands" << endl;
            for (size_t i = 0; i < (*this).Army.size(); i++) {
                (*this).Army[i]->setStrength(0);
            }
            for (size_t j = 0; j < opponent->Army.size(); j++) {
                opponent->Army[j]->setStrength(0);
            }
            (*this).alive = false;
            opponent->setAlive(false);
        }
        // winning battle for army1, change strengths and set loser to dead
        else if (army1Power > army2Power) {
            cout << (*this).name << " defeats " << opponent->getName() << endl;
            ratio = army2Power / army1Power;
            for (size_t i = 0; i < opponent->Army.size(); i++) {
                opponent->Army[i]->setStrength(0);
            }
            for (size_t j = 0; j < (*this).Army.size(); j++) {
                float newStrength = (*this).Army[j]->getStrength() -
                ((*this).Army[j]->getStrength() * ratio);
                (*this).Army[j]->setStrength(newStrength);
            }
            opponent->setAlive(false);
        }
        // winning battle for army2, change strengths and set loser to dead
        else {  // army1Power < army2Power
            cout << (*this).name << " defeats " << opponent->getName() << endl;
            ratio = army1Power / army2Power;
            for (size_t i = 0; i < (*this).Army.size(); i++) {
                (*this).Army[i]->setStrength(0);
            }
            for (size_t j = 0; j < opponent->Army.size(); j++) {
                float newStrength = opponent->Army[j]->getStrength() -
                (opponent->Army[j]->getStrength() * ratio);
                opponent->Army[j]->setStrength(newStrength);
            }
            (*this).alive = false;
        }
    }
private:
    string name;
    vector<Warrior*> Army;
    bool alive = true;
};

/* when status is called print the nobles in noble vector and warriors in their
 armies and any unemployed warriors */
void status(vector<Noble*>& Nobles, vector<Warrior*>& Warriors) {
    cout << "Status\n" << "======" << endl;
    cout << "Nobles:" << endl;
    // if both vectors are empty
    if (Nobles.size() == 0 && Warriors.size() == 0) {
        cout << "NONE\nUnemployed Warriors:\nNONE" << endl;
    }
    // loop through vector of nobles and print out their names and their armies
    else {
        for (size_t i = 0; i < Nobles.size(); i++) {
            cout << Nobles[i]->getName() << " has an army of " <<
            Nobles[i]->Army.size() << endl;
            for (size_t j = 0; j < Nobles[i]->Army.size(); j++) {
                cout << "\t\t" << Nobles[i]->Army[j]->getName() << ": " <<
                Nobles[i]->Army[j]->getStrength() << endl;
            }
        }
        cout << "Unemployed Warriors: " << endl;
        string unemployed = "NONE";
        // loop through warriors vector to look for unemployed
        for (size_t k = 0; k < Warriors.size(); k++) {
            if (Warriors[k]->getOwner() == nullptr) {
                unemployed = "";
                cout << Warriors[k]->getName() << ": " <<
                Warriors[k]->getStrength() << endl;
            }
        }
        // if there are no unemployed print NONE
        if (unemployed == "NONE") {
            cout << unemployed << endl;
        }
    }
};

// a clear function to free up space allocated on the heap
void clear(vector<Noble*>& Nobles, vector<Warrior*>& Warriors) {
    // loop through vector of nobles and delete each noble pointer on heap
    for (size_t i = 0; i < Nobles.size(); i++) {
        delete Nobles[i];
    }
    // clear noble vector
    Nobles.clear();
    // loop through vector of nobles and delete each warrior pointer on heap
    for (size_t j = 0; j < Warriors.size(); j++) {
        delete Warriors[j];
    }
    // clear warrior vector
    Warriors.clear();
};

// function to check if noble already exists returns true if so, else false
bool nobleExist(const string& nobleName, vector<Noble*>& Nobles){
    // loop throught noble vector to check for noble name
    for (size_t i = 0; i < Nobles.size(); i++) {
        if (Nobles[i]->getName() == nobleName){
            return true;
        }
    }
    return false;
};

// function to check if warrior already exists return true if so, else false
bool warriorExist(const string& warriorName, vector<Warrior*>& Warriors){
    // loop throught warrior vector to check for warrior name
    for (size_t i = 0; i < Warriors.size(); i++) {
        if (Warriors[i]->getName() == warriorName){
            return true;
        }
    }
    return false;
};

int main() {
    // input stream text file
    ifstream file("nobleWarriors.txt");
    // check if file is valid, if not, print error message and exit
    if (!file) {
        cerr << "Failed to open file" << endl;
        exit(1);
    }
    vector<Noble*> Nobles;
    vector<Warrior*> Warriors;
    string command;
    string noble;
    string noble2;
    string warrior;
    float strength;
    // read through input file
    while (file >> command) {
        if (command == "Clear") {
            clear(Nobles, Warriors);
        }
        else if (command == "Status") {
            status(Nobles, Warriors);
        }
        else if (command == "Noble") {
            file >> noble;
            // if noble already exist, print error message, don't make Noble
            if (nobleExist(noble, Nobles)) {
                cerr << noble << " already exists!" << endl;
            }
            /* if valid, allocate space on heap for new noble and add to noble
            vector */
            else {
                Noble* newNoble = new Noble(noble);
                Nobles.push_back(newNoble);
            }
        }
        else if (command == "Warrior") {
            file >> warrior >> strength;
            // if warrior already exist, print error message, dont' make Warrior
            if (warriorExist(warrior, Warriors)) {
                cerr << "Warrior already exists!" << endl;
            }
            /* if valid, allocate space on heap for new warrior and add to
             warrior vector */
            else {
                Warrior* newWarrior = new Warrior(warrior, strength);
                Warriors.push_back(newWarrior);
            }
        }
        else if (command == "Hire") {
            file >> noble >> warrior;
            // if both the noble and warrior exist, proceed to check
            if (nobleExist(noble, Nobles) && warriorExist(warrior, Warriors)){
                /* loop throught warrior vector looking for warrior, then loop
                 through noble vector for noble and then call hire method */
                for (size_t i = 0; i < Warriors.size(); i++) {
                    if (warrior == Warriors[i]->getName()) {
                        for (size_t j = 0; j < Nobles.size(); j++) {
                            if (noble == Nobles[j]->getName()) {
                                Nobles[j]->hire(Warriors[i]);
                                break;
                            }
                            
                        }
                        break;
                    }
                }
            }
            // if either noble or warriors doesn't exist
            else {
                // print error message if noble doesn't exist
                if (nobleExist(noble, Nobles) == false) {
                    cerr << "Noble " << noble << ", doesn't exist!" <<
                    " Can't hire!" << endl;
                }
                // print error message if warrior doesn't exist
                if (warriorExist(warrior, Warriors) == false) {
                    cerr << "Warrior " << warrior << ", doesn't exist!" <<
                    " Can't hire!" << endl;
                }
            }
        }
        else if (command == "Fire") {
            file >> noble >> warrior;
            // if both the noble and warrior exist, proceed to check
            if (nobleExist(noble, Nobles) && warriorExist(warrior, Warriors)) {
                /* loop throught warrior vector looking for warrior, then loop
                 through noble vector for noble and then call fire method */
                for (size_t i = 0; i < Warriors.size(); i++) {
                    if (warrior == Warriors[i]->getName()) {
                        for (size_t j = 0; j < Nobles.size(); j++) {
                            if (noble == Nobles[j]->getName()) {
                                Nobles[j]->fire(Warriors[i]);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            // if either noble or warriors doesn't exist
            else {
                // print error message if noble doesn't exist
                if (nobleExist(noble, Nobles) == false) {
                    cerr << "Noble " << noble << ", doesn't exist!" <<
                    " Can't fire!" << endl;
                }
                // print error message if warrior doesn't exist
                if (warriorExist(warrior, Warriors) == false) {
                    cerr << "Warrior " << warrior << ", doesn't exist!" <<
                    " Can't fire!" << endl;
                }
            }
        }
        else {  //command == "Battle"
            file >> noble >> noble2;
            // if both the noble and warrior exist, proceed to check
            if (nobleExist(noble, Nobles) && nobleExist(noble2, Nobles)) {
                /* loop throught noble vector looking for noble1, then loop
                 through noble vector again for noble2 and then call battle
                 method */
                for (size_t i = 0; i < Nobles.size(); i++) {
                    if (noble == Nobles[i]->getName()) {
                        for (size_t j = 0; j < Nobles.size(); j++) {
                            if (noble2 == Nobles[j]->getName()) {
                                Nobles[i]->battle(Nobles[j]);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            // if either noble or warriors doesn't exist
            else {
                // print error message if noble doesn't exist
                if (nobleExist(noble, Nobles) == false) {
                    cerr << "Noble " << noble << ", doesn't exist!" <<
                    " Can't fight!" << endl;
                }
                // print error message if warrior doesn't exist
                if (warriorExist(warrior, Warriors) == false) {
                    cerr << "Warrior " << warrior << ", doesn't exist!" <<
                    " Can't fight!" << endl;
                }
            }
        }
    }
    // very important to close the file after done streaming it
    file.close();
}
