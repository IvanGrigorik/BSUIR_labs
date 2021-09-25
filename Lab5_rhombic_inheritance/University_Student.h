//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
#define LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H

#include <ostream>
#include "Student.h"

class University_Student : public /*virtual*/ Student {
protected:
    int term{};

public:
    University_Student (const string &new_name, int new_GPA, int new_term) :
            Student(new_name, new_GPA), term(new_term) {};

    ~University_Student () = default;

    friend ostream &operator<< (ostream &os, const University_Student &student) {
        os << static_cast<const Student &>(student) << endl << "Term: " << student.term;
        return os;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
