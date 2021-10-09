//
// Created by Ivan on 04.10.2021.
//

#include "menu_functions.h"

int get_menu_choice () {
    system("cls");
    cout << "Enter what you want to enter: " <<
         endl << "1) Change something " <<
         endl << "2) Show people " <<
         endl << "0) Exit" <<
         endl << ">> ";

    int choice;
    get_int(choice, 2);
    return choice;
}

int get_change_people_class () {
    cout
            << "Enter what you want to change: " << endl
            << "1) Name" << endl
            << "2) Salary" << endl
            << "3) Programming language" << endl
            << "4) GPA" << endl
            << "5) Term" << endl
            << "6) University programming language" << endl;

    int choice;
    get_int(choice, 6);
    return choice;
}
