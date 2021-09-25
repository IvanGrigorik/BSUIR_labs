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
    Employee () : Man(), salary() { cout << "Employee created" << endl; };

    Employee (const string &new_name, int new_salary) :
            Man(new_name), salary(new_salary) {};

    ~Employee () = default;

    void show () const override  {
        Man::show();
        cout << "Salary: " << salary << endl;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_EMPLOYEE_H
