//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_STUDENT_H
#define LAB5_RHOMBIC_INHERITANCE_STUDENT_H

#include "Man.h"

class Student : public virtual Man {
protected:
    int GPA{};

public:
    Student () : Man(), GPA() { cout << "Student created" << endl; };

    Student (const string &new_name, int new_GPA) : Man(new_name), GPA(new_GPA) {};

    ~Student () = default;

    void show () const override  {
        cout << "GPA: " << GPA << endl;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_STUDENT_H
