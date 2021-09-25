//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H

#include "University_Student.h"
#include "Programmer.h"

#include <utility>

class Student_Programmer : public virtual University_Student, public virtual Programmer {
protected:
    string university_program_language{};

public:

    Student_Programmer () : Programmer(), University_Student() { cout << "Student-programmer created" << endl; };

    Student_Programmer (const string &new_name,
                        int new_salary, string new_programming_language,
                        int new_GPA, int new_term,
                        const string &new_university_program_language) :
            Programmer(new_name, new_salary, std::move(new_programming_language)),
            University_Student(new_name, new_GPA, new_term),
            university_program_language(new_university_program_language) {};

    void show () const final {
        Programmer::show();
        University_Student::show();
        cout << "University program language: " << university_program_language;
    }

};


#endif //LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
