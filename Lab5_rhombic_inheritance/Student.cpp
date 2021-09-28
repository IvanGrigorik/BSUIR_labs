//
// Created by Ivan on 25.09.2021.
//

#include "Student.h"

Student::Student (const string &new_name, int new_GPA) : Man(new_name) {
    cout << "Student constructor called" << endl;
    set_GPA(new_GPA);
}

Student::~Student () {
    cout << "Student destructor called" << endl;
}

ostream &operator<< (ostream &os, const Student &student) {
    os << static_cast<const Man &>(student) << endl << "GPA: " << student.GPA;
    return os;
}

void Student::set_GPA (int new_GPA) {
    this->GPA = new_GPA;
}
