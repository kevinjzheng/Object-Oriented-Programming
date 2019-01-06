//
//  Student.cpp
//  testrec007
//
//  Created by Kevin J. Zheng on 10/18/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "Student.h"
#include "Courses.h"
#include "Registrar.h"

#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(ostream& os, const Student& student) {
        os << student.name << ": ";
        if (student.courses.size() == 0) {
            os << "No Courses";
        }
        else {
            for (size_t i = 0; i < student.courses.size(); i++)  {
                os << student.courses[i]->getName() << "\t";
            }
        }
        return os;
    }
    Student::Student(const string& name) : name(name) { }
    string Student::getName() const { return name; }
    void Student::addCourse(Course* course) { courses.push_back(course); }
    void Student::removeCourse(Course* course) {
        for (size_t i = 0; i < courses.size(); i++) {
            if (course == courses[i]) {
                courses[i] = courses[courses.size() - 1];
                courses.pop_back();
            }
        }
    }
}
