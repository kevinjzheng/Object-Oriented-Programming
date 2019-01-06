//
//  Courses.hpp
//  testrec007
//
//  Created by Kevin J. Zheng on 10/18/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef COURSES_H
#define COURSES_H

#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly {
    class Student;  // forward class declaration

    class Course {
        friend std::ostream& operator<<(std::ostream&, const Course&);
    public:
        Course(const std::string& courseName);
        std::string getName() const;
        void addStudent(Student*);
        void purge();
    private:
        std::string name;
        std::vector<Student*> students;
    };
}

#endif /* COURSES_H */
