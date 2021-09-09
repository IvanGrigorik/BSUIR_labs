#include <iostream>
#include "Task.h"
#include "Verifier.h"
#include "func.h"
#include <array>

int main() {
    const int ARR_SIZE = 10;

    Task Tasks_arr[ARR_SIZE];

    while(menu())
    {
        cout << "Enter what you want to do: ";


        break;

    }


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

// Всё, что монжо ввести с клавиатуры  - вводится
// Запрос вывести все задания, у кого процентовка введённая с клавиатуры.