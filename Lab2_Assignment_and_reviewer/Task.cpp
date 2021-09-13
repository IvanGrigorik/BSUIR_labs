//
// Created by Ivan on 07.09.2021.
//

#include "Task.h"
#include "Verifier.h"

const int min_id = 0;
int Task::total_id = min_id;

// Constructor's and destructor

Task::Task (const string &new_name) {
    id = ++total_id;
    set_name(new_name);
    result = 0;
}

Task::~Task () {
    total_id--;
}

// Getter
int Task::get_result () const {
    return result;
}

void Task::set_name (string new_name) {
    name = std::move(new_name);
}

void show_info (const Task &task_to_show) {
    cout << "Id: " << task_to_show.id <<
         endl << "Name: " << task_to_show.name <<
         endl << "Result: " << task_to_show.result << "%" << endl;
}



