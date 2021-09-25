//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
#define LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H

#include "Student.h"

class University_Student : public virtual Student {
protected:
    int term{};

public:
    University_Student () : Student(), term() {};

    University_Student (const string &new_name, int new_GPA, int new_term) :
            Student(new_name, new_GPA), term(new_term) {};

    ~University_Student () = default;

    void show () const override {
        Student::show();
        cout << "Term: " << term << endl;
    }
};


#endif //LAB5_RHOMBIC_INHERITANCE_UNIVERSITY_STUDENT_H
