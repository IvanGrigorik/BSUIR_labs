//
// Created by Ivan on 25.09.2021.
//

#include "University_Student.h"

University_Student::University_Student (const string &name, int GPA, int new_term) :
        Man(name), Student(name, GPA) {
    cout << "University student constructor called" << endl;
    set_term(new_term);
}

ostream &operator<< (ostream &os, const University_Student &student) {
    os << static_cast<const Student &>(student) << endl << "Term: " << student.term;
    return os;
}

University_Student::~University_Student () {
    cout << "University student destructor called" << endl;
}

void University_Student::set_term (int new_term) {
    this->term = new_term;
}

void University_Student::re_term () {
    cout << "Enter new term: ";
    int new_term{};
    get_int(new_term, 4);
    set_term(new_term);
}
