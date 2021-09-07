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

    std::cout << "After the change: " << std::endl;
    show_info(task1);
    show_info(task3);

    Task Tasks_arr[ARR_SIZE];

    std::array<Task, ARR_SIZE> new_arr {("Name", 13), };

    for (int i = 0; i < ARR_SIZE; i++) {
        Tasks_arr[i] = {"Name", 10 * i};
    }

    for (const auto & i : Tasks_arr){
        show_info(i);
    }
    for (int i = 0; i < ARR_SIZE; i++){
        Verifier::get_result(Tasks_arr[i], i*15);
    }
    for (const auto & i : Tasks_arr){
        show_info(i);
    }
}