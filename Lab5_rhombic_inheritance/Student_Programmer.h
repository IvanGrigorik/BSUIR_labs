//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H

#include <ostream>
#include <utility>
#include "University_Student.h"
#include "Programmer.h"

class Student_Programmer : public /*virtual*/ University_Student, public /*virtual*/ Programmer {
protected:
    string university_program_language{};

public:

    Student_Programmer (const string &new_name,
                        int new_salary, string new_programming_language,
                        int new_GPA, int new_term,
                        string new_university_program_language) :
            Programmer(new_name, new_salary, std::move(new_programming_language)),
            University_Student(new_name, new_GPA, new_term),
            university_program_language(std::move(new_university_program_language)) {};

    friend ostream &operator<< (ostream &os, const Student_Programmer &programmer) {
        os << static_cast<const University_Student &>(programmer) << ' ' << static_cast<const Programmer &>(programmer)
           << endl << " University program language: " << programmer.university_program_language;
        return os;
    }

};


#endif //LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
