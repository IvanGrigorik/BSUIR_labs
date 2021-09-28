//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
#define LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H

#include "Student.h"

class University_Student : public Student {
protected:
    int term{};

public:
    University_Student (const string &name, int GPA, int new_term);

    ~University_Student () override;

    void set_term (int new_term);

    friend ostream &operator<< (ostream &os, const University_Student &student);
};


#endif //LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
