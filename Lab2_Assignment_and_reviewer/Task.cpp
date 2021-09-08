//
// Created by Ivan on 07.09.2021.
//

#include "Task.h"
#include <cassert>

const  Task::Id min_id = 0;
Task::Id Task::total_id = min_id;

// Constructor's and destructor
Task::Task() {
    id = ++total_id;
    set_result(1);
}

Task::Task(const Name &new_name, Result new_result) {
    if(!id){
        id = ++total_id;
    }
    set_name(new_name);
    set_result(new_result);
}

Task::~Task() {
    --total_id;
}


// Getters and setters (for realize encapsulation method)
void Task::set_name(const Name &new_name) {
    name = new_name;
}

// Первый Task показывает - что такое "Name", второй - что такое "get_name"
Task::Name Task::get_name() const {
    return name;
}

void Task::set_result(Task::Result new_result) {
    assert((new_result > 0 && new_result < 100) && "Invalid result size!");
    result = new_result;
}

Task::Result Task::get_result() const {
    return result;
}

Task::Id Task::get_id() const {
    return id;
}


void show_info(const Task &task_to_show) {
    std::cout << "Id: " << task_to_show.get_id() <<
              std::endl << "Name: " << task_to_show.get_name() <<
              std::endl << "Result: " << task_to_show.get_result() << "%" << std::endl;
}