//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_EMPLOYEE_H
#define LAB5_RHOMBIC_INHERITANCE_EMPLOYEE_H

#include "Man.h"

class Employee : public virtual Man {
protected:
    int salary{};

public:
    Employee (const string &name, int new_salary);

    ~Employee () override;

    void set_salary (int new_salary);


    friend ostream &operator<< (ostream &os, const Employee &employee);
};


#endif //LAB5_RHOMBIC_INHERITANCE_EMPLOYEE_H
