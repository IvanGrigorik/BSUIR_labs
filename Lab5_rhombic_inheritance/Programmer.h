//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H

#include <ostream>
#include "Employee.h"

class Programmer : public /*virtual*/ Employee {
protected:
    string programming_language{};

public:
    Programmer (const string &new_name, int new_salary, string new_programming_language) :
            Employee(new_name, new_salary), programming_language(std::move(new_programming_language)) {};

    ~Programmer () = default;

    friend ostream &operator<< (ostream &os, const Programmer &programmer) {
        os << static_cast<const Employee &>(programmer) << endl << "Programming_language: " << programmer.programming_language;
        return os;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
