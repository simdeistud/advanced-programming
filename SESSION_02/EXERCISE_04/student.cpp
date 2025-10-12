//
// Created by simone on 12/10/25.
//

#include "student.h"

#include <iostream>
#include <ostream>

void print_student_info(const Student& s)
{
    std::cout << "Name: " << s.name << std::endl;
    std::cout << "Age: " << s.age << std::endl;
    std::cout << "Average grade: " << s.avg_grade << std::endl;
}

void print_students_info(const std::vector<Student>& students)
{
    for (const auto& student : students)
    {
        print_student_info(student);
        std::cout << "=========================" << std::endl;
    }
}
