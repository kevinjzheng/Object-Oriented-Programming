//
//  Courses.cpp
//  testrec007
//
//  Created by Kevin J. Zheng on 10/18/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#include "Courses.h"
#include "Student.h"
#include "Registrar.h"

#include <string>
#include <iostream>
using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(ostream& os, const Course& course) {
        os << course.name << ": ";
        if (course.students.size() == 0) {
            os << "No Students";
        }
        else {
            for (size_t i = 0; i < course.students.size(); i++) {
                os << course.students[i]->getName() << "\t";
            }
        }
        return os;
    }
    Course::Course(const string& courseName) : name(courseName) { }
    string Course::getName() const { return name; }
    void Course::addStudent(Student* stu) { students.push_back(stu); }
    void Course::purge() {
        for (size_t i = 0; i < students.size(); i++) {
            students[i]->removeCourse(this);
        }
    }
}
