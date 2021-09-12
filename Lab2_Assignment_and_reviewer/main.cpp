#include "Task.h"
#include "Verifier.h"
#include "menu_function.h"

int main () {

    list<Task> tasks;

    while (true) {
        switch (menu()) {
            case 1:
                add_task(tasks);
                break;

            case 2:
                show_specific_tasks(tasks);
                break;

            case 3:
                show_tasks(tasks);
                break;

            case 0:
                return 0;

            default:
                cout << "Invalid input!";
                system("cls");
                break;

        }
        system("cls");
    }
}

// Всё, что монжо ввести с клавиатуры  - вводится
// Запрос вывести все задания, у кого процентовка введённая с клавиатуры.

