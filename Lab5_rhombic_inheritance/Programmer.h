//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H

#include <ostream>
#include "Employee.h"

class Programmer : public virtual Employee {
protected:
    string programming_language{};

public:
    Programmer (const string &name, int salary, string new_programming_language);

    ~Programmer () override;

    friend ostream &operator<< (ostream &os, const Programmer &programmer);
};


#endif //LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
