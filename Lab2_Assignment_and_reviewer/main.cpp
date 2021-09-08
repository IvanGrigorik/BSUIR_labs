#include <iostream>
#include "Task.h"
#include "Verifier.h"
#include <array>

int main() {
    const int ARR_SIZE = 4;
    Task task1("New_name_1", 51);
    Task task3("Andrei", 41);

    cout << "Before the change: " << endl;
    show_info(task1);
    show_info(task3);

    Verifier::get_result(task1, 99);
    Verifier::get_result(task3, 13);

    cout << "After the change: " << endl << endl;
    show_info(task1);
    show_info(task3);

    array<Task, ARR_SIZE> Tasks_arr {{
                                        {"Name", 1},
                                        {"Name2", 2},
                                        {"Name3", 3},
                                        {"Name4", 4}}};

//    Task Tasks_arr[ARR_SIZE];
    for (const auto & i : Tasks_arr){
        show_info(i);
    }
    cout << endl << "After the change: " << endl;
    for (int i = 0; i < ARR_SIZE; i++){
        Verifier::get_result(Tasks_arr[i], static_cast<int>(Tasks_arr[i].get_result() + 10));
    }
    for (const auto & i : Tasks_arr){
        show_info(i);
    }
    return 0;
}