//
//  Registrar.hpp
//  testrec007
//
//  Created by Kevin J. Zheng on 10/18/18.
//  Copyright © 2018 Kevin J. Zheng. All rights reserved.
//

#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly {
    class Student;  // forward class declaration
    class Course;  // forward class declaration

    class Registrar {
        friend std::ostream& operator<<(std::ostream&, const Registrar&);
    public:
        Registrar();
        bool addCourse(const std::string&);
        bool addStudent(const std::string&);
        bool enrollStudentInCourse(const std::string& studentName,
                                   const std::string& courseName);
        bool cancelCourse(const std::string& courseName);
        void purge();
        
    private:
        size_t findStudent(const std::string&);
        size_t findCourse(const std::string&);
        
        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}

#endif /* REGISTRAR_H */
