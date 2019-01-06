//
//  rec06.cpp
//  rec06
//
//  Created by Kevin J. Zheng on 10/11/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

/*
 Recitation 06
 CS2124
 
 Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
        << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
    : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    const unsigned& getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& dir) {
        for (size_t i = 0; i < dir.size; i++) {
            os << *(dir.entries[i]) << endl;
        }
        return os;
    }
public:
    // Default constructor
    Directory() : size(0), capacity(1), entries(new Entry*[1]) {
        cout << "Default Directory" << endl;
    }
    // Destructor
    ~Directory() {
        cout << "Destructing Directory" << endl;
        for (size_t i = 0; i < size; i++) {
            delete entries[i];
        }
        delete [] entries;
    }
    // Copy-Constructor
    Directory(const Directory& oldDir) {
        cout << "Copying Directory" << endl;
        size = oldDir.size;
        capacity = oldDir.capacity;
        entries = new Entry*[size];
        for (size_t i = 0; i < size; i++) {
            entries[i] = new Entry(*(oldDir.entries[i]));
        }
    }
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity) {
            // something is missing!!!  Add it!
            cout << "Resizing Array!" << endl;
            Entry** oldEntries = entries;
            capacity *= 2;
            entries = new Entry*[capacity];
            for (size_t i = 0; i < size; i++) {
                entries[i] = oldEntries[i];
            }
            delete [] oldEntries;
        } // if
        cout << "New Entry Added!" << endl;
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    // Bracket Operator
    unsigned operator[](const string& name) const {
        cout << "Using Directory Bracket Operator" << endl;
        for (size_t i = 0; i < size; i++) {
            if (name == entries[i]->getName()) {
                return entries[i]->getPhone();
            }
        }
        // Didn't find the entry
        return 99999;
    }
    //  Assignment Operator
    Directory& operator=(const Directory& rhs) {
        cout << "Using Assignment Operator" << endl;
        // 1. Check for self assignment
        if (this != &rhs) {
            // 2. Free Up Space
            for (size_t i = 0; i < size; i++) {
                delete entries[i];
            }
            delete [] entries;
            // 3. Allocating
            entries = new Entry*[size];
            // 4. Copying
            size = rhs.size;
            capacity = rhs.capacity;
            for (size_t i = 0; i < size; i++) {
                entries[i] = new Entry(*(rhs.entries[i]));
            }
        }
        // 5. Returning yourself
        return *this;
    }
    
    
private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
//     Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;    // What function is being used??
    // copy - constructor
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;
    cout << d2 << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
    
} // main
