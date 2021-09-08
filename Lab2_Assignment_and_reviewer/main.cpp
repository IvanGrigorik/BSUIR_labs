#include <iostream>
#include "Task.h"
#include "Verifier.h"
#include <array>

int main() {
    const int ARR_SIZE = 4;
    Task task1("New_name_1", 51);
    Task task3("Andrei", 41);

    std::cout << "Before the change: " << std::endl;
    show_info(task1);
    show_info(task3);

    Verifier::get_result(task1, 99);
    Verifier::get_result(task3, 13);

    std::cout << "After the change: " << std::endl << std::endl;
    show_info(task1);
    show_info(task3);

    std::array<Task, ARR_SIZE> Tasks_arr {{
                                        {"Name", 1},
                                        {"Name2", 2},
                                        {"Name3", 3},
                                        {"Name4", 4}}};

//    Task Tasks_arr[ARR_SIZE];
    for (const auto & i : Tasks_arr){
        show_info(i);
    }
    std::cout << std::endl << "After the change: " << std::endl;
    for (int i = 0; i < ARR_SIZE; i++){
        Verifier::get_result(Tasks_arr[i], static_cast<int>(Tasks_arr[i].get_result() + 10));
    }
    for (const auto & i : Tasks_arr){
        show_info(i);
    }

    return 0;
}