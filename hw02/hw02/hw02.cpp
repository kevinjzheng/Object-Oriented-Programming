//
//  hw02.cpp
//  hw02
//
//  Created by Kevin J. Zheng on 9/24/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class Warrior {
    class Weapon {
    private:
        int power;
        string weaponName;
    public:
        Weapon(const string& name, int power) :
        weaponName(name), power(power){ }
        string getWepName() const {
            return weaponName;
        }
        int getWepPower() const {
            return power;
        }
        void setWepPower(int newPower) {
            power = newPower;
        }
    };
private:
    string warriorName;
    Weapon newWeapon;
public:
    Warrior(const string& name, const string& wep, int power) :
    warriorName(name), newWeapon(wep,power) { }
    
    string getName() const {
        return warriorName;
    }
    string getWepName() const {
        return newWeapon.getWepName();
    }
    int getWepPower() const {
        return newWeapon.getWepPower();
    }
    void battle(Warrior& opponent) {
        cout << warriorName << " battles " << opponent.warriorName << endl;
        if (getWepPower() == 0 && opponent.getWepPower() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (getWepPower() == 0) {
            cout << "He's dead, " << opponent.warriorName << endl;
        }
        else if (opponent.getWepPower() == 0) {
            cout << "He's dead, " << warriorName << endl;
        }
        else if (getWepPower() > opponent.getWepPower()) {
            int newPower = getWepPower() - opponent.getWepPower();
            newWeapon.setWepPower(newPower);
            opponent.newWeapon.setWepPower(0);
            cout << warriorName << " beats " << opponent.warriorName << endl;
        }
        else if (getWepPower() < opponent.getWepPower()) {
            int newPower = opponent.getWepPower() - getWepPower();
            opponent.newWeapon.setWepPower(newPower);
            newWeapon.setWepPower(0);
            cout << opponent.warriorName << " beats " << warriorName << endl;
        }
        else {  // powers are equal
            cout << "Mutual Annihilation: " << warriorName << " and " <<
            opponent.warriorName << " die at each other's hands" << endl;
            newWeapon.setWepPower(0);
            opponent.newWeapon.setWepPower(0);
        }
    }
};

// cout overload
ostream& operator<< (ostream& os, const Warrior& warrior) {
    os << "Warrior: " << warrior.getName() << ", weapon: "
    << warrior.getWepName() << ", " << warrior.getWepPower();
    return os;
}

void fillVector(ifstream& ifs, vector<Warrior>& Warriors) {
    string warrior1;
    string weaponName;
    int weaponPower;
    ifs >> warrior1 >> weaponName >> weaponPower;
    Warrior newWarrior(warrior1,weaponName,weaponPower);
    Warriors.push_back(newWarrior);

}

// prints out all the warriors with their weapon names and powers
void displayVector(const vector<Warrior>& Warriors) {
    cout << "There are: " << Warriors.size() << " warriors" << endl;
    for (size_t i = 0; i < Warriors.size(); i++) {
        cout << Warriors[i] << endl;
    }
}

int main () {
    vector<Warrior> Warriors;
    ifstream file("warriors.txt");
    if (!file) {
        cerr << "failed to open warriors" << endl;
        exit(1);
    }
    string command;
    while (file >> command) {
        if (command == "Warrior") {
            fillVector(file,Warriors);
        }
        else if (command == "Status") {
            displayVector(Warriors);
        }
        else {  // command == "Battle"
            string warrior1;
            string warrior2;
            file >> warrior1 >> warrior2;
            for (size_t i = 0; i < Warriors.size(); i++) {
                if (Warriors[i].getName() == warrior1) {
                    for (size_t j = 0; j < Warriors.size(); j++) {
                        if (Warriors[j].getName() == warrior2) {
                            Warriors[i].battle(Warriors[j]);
                            break;  // breaks out if both warriors found
                        }
                    }
                }
            }
        } // close else
    }
    file.close();
}
