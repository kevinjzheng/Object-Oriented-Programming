//
//  rec05.cpp
//  rec05
//
//  Created by Kevin J. Zheng on 10/4/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Section { // lab section class
    // overloading the output operator for section class
    friend ostream& operator<<(ostream& os, const Section& section) {
        cout << "Section: " << section.sectionName << ", Time slot:";
        cout << section.slot;
        for (size_t i = 0; i < section.studentRec.size(); i++) {
            cout << *(section.studentRec[i]);
        }
        return os;
    }
    class TimeSlot {    // time slot class for that lab section
        // overloading the output operator for time slot class
        friend ostream& operator<<(ostream& os, const TimeSlot& slot) {
            cout << "[Day: " << slot.dayOfWeek << ", Start time: ";
            if (slot.hour <= 12){
                cout << slot.hour << "am], Students: " << endl;
            }
            else {
                cout << (slot.hour - 12) << "pm], Students: " << endl;
            }
            return os;
        }
    public:
        // default constructor for TimeSlot class
        TimeSlot(const string& dayOfWeek, unsigned hour) : dayOfWeek(dayOfWeek),
        hour(hour) { }
    private:
        string dayOfWeek;
        unsigned hour;
    };
    
    class StudentRecord {
        // overloading the output operator for student record class
        friend ostream& operator<<(ostream& os, const StudentRecord& students) {
            cout << "Name: " << students.name << ", Grades:";
            for (size_t i = 0; i < students.grades.size(); i++) {
                cout << ' ' << students.grades[i];
            }
            cout << "\n";
            return os;
        }
    public:
        // default constructor for StudentRecord, with array of -1 grades
        StudentRecord(const string& name) : name(name), grades(14,-1) { }
        
        string getName() {
            return name;
        }
        
        void setGrades(int grade, int week) {
            for (size_t i = 0; i < grades.size(); i++) {
                if (week == i+1) {
                    grades[i] = grade;
                }
            }
        }
    private:
        string name;
        vector<int> grades;
    };
public:
    // default constructor for Section class
    Section(const string& section, const string& dayOfWeek, unsigned hour) :
        sectionName(section), slot(dayOfWeek,hour) { }
    
    // copy-constructor
    Section(const Section& oldSection) : sectionName(oldSection.sectionName),
    slot(oldSection.slot) {
        for (size_t i = 0; i < oldSection.studentRec.size(); i++) {
            studentRec.push_back(new StudentRecord(*(oldSection.studentRec[i])));
        }
    }
    
    void addStudent(const string& studentName) {
        studentRec.push_back(new StudentRecord(studentName));
    }
    
    void addGrade(const string& studentName, int grade, int week) {
        for (size_t i = 0; i < studentRec.size(); i++) {
            if (studentRec[i]->getName() == studentName) {
                studentRec[i]->setGrades(grade, week);
            }
        }
    }
    // destructor for Section class
    ~Section(){
        cout << "Section " << sectionName << " is being deleted" << endl;
        for (size_t i = 0; i < studentRec.size(); i++){
            cout << "Deleting " << studentRec[i]->getName() << endl;
            delete studentRec[i];
        }
        studentRec.clear();
    }
private:
    string sectionName;
    TimeSlot slot;
    vector<StudentRecord*> studentRec;
};

class LabWorker {
    // overloading the output operator for LabWorker class
    friend ostream& operator<<(ostream& os, LabWorker& ta) {
        if (!ta.section) {
            cout << ta.name << " does not have a section" << endl;
        }
        else {
            cout << ta.name << " has " << *(ta.section);
        }
        return os;
    }
public:
    // default constructor for LabWorker class
    LabWorker(const string& name) : name(name) { }
    
    void addSection(Section& newSection) {
        section = &newSection;
    }
    
    void addGrade(const string& studentName, int grade, int week) {
        section->addGrade(studentName, grade, week);
    }
private:
    string name;
    Section* section = nullptr;
};

// ta needs to know what section he/she is

// Test code
// this triggers copy constructor for Section class
void doNothing(Section sec) {
    cout << sec << endl;
}

int main() {
    
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;
    
    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;
    
    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;
    
    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;
    
    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;
    
    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;
    
    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;
    
    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
    << "those students (or rather their records?)\n";
    
    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
    << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
    
} // main
