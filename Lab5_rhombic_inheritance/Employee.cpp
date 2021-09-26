//
// Created by Ivan on 25.09.2021.
//

#include "Employee.h"

Employee::Employee (const string &name, int new_salary) :
        Man(name), salary(new_salary) {}

Employee::~Employee () {
    cout << "Employee destructor called" << endl;
}

ostream &operator<< (ostream &os, const Employee &employee) {
    os << static_cast<const Man &>(employee) << endl << "Salary: " << employee.salary;
    return os;
}