//
// Created by Ivan on 25.09.2021.
//

#pragma once

#include "Man.h"

class Student : public virtual Man {
protected:
    int GPA{};

public:
    Student() = default;

    Student (const string &new_name, int new_GPA);

    ~Student () override;

    void set_GPA (int new_GPA);

    void re_GPA();

    friend ostream &operator<< (ostream &os, const Student &student);
};


