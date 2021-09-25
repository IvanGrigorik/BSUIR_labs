//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_STUDENT_H
#define LAB5_RHOMBIC_INHERITANCE_STUDENT_H

#include <ostream>
#include "Man.h"

class Student : public /*virtual*/ Man {
protected:
    int GPA{};

public:

    Student (const string &new_name, int new_GPA) : Man(new_name), GPA(new_GPA) {};

    ~Student () = default;

    friend ostream &operator<< (ostream &os, const Student &student) {
        os << static_cast<const Man &>(student) << endl << "GPA: " << student.GPA;
        return os;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_STUDENT_H
