//
// Created by Ivan on 09.09.2021.
//

#ifndef MAIN_CPP_MENU_FUNCTION_H
#define MAIN_CPP_MENU_FUNCTION_H

#include <list>
#include "Task.h"
#include "Verifier.h"

int get_menu_choice ();

void get_int (int &y, int max_size);

void add_task (list<Task> &tasks);

void show_tasks (const list<Task> &tasks);

void show_specific_tasks (const list<Task> &tasks);

#endif //MAIN_CPP_MENU_FUNCTION_H
