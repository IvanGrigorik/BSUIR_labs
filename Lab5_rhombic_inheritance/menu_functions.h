//
// Created by Ivan on 04.10.2021.
//

#ifndef UNIVERSITY_STUDENT_H_MENU_FUNCTIONS_H
#define UNIVERSITY_STUDENT_H_MENU_FUNCTIONS_H

#include <iostream>
#include "Student_Programmer.h"
#include "getters.h"

using namespace std;


int get_menu_choice ();

int get_change_person_class (Student_Programmer const& person);

void get_Student_programmer_data (Student_Programmer &person);

void change_Student_programmer_field(Student_Programmer &person);

#endif //UNIVERSITY_STUDENT_H_MENU_FUNCTIONS_H
