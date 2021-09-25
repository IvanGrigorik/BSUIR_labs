//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H

#include "Employee.h"

class Programmer : public virtual Employee {
protected:
    string programming_language{};

private:
    Programmer () : Employee(), programming_language() { cout << "Programmer created" << endl; };

    Programmer (string new_name, int new_salary, string new_programming_language) :
            Employee(std::move(new_name), new_salary), programming_language(std::move(new_programming_language)) {};

    ~Programmer () = default;

    // Maybe I should write "virtual void" rather than "override"??
    void show () const override {
        Employee::show();
        cout << "Programmer language: " << programming_language << endl;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_PROGRAMMER_H
