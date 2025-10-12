#ifndef ADVANCED_PROGRAMMING_STUDENT_H
#define ADVANCED_PROGRAMMING_STUDENT_H
#include <string>
#include <vector>

struct Student
{
    std::string name;
    unsigned int age;
    double avg_grade;
};

void print_student_info(const Student& s);

void print_students_info(const std::vector<Student>& students);

#endif //ADVANCED_PROGRAMMING_STUDENT_H