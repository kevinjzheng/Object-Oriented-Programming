//
//  main.cpp
//  testrec007
//
//  Created by Kevin J. Zheng on 10/18/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

/*
 rec07
 Starter Code for required functionality
 */

#include "Student.cpp"
#include "Courses.cpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream&, const Course&);
public:
    Course(const string& courseName);
    string getName() const;
    void addStudent(Student*);
    void purge();
private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& stu);
public:
    Student(const string& name);
    string getName() const;
    void addCourse(Course*);
private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream&, const Registrar&);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();
    
private:
    size_t findStudent(const string&);
    size_t findCourse(const string&);
    
    vector<Course*> courses;
    vector<Student*> students;
};

ostream& operator<<(ostream& os, const Course& course) {
    os << "Course: " << course.name << "\nStudents: ";
    return os;
}
Course::Course(const string& courseName) : name(courseName) { }
string Course::getName() const { return name; }
void Course::addStudent(Student* stu) { students.push_back(stu); }
void Course::purge() {  }

ostream& operator<<(ostream& os, const Student& student) {
    return os;
}
Student::Student(const string& name) : name(name) { }
string Student::getName() const { return name; }
void Student::addCourse(Course * course) { courses.push_back(course); }

ostream& operator<<(ostream& os, const Registrar& registrar) {
    return os;
}

//Registrar::Registrar() { }
//bool Registrar::addCourse(const string& courseName) {
//    courses.push_back(courseName);
//}
//bool Registrar::addStudent(const string& studentName) {
//    students.push_back(studentName);
//}
//bool Registrar::enrollStudentInCourse(const string& studentName,
//                                      const string& courseName) {
//
//}
//bool Registrar::cancelCourse(const string& courseName) {
//    for (size_t i = 0, i < courses.size(); i++) {
//        if (courses[i]->getName() == courseName) {
//            Course* temp;
//            temp = course[i];
//            course[i] = course[courses.size() - 1];
//            courses[courses.size() - 1] = temp;
//        }
//    }
//}
//void Registrar::purge() { }

int main() {
    
    Registrar registrar;
    
    cout << "No courses or students added yet\n";
    cout << registrar << endl;
    
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;
    
    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;
    
    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;
    
    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;
    
    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout <<  "Should fail, i.e. do nothing, since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;
    
    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
    
    /*
     // [OPTIONAL - do later if time]
     cout << "ChangeStudentName FritzTheCat MightyMouse\n";
     registrar.changeStudentName("FritzTheCat", "MightyMouse");
     cout << registrar << endl;  // or registrar.printReport()
     
     cout << "DropStudentFromCourse MightyMouse CS101.001\n";
     registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
     cout << registrar << endl;  // or registrar.printReport()
     
     cout << "RemoveStudent FritzTheCat\n";
     registrar.removeStudent("FritzTheCat");
     cout << registrar << endl;  // or registrar.printReport()
     */
    
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}



