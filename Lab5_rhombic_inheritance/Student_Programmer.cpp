//
// Created by Ivan on 25.09.2021.
//

#include "Student_Programmer.h"


Student_Programmer::Student_Programmer (const string &name, int salary, string programming_language,
                                        int GPA, int term, string new_university_programming_language) :
        Man(name),
        Programmer(name, salary, std::move(programming_language)),
        University_Student(name, GPA, term) {
    university_program_language = std::move(new_university_programming_language);
}

ostream &operator<< (ostream &os, const Student_Programmer &programmer) {
    os << static_cast<const Programmer &>(programmer) << " " << endl
       << "GPA: " << programmer.GPA << endl
       << "Term: " << programmer.term << endl
       << "University program language: " << programmer.university_program_language << endl;
    return os;
}

Student_Programmer::~Student_Programmer () {
    cout << "Student programmer destructor called" << endl;
}
