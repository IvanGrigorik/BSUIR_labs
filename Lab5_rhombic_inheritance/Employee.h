//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_EMPLOYEE_H
#define LAB5_RHOMBIC_INHERITANCE_EMPLOYEE_H

#include <ostream>
#include "Man.h"

class Employee : public /*virtual*/ Man {
protected:
    int salary{};

public:
    Employee (const string &new_name, int new_salary) :
            Man(new_name), salary(new_salary) {};

    ~Employee () = default;

    friend ostream &operator<< (ostream &os, const Employee &employee) {
        os << static_cast<const Man &>(employee) << endl << "Salary: " << employee.salary;
        return os;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_EMPLOYEE_H
