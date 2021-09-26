//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
#define LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H

#include <ostream>
#include "Student.h"

class University_Student : public virtual Student {
protected:
    int term{};

public:
    University_Student (const string &name, int GPA, int new_term);

    ~University_Student () override;

    friend ostream &operator<< (ostream &os, const University_Student &student);
};


#endif //LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
