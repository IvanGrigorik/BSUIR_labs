//
// Created by Ivan on 25.09.2021.
//

#include "University_Student.h"

University_Student::University_Student (const string &name, int GPA, int new_term) :
        Man(name), Student(name, GPA), term(new_term) {}

ostream &operator<< (ostream &os, const University_Student &student) {
    os << static_cast<const Student &>(student) << endl << "Term: " << student.term;
    return os;
}

University_Student::~University_Student () {
    cout << "University student destructor called" << endl;
}
