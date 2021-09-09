//
// Created by Ivan on 07.09.2021.
//

#include "Task.h"

const int min_id = 0;
int Task::total_id = min_id;

// Constructor's and destructor
Task::Task() {
    id = ++total_id;
    result = 0;
}

Task::Task(const string &new_name, int new_result) {
    id = (id == 0) ? ++total_id : id;
    name = new_name;
    result = new_result;
}

Task::~Task() {
    --total_id;
}

// Первый Task показывает - что такое "Name", второй - что такое "get_name"
int Task::get_result() const {
    return result;
}

void show_info(const Task &task_to_show) {
    cout << "Id: " << task_to_show.id <<
              endl << "Name: " << task_to_show.name <<
              endl << "Result: " << task_to_show.result << "%" << endl;
}