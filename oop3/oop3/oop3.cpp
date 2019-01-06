//
//  oop3.cpp
//  oop3
//
//  Created by Kevin J. Zheng on 9/24/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//vector<int> row(6,0);
//vector<vector<int>> board(5,row);

//class Date {
//    friend ostream& operator << (ostream& os, const Date& rhs) {
//        os << rhs.month << '/' << rhs.day << '/' << rhs.year;
//        return os;
//    }
//
//public:
//    Date(int m, int d, int y) : month(m), day(d), year(y) {}
//    // there is no longer a default constructor
//private:
//    int month,day,year;
//};

// NESTING CLASSES

class Person {
    // still not a member function, still a function outside the class
    friend ostream& operator << (ostream& os, const Person& rhs);
    //    {
    //        os << "Person: name = " << rhs.name;    // no need to include endl
    //        return os;
    //    }
    class Date {
        friend ostream& operator << (ostream& os, const Date& rhs) {
            os << rhs.month << '/' << rhs.day << '/' << rhs.year;
            return os;
        }
        
    public:
        Date(int m, int d, int y) : month(m), day(d), year(y) {}
        // there is no longer a default constructor
    private:
        int month,day,year;
    };
public:
    Person(const string& name, int m, int d, int y) : name(name), dob(m,d,y) { }
    void display() const {
        cout << "Person: name = " << name << ", dob = " << endl;
    }
    const string& getName() const { return name; }
private:
    string name;
    Date dob;
};

ostream& operator << (ostream& os, const Person& rhs) {
    os << "Person: name = " << rhs.name;    // no need to include endl
    return os;
}

int main() {
    Person john("John", 9, 19, 2018);
    john.display();
    cout << john << endl;
    //    cout << john;
    //    operator << (cout,john);  this is what is being called when cout
    //    cout.operator << (john);  this means operator is a method of ostream class
    
    //    Date someday;   // called the constructor
    //    Date anotherDay(9, 19, 2018);
}
