//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H

#include "University_Student.h"
#include "Programmer.h"

class Student_Programmer : public University_Student, public Programmer {
protected:
    string university_program_language{};

public:

    Student_Programmer (const string &name,
                        int salary,
                        string programming_language,
                        int GPA,
                        int term,
                        string new_university_programming_language);

    ~Student_Programmer () override;

    void set_university_program_language(string new_university_program_language);

    friend ostream &operator<< (ostream &os, const Student_Programmer &programmer);
};


#endif //LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
