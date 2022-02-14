//
// Created by Ivan on 25.09.2021.
//

#include "Employee.h"

Employee::Employee (const string &name, int new_salary) :
        Man(name) {
    cout << "Employee constructor called" << endl;
    set_salary(new_salary);
}

Employee::~Employee () {
    cout << "Employee destructor called" << endl;
}

ostream &operator<< (ostream &os, const Employee &employee) {
    os << static_cast<const Man &>(employee) << endl << "Salary: " << employee.salary << "$";
    return os;
}

void Employee::set_salary (int new_salary) {
    this->salary = new_salary;
}

void Employee::re_salary () {
    cout << "Enter new salary: ";
    set_salary(get_int(5000));
}
