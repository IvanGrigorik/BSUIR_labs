//
// Created by Ivan on 25.09.2021.
//

#include "Programmer.h"

Programmer::Programmer (const string &name, int salary, string new_programming_language) :
        Man(name),
        Employee(name, salary),
        programming_language(std::move(new_programming_language)) {}

Programmer::~Programmer () {
    cout << "Programmer destructor called" << endl;
}

ostream &operator<< (ostream &os, const Programmer &programmer) {
    os << static_cast<const Employee &>(programmer) << endl
       << "Programming language: " << programmer.programming_language;
    return os;
}


