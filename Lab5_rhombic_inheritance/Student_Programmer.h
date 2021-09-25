//
// Created by Ivan on 25.09.2021.
//

#ifndef LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
#define LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H

#include "University_Student.h"
#include "Programmer.h"

class Student_Programmer : public virtual University_Student, public virtual Programmer {


public:


    void show () const final {
        University_Student::show();
        Programmer::show();

    }

};


#endif //LAB5_RHOMBIC_INHERITANCE_STUDENT_PROGRAMMER_H
