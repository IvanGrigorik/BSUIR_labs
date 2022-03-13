//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H

#include "Employee.h"

class Programmer : public Employee {
protected:
    string programming_language{};

public:
    Programmer() = default;

    Programmer (const string &name, int salary, string new_programming_language);

    ~Programmer () override;

    void set_programming_language (string new_programming_language);

    void re_programming_language();

    friend ostream &operator<< (ostream &os, const Programmer &programmer);
};


#endif //LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
