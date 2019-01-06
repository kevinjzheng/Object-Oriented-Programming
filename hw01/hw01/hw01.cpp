//
//  hw01.cpp
//  hw01 - Functions, structs, vectors and file I/O
//  Medieval Times Game
//  Created by Kevin J. Zheng on 9/19/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Warrior {
    string name;
    int strength;
    bool alive;
};

void addWarrior(const string& name, int strength, vector<Warrior>& arena) {
    Warrior newWarrior;
    newWarrior.name = name;
    newWarrior.strength = strength;
    newWarrior.alive = true;
    arena.push_back(newWarrior);
};

void printWarriors(const vector<Warrior>& arena) {
    cout << "There are: " << arena.size() << " warriors" << endl;
    for (size_t i = 0; i < arena.size(); i++) {
        cout << "Warrior: " << arena[i].name << ", strength: " <<
        arena[i].strength << endl;
    }
};

void battleWarriors(string& challenger, string& fighter, vector<Warrior>& arena) {
    Warrior warrior1;
    Warrior warrior2;
    cout << challenger << " battles " << fighter << endl;
    for (int i = 0; i < arena.size(); i++) {
        if (challenger == arena[i].name) {
            warrior1 = arena[i];
        }
        if (fighter == arena[i].name) {
            warrior2 = arena[i];
        }
    }
    if (!warrior1.alive && !warrior2.alive) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (warrior1.strength == warrior2.strength) {
        cout << "Mutual Annihilation: " << warrior1.name <<
        " and " << warrior2.name << " die at each other's hands" << endl;
        warrior1.alive = false;
        warrior2.alive = false;
        warrior1.strength = 0;
        warrior2.strength = 0;
    }
    else if (!warrior1.alive) {
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if (!warrior2.alive) {
        cout << "He's dead, " << warrior1.name << endl;
    }
    else if (warrior1.strength > warrior2.strength) {
        cout << warrior1.name << " defeats " << warrior2.name << endl;
        warrior1.strength = warrior1.strength - warrior2.strength;
        warrior2.alive = false;
        warrior2.strength = 0;
    }
    else if (warrior1.strength < warrior2.strength) {
        cout << warrior2.name << " defeats " << warrior1.name << endl;
        warrior2.strength = warrior2.strength - warrior1.strength;
        warrior1.alive = false;
        warrior1.strength = 0;
    }
    // updates warrior structs with no strength and alive status
    for (size_t i = 0; i < arena.size(); i++) {
        if (warrior1.name == arena[i].name) {
            arena[i].strength = warrior1.strength;
            arena[i].alive = warrior1.alive;
        }
        if (warrior2.name == arena[i].name) {
            arena[i].strength = warrior2.strength;
            arena[i].alive = warrior2.alive;
        }
    }
};

int main() {
    vector<Warrior> arena;
    ifstream ifs("warriors.txt");
    string command;
    string challenger;
    string fighter;
    int strength;
    while (ifs >> command) {
        if (command == "Warrior") {
            ifs >> challenger >> strength;
            addWarrior(challenger, strength, arena);
        }
        else if (command == "Status") {
            printWarriors(arena);
        }
        else if (command == "Battle") {
            ifs >> challenger >> fighter;
            battleWarriors(challenger, fighter, arena);
        }
    }
    ifs.close();
};
