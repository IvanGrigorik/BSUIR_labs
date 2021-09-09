#include <iostream>
#include "Task.h"
#include "Verifier.h"
#include "func.h"
#include <array>

int main () {
    const int ARR_SIZE = 10;

    Task tasks_arr[ARR_SIZE];

    while (true) {
        switch (menu()) {
            case 1: {
                tasks_arr;
                break;
            }


            default:
                break;
        }
        if (menu() == 0)
            return 0;
        system("cls");
    }


    for (const auto &i : tasks_arr) {
        show_info(i);
    }
    cout << endl << "After the change: " << endl;
    for (auto &i : tasks_arr) {
        Verifier::get_result(i, static_cast<int>(i.get_result() + 10));
    }
    for (const auto &i : tasks_arr) {
        show_info(i);
    }


    return 0;
}

// Всё, что монжо ввести с клавиатуры  - вводится
// Запрос вывести все задания, у кого процентовка введённая с клавиатуры.