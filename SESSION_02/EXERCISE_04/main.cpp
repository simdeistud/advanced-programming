#include "student.h"

int main()
{
    const std::vector<Student> students{
        {"Andrea", 18, 7.4},
        {"Silvio", 19, 6.1},
        {"Michele", 19, 8.3},
        {"Giulia", 19, 7.0},
        {"Sara", 18, 7.9}
    };

    print_students_info(students);

    return 0;
}
