#include "menu_functions.h"

int main() {

    Student_Programmer person;

    Man *man = new Student_Programmer;

    get_Student_programmer_data(person);

    while (true) {
        switch (get_menu_choice()) {
            case 1:
                change_Student_programmer_field(person);
                break;

            case 2:
                cout << endl << person;
                system("pause > 0");
                break;

            case 0:
                return 0;

        }
    }
}

/*
 * Дополнительное задание:
 * Всё вводится с клавиатуры. Можно будет изменить поле определённого класса. Все переменные подтягиваются с остальных классов. (что?)
 * (т.е. я хочу изменить что-то класса Employee и изменяю там зарплату).
 *
 * Всё с проверками.
 */